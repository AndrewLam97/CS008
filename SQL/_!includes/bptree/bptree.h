#ifndef BPTREE_H
#define BPTREE_H
#include <algorithm>
#include <cassert>
#include <iostream>

//! The maximum of a and b. Used in some compile-time formulas.
#define BTREE_MAX(a, b)          ((a) < (b) ? (b) : (a))

/*!
 * Generates default traits for a B+ tree used as a set or map. It estimates
 * leaf and inner node sizes by assuming a cache line multiple of 256 bytes.
*/
template <typename Key, typename Value>
struct btree_default_traits {
    //! If true, the tree will self verify its invariants after each insert() or
    //! erase(). The header must have been compiled with TLX_BTREE_DEBUG
    //! defined.
    static const bool self_verify = false;

    //! If true, the tree will print out debug information and a tree dump
    //! during insert() or erase() operation. The header must have been
    //! compiled with TLX_BTREE_DEBUG defined and key_type must be std::ostream
    //! printable.
    static const bool debug = false;

    //! Number of slots in each leaf of the tree. Estimated so that each node
    //! has a size of about 256 bytes.
    static const int leaf_slots =
        TLX_BTREE_MAX(8, 256 / (sizeof(Value)));

    //! Number of slots in each inner node of the tree. Estimated so that each
    //! node has a size of about 256 bytes.
    static const int inner_slots =
        TLX_BTREE_MAX(8, 256 / (sizeof(Key) + sizeof(void*)));

    //! As of stx-btree-0.9, the code does linear search in find_lower() and
    //! find_upper() instead of binary_search, unless the node size is larger
    //! than this threshold. See notes at
    //! http://panthema.net/2013/0504-STX-B+Tree-Binary-vs-Linear-Search
    static const size_t binsearch_threshold = 256;
};

/*!
 * Basic class implementing a B+ tree data structure in memory.
 *
 * The base implementation of an in-memory B+ tree. It is based on the
 * implementation in Cormen's Introduction into Algorithms, Jan Jannink's paper
 * and other algorithm resources. Almost all STL-required function calls are
 * implemented. The asymptotic time requirements of the STL are not always
 * fulfilled in theory, however, in practice this B+ tree performs better than a
 * red-black tree and almost always uses less memory. The insertion function
 * splits the nodes on the recursion unroll. Erase is largely based on Jannink's
 * ideas.
 *
 * This class is specialized into btree_set, btree_multiset, btree_map and
 * btree_multimap using default template parameters and facade functions.
 */
template <typename Key, typename Value,
          typename KeyOfValue,
          typename Compare = std::less<Key>,
          typename Traits = btree_default_traits<Key, Value>,
          bool Duplicates = false,
          typename Allocator = std::allocator<Value> >
class BPTree
{
public:
    //! \name Template Parameter Types
    //! \{

    //! First template parameter: The key type of the B+ tree. This is stored in
    //! inner nodes.
    typedef Key key_type;

    //! Second template parameter: Composition pair of key and data types, or
    //! just the key for set containers. This data type is stored in the leaves.
    typedef Value value_type;

    //! Third template: key extractor class to pull key_type from value_type.
    typedef KeyOfValue key_of_value;

    //! Fourth template parameter: key_type comparison function object
    typedef Compare key_compare;

    //! Fifth template parameter: Traits object used to define more parameters
    //! of the B+ tree
    typedef Traits traits;

    //! Sixth template parameter: Allow duplicate keys in the B+ tree. Used to
    //! implement multiset and multimap.
    static const bool allow_duplicates = Duplicates;

    //! Seventh template parameter: STL allocator for tree nodes
    typedef Allocator allocator_type;

public:
    //! \name Constructed Types
    //! \{

    //! Typedef of our own type
    typedef BPTree<key_type, value_type, key_of_value, key_compare,
                  traits, allow_duplicates, allocator_type> Self;

    //! Size type used to count keys
    typedef size_t size_type;

    //! \}

public:
    //! \name Static Constant Options and Values of the B+ Tree
    //! \{

    //! Base B+ tree parameter: The number of key/data slots in each leaf
    static const unsigned short leaf_slotmax = traits::leaf_slots;

    //! Base B+ tree parameter: The number of key slots in each inner node,
    //! this can differ from slots in each leaf.
    static const unsigned short inner_slotmax = traits::inner_slots;

    //! Computed B+ tree parameter: The minimum number of key/data slots used
    //! in a leaf. If fewer slots are used, the leaf will be merged or slots
    //! shifted from it's siblings.
    static const unsigned short leaf_slotmin = (leaf_slotmax / 2);

    //! Computed B+ tree parameter: The minimum number of key slots used
    //! in an inner node. If fewer slots are used, the inner node will be
    //! merged or slots shifted from it's siblings.
    static const unsigned short inner_slotmin = (inner_slotmax / 2);

    //! Debug parameter: Enables expensive and thorough checking of the B+ tree
    //! invariants after each insert/erase operation.
    static const bool self_verify = traits::self_verify;

    //! Debug parameter: Prints out lots of debug information about how the
    //! algorithms change the tree. Requires the header file to be compiled
    //! with TLX_BTREE_DEBUG and the key type must be std::ostream printable.
    static const bool debug = traits::debug;

    //! \}

private:
    //! \name Node Classes for In-Memory Nodes
    //! \{

    //! The header structure of each node in-memory. This structure is extended
    //! by InnerNode or LeafNode.
    struct node {
        //! Level in the b-tree, if level == 0 -> leaf node
        unsigned short level;

        //! Number of key slotuse use, so the number of valid children or data
        //! pointers
        unsigned short slotuse;

        //! Delayed initialisation of constructed node.
        void initialize(const unsigned short l) {
            level = l;
            slotuse = 0;
        }

        //! True if this is a leaf node.
        bool is_leafnode() const {
            return (level == 0);
        }
    };

    //! Extended structure of a inner node in-memory. Contains only keys and no
    //! data items.
    struct InnerNode : public node {
        //! Define an related allocator for the InnerNode structs.
        typedef typename Allocator::template rebind<InnerNode>::other alloc_type;

        //! Keys of children or data pointers
        key_type slotkey[inner_slotmax]; // NOLINT

        //! Pointers to children
        node* childid[inner_slotmax + 1]; // NOLINT

        //! Set variables to initial values.
        void initialize(const unsigned short l) {
            node::initialize(l);
        }

        //! Return key in slot s
        const key_type& key(size_t s) const {
            return slotkey[s];
        }

        //! True if the node's slots are full.
        bool is_full() const {
            return (node::slotuse == inner_slotmax);
        }

        //! True if few used entries, less than half full.
        bool is_few() const {
            return (node::slotuse <= inner_slotmin);
        }

        //! True if node has too few entries.
        bool is_underflow() const {
            return (node::slotuse < inner_slotmin);
        }
    };

    //! Extended structure of a leaf node in memory. Contains pairs of keys and
    //! data items. Key and data slots are kept together in value_type.
    struct LeafNode : public node {
        //! Define an related allocator for the LeafNode structs.
        typedef typename Allocator::template rebind<LeafNode>::other alloc_type;

        //! Double linked list pointers to traverse the leaves
        LeafNode* prev_leaf;

        //! Double linked list pointers to traverse the leaves
        LeafNode* next_leaf;

        //! Array of (key, data) pairs
        value_type slotdata[leaf_slotmax]; // NOLINT

        //! Set variables to initial values
        void initialize() {
            node::initialize(0);
            prev_leaf = next_leaf = nullptr;
        }

        //! Return key in slot s.
        const key_type& key(size_t s) const {
            return key_of_value::get(slotdata[s]);
        }

        //! True if the node's slots are full.
        bool is_full() const {
            return (node::slotuse == leaf_slotmax);
        }

        //! True if few used entries, less than half full.
        bool is_few() const {
            return (node::slotuse <= leaf_slotmin);
        }

        //! True if node has too few entries.
        bool is_underflow() const {
            return (node::slotuse < leaf_slotmin);
        }

        //! Set the (key,data) pair in slot. Overloaded function used by
        //! bulk_load().
        void set_slot(unsigned short slot, const value_type& value) {
            slotdata[slot] = value;
        }
    };

    //! \}

public:
    //! \name Iterators
    //! \{

    class iterator;

    //! STL-like iterator object for B+ tree items. The iterator points to a
    //! specific slot number in a leaf.
    class iterator
    {
    public:
        // *** Types

        //! The key type of the btree. Returned by key().
        typedef typename BPTree::key_type key_type;

        //! The value type of the btree. Returned by operator*().
        typedef typename BPTree::value_type value_type;

        //! Reference to the value_type. STL required.
        typedef value_type& reference;

        //! Pointer to the value_type. STL required.
        typedef value_type* pointer;

        //! STL-magic iterator category
        typedef std::bidirectional_iterator_tag iterator_category;

        //! STL-magic
        typedef ptrdiff_t difference_type;

        //! Our own type
        typedef iterator self;

    private:
        // *** Members

        //! The currently referenced leaf node of the tree
        typename BPTree::LeafNode* curr_leaf;

        //! Current key/data slot referenced
        unsigned short curr_slot;

        //! Also friendly to the base btree class, because erase_iter() needs
        //! to read the curr_leaf and curr_slot values directly.
        friend class BPTree<key_type, value_type, key_of_value, key_compare,
                           traits, allow_duplicates, allocator_type>;


    public:
        // *** Methods

        //! Default-Constructor of a mutable iterator
        iterator()
            : curr_leaf(nullptr), curr_slot(0)
        { }

        //! Initializing-Constructor of a mutable iterator
        iterator(typename BPTree::LeafNode* l, unsigned short s)
            : curr_leaf(l), curr_slot(s)
        { }


        //! Dereference the iterator.
        reference operator * () const {
            return curr_leaf->slotdata[curr_slot];
        }

        //! Dereference the iterator.
        pointer operator -> () const {
            return &curr_leaf->slotdata[curr_slot];
        }

        //! Key of the current slot.
        const key_type& key() const {
            return curr_leaf->key(curr_slot);
        }

        //! Prefix++ advance the iterator to the next slot.
        iterator& operator ++ () {
            if (curr_slot + 1u < curr_leaf->slotuse) {
                ++curr_slot;
            }
            else if (curr_leaf->next_leaf != nullptr) {
                curr_leaf = curr_leaf->next_leaf;
                curr_slot = 0;
            }
            else {
                // this is end()
                curr_slot = curr_leaf->slotuse;
            }

            return *this;
        }

        //! Postfix++ advance the iterator to the next slot.
        iterator operator ++ (int) {
            iterator tmp = *this;   // copy ourselves

            if (curr_slot + 1u < curr_leaf->slotuse) {
                ++curr_slot;
            }
            else if (curr_leaf->next_leaf != nullptr) {
                curr_leaf = curr_leaf->next_leaf;
                curr_slot = 0;
            }
            else {
                // this is end()
                curr_slot = curr_leaf->slotuse;
            }

            return tmp;
        }

        //! Prefix-- backstep the iterator to the last slot.
        iterator& operator -- () {
            if (curr_slot > 0) {
                --curr_slot;
            }
            else if (curr_leaf->prev_leaf != nullptr) {
                curr_leaf = curr_leaf->prev_leaf;
                curr_slot = curr_leaf->slotuse - 1;
            }
            else {
                // this is begin()
                curr_slot = 0;
            }

            return *this;
        }

        //! Postfix-- backstep the iterator to the last slot.
        iterator operator -- (int) {
            iterator tmp = *this;   // copy ourselves

            if (curr_slot > 0) {
                --curr_slot;
            }
            else if (curr_leaf->prev_leaf != nullptr) {
                curr_leaf = curr_leaf->prev_leaf;
                curr_slot = curr_leaf->slotuse - 1;
            }
            else {
                // this is begin()
                curr_slot = 0;
            }

            return tmp;
        }

        //! Equality of iterators.
        bool operator == (const iterator& x) const {
            return (x.curr_leaf == curr_leaf) && (x.curr_slot == curr_slot);
        }

        //! Inequality of iterators.
        bool operator != (const iterator& x) const {
            return (x.curr_leaf != curr_leaf) || (x.curr_slot != curr_slot);
        }
    }; 

public:
    //! \name Small Statistics Structure
    //! \{

    /*!
     * A small struct containing basic statistics about the B+ tree. It can be
     * fetched using get_stats().
     */
    struct tree_stats {
        //! Number of items in the B+ tree
        size_type size;

        //! Number of leaves in the B+ tree
        size_type leaves;

        //! Number of inner nodes in the B+ tree
        size_type inner_nodes;

        //! Base B+ tree parameter: The number of key/data slots in each leaf
        static const unsigned short leaf_slots = Self::leaf_slotmax;

        //! Base B+ tree parameter: The number of key slots in each inner node.
        static const unsigned short inner_slots = Self::inner_slotmax;

        //! Zero initialized
        tree_stats()
            : size(0),
              leaves(0), inner_nodes(0)
        { }

        //! Return the total number of nodes
        size_type nodes() const {
            return inner_nodes + leaves;
        }

        //! Return the average fill of leaves
        double avgfill_leaves() const {
            return static_cast<double>(size) / (leaves * leaf_slots);
        }
    };

    //! \}

private:
    //! \name Tree Object Data Members
    //! \{

    //! Pointer to the B+ tree's root node, either leaf or inner node.
    node* root_;

    //! Pointer to first leaf in the double linked leaf chain.
    LeafNode* head_leaf_;

    //! Pointer to last leaf in the double linked leaf chain.
    LeafNode* tail_leaf_;

    //! Other small statistics about the B+ tree.
    tree_stats stats_;

    //! Key comparison object. More comparison functions are generated from
    //! this < relation.
    key_compare key_less_;

    //! Memory allocator.
    allocator_type allocator_;

    //! \}

public:
    //! \name Constructors and Destructor
    //! \{

    //! Default constructor initializing an empty B+ tree with the standard key
    //! comparison function.
    explicit BPTree(const allocator_type& alloc = allocator_type())
        : root_(nullptr), head_leaf_(nullptr), tail_leaf_(nullptr),
          allocator_(alloc)
    { }

    //! Frees up all used B+ tree memory pages
    ~BPTree() {
        clear();
    }

    //! Fast swapping of two identical B+ tree objects.
    void swap(BPTree& from) {
        std::swap(root_, from.root_);
        std::swap(head_leaf_, from.head_leaf_);
        std::swap(tail_leaf_, from.tail_leaf_);
        std::swap(stats_, from.stats_);
        std::swap(key_less_, from.key_less_);
        std::swap(allocator_, from.allocator_);
    }

    //! \}

public:
    //! \name Key and Value Comparison Function Objects
    //! \{

    //! Function class to compare value_type objects. Required by the STL
    class value_compare
    {
    protected:
        //! Key comparison function from the template parameter
        key_compare key_comp;

        //! Constructor called from BPTree::value_comp()
        explicit value_compare(key_compare kc)
            : key_comp(kc)
        { }

        //! Friendly to the btree class so it may call the constructor
        friend class BPTree<key_type, value_type, key_of_value, key_compare,
                           traits, allow_duplicates, allocator_type>;

    public:
        //! Function call "less"-operator resulting in true if x < y.
        bool operator () (const value_type& x, const value_type& y) const {
            return key_comp(x.first, y.first);
        }
    };

    //! Constant access to the key comparison object sorting the B+ tree.
    key_compare key_comp() const {
        return key_less_;
    }

    //! Constant access to a constructed value_type comparison object. Required
    //! by the STL.
    value_compare value_comp() const {
        return value_compare(key_less_);
    }

    //! \}

private:
    //! \name Convenient Key Comparison Functions Generated From key_less
    //! \{

    //! True if a < b ? "constructed" from key_less_()
    bool key_less(const key_type& a, const key_type& b) const {
        return key_less_(a, b);
    }

    //! True if a <= b ? constructed from key_less()
    bool key_lessequal(const key_type& a, const key_type& b) const {
        return !key_less_(b, a);
    }

    //! True if a > b ? constructed from key_less()
    bool key_greater(const key_type& a, const key_type& b) const {
        return key_less_(b, a);
    }

    //! True if a >= b ? constructed from key_less()
    bool key_greaterequal(const key_type& a, const key_type& b) const {
        return !key_less_(a, b);
    }

    //! True if a == b ? constructed from key_less(). This requires the <
    //! relation to be a total order, otherwise the B+ tree cannot be sorted.
    bool key_equal(const key_type& a, const key_type& b) const {
        return !key_less_(a, b) && !key_less_(b, a);
    }

    //! \}

public:
    //! \name Allocators
    //! \{

    //! Return the base node allocator provided during construction.
    allocator_type get_allocator() const {
        return allocator_;
    }

    //! \}

private:
    //! \name Node Object Allocation and Deallocation Functions
    //! \{

    //! Return an allocator for LeafNode objects.
    typename LeafNode::alloc_type leaf_node_allocator() {
        return typename LeafNode::alloc_type(allocator_);
    }

    //! Return an allocator for InnerNode objects.
    typename InnerNode::alloc_type inner_node_allocator() {
        return typename InnerNode::alloc_type(allocator_);
    }

    //! Allocate and initialize a leaf node
    LeafNode * allocate_leaf() {
        LeafNode* n = new (leaf_node_allocator().allocate(1)) LeafNode();
        n->initialize();
        stats_.leaves++;
        return n;
    }

    //! Allocate and initialize an inner node
    InnerNode * allocate_inner(unsigned short level) {
        InnerNode* n = new (inner_node_allocator().allocate(1)) InnerNode();
        n->initialize(level);
        stats_.inner_nodes++;
        return n;
    }

    //! Correctly free either inner or leaf node, destructs all contained key
    //! and value objects.
    void free_node(node* n) {
        if (n->is_leafnode()) {
            LeafNode* ln = static_cast<LeafNode*>(n);
            typename LeafNode::alloc_type a(leaf_node_allocator());
            a.destroy(ln);
            a.deallocate(ln, 1);
            stats_.leaves--;
        }
        else {
            InnerNode* in = static_cast<InnerNode*>(n);
            typename InnerNode::alloc_type a(inner_node_allocator());
            a.destroy(in);
            a.deallocate(in, 1);
            stats_.inner_nodes--;
        }
    }

    //! \}

public:
    //! \name Fast Destruction of the B+ Tree
    //! \{

    //! Frees all key/data pairs and all nodes of the tree.
    void clear() {
        if (root_)
        {
            clear_recursive(root_);
            free_node(root_);

            root_ = nullptr;
            head_leaf_ = tail_leaf_ = nullptr;

            stats_ = tree_stats();
        }
    }

private:
    //! Recursively free up nodes.
    void clear_recursive(node* n) {
        if (n->is_leafnode())
        {
            LeafNode* leafnode = static_cast<LeafNode*>(n);

            for (unsigned short slot = 0; slot < leafnode->slotuse; ++slot)
            {
                // data objects are deleted by LeafNode's destructor
            }
        }
        else
        {
            InnerNode* innernode = static_cast<InnerNode*>(n);

            for (unsigned short slot = 0; slot < innernode->slotuse + 1; ++slot)
            {
                clear_recursive(innernode->childid[slot]);
                free_node(innernode->childid[slot]);
            }
        }
    }

    //! \}

public:
    //! \name STL Iterator Construction Functions
    //! \{

    //! Constructs a read/data-write iterator that points to the first slot in
    //! the first leaf of the B+ tree.
    iterator begin() {
        return iterator(head_leaf_, 0);
    }

    //! Constructs a read/data-write iterator that points to the first invalid
    //! slot in the last leaf of the B+ tree.
    iterator end() {
        return iterator(tail_leaf_, tail_leaf_ ? tail_leaf_->slotuse : 0);
    }

private:
    //! \name B+ Tree Node Binary Search Functions
    //! \{

    //! Searches for the first key in the node n greater or equal to key. Uses
    //! binary search with an optional linear self-verification. This is a
    //! template function, because the slotkey array is located at different
    //! places in LeafNode and InnerNode.
    template <typename node_type>
    unsigned short find_lower(const node_type* n, const key_type& key) const {
        if (sizeof(*n) > traits::binsearch_threshold)
        {
            if (n->slotuse == 0) return 0;

            unsigned short lo = 0, hi = n->slotuse;

            while (lo < hi)
            {
                unsigned short mid = (lo + hi) >> 1;

                if (key_lessequal(key, n->key(mid))) {
                    hi = mid; // key <= mid
                }
                else {
                    lo = mid + 1; // key > mid
                }
            }

            return lo;
        }
        else // for nodes <= binsearch_threshold do linear search.
        {
            unsigned short lo = 0;
            while (lo < n->slotuse && key_less(n->key(lo), key)) ++lo;
            return lo;
        }
    }

    //! Searches for the first key in the node n greater than key. Uses binary
    //! search with an optional linear self-verification. This is a template
    //! function, because the slotkey array is located at different places in
    //! LeafNode and InnerNode.
    template <typename node_type>
    unsigned short find_upper(const node_type* n, const key_type& key) const {
        if (sizeof(*n) > traits::binsearch_threshold)
        {
            if (n->slotuse == 0) return 0;

            unsigned short lo = 0, hi = n->slotuse;

            while (lo < hi)
            {
                unsigned short mid = (lo + hi) >> 1;

                if (key_less(key, n->key(mid))) {
                    hi = mid; // key < mid
                }
                else {
                    lo = mid + 1; // key >= mid
                }
            }

            return lo;
        }
        else // for nodes <= binsearch_threshold do linear search.
        {
            unsigned short lo = 0;
            while (lo < n->slotuse && key_lessequal(n->key(lo), key)) ++lo;
            return lo;
        }
    }

    //! \}

public:
    //! \name Access Functions to the Item Count
    //! \{

    //! Return the number of key/data pairs in the B+ tree
    size_type size() const {
        return stats_.size;
    }

    //! Returns true if there is at least one key/data pair in the B+ tree
    bool empty() const {
        return (size() == size_type(0));
    }

    //! Returns the largest possible size of the B+ Tree. This is just a
    //! function required by the STL standard, the B+ Tree can hold more items.
    size_type max_size() const {
        return size_type(-1);
    }

    //! Return a const reference to the current statistics.
    const struct tree_stats& get_stats() const {
        return stats_;
    }

    //! \}

public:
    //! \name STL Access Functions Querying the Tree by Descending to a Leaf
    //! \{

    //! Non-STL function checking whether a key is in the B+ tree. The same as
    //! (find(k) != end()) or (count() != 0).
    bool exists(const key_type& key) const {
        const node* n = root_;
        if (!n) return false;

        while (!n->is_leafnode())
        {
            const InnerNode* inner = static_cast<const InnerNode*>(n);
            unsigned short slot = find_lower(inner, key);

            n = inner->childid[slot];
        }

        const LeafNode* leaf = static_cast<const LeafNode*>(n);

        unsigned short slot = find_lower(leaf, key);
        return (slot < leaf->slotuse && key_equal(key, leaf->key(slot)));
    }

    //! Tries to locate a key in the B+ tree and returns an iterator to the
    //! key/data slot if found. If unsuccessful it returns end().
    iterator find(const key_type& key) {
        node* n = root_;
        if (!n) return end();

        while (!n->is_leafnode())
        {
            const InnerNode* inner = static_cast<const InnerNode*>(n);
            unsigned short slot = find_lower(inner, key);

            n = inner->childid[slot];
        }

        LeafNode* leaf = static_cast<LeafNode*>(n);

        unsigned short slot = find_lower(leaf, key);
        return (slot < leaf->slotuse && key_equal(key, leaf->key(slot)))
               ? iterator(leaf, slot) : end();
    }

    //! Tries to locate a key in the B+ tree and returns the number of identical
    //! key entries found.
    size_type count(const key_type& key) const {
        const node* n = root_;
        if (!n) return 0;

        while (!n->is_leafnode())
        {
            const InnerNode* inner = static_cast<const InnerNode*>(n);
            unsigned short slot = find_lower(inner, key);

            n = inner->childid[slot];
        }

        const LeafNode* leaf = static_cast<const LeafNode*>(n);

        unsigned short slot = find_lower(leaf, key);
        size_type num = 0;

        while (leaf && slot < leaf->slotuse && key_equal(key, leaf->key(slot)))
        {
            ++num;
            if (++slot >= leaf->slotuse)
            {
                leaf = leaf->next_leaf;
                slot = 0;
            }
        }

        return num;
    }

    //! Searches the B+ tree and returns an iterator to the first pair equal to
    //! or greater than key, or end() if all keys are smaller.
    iterator lower_bound(const key_type& key) {
        node* n = root_;
        if (!n) return end();

        while (!n->is_leafnode())
        {
            const InnerNode* inner = static_cast<const InnerNode*>(n);
            unsigned short slot = find_lower(inner, key);

            n = inner->childid[slot];
        }

        LeafNode* leaf = static_cast<LeafNode*>(n);

        unsigned short slot = find_lower(leaf, key);
        return iterator(leaf, slot);
    }

    //! Searches the B+ tree and returns an iterator to the first pair greater
    //! than key, or end() if all keys are smaller or equal.
    iterator upper_bound(const key_type& key) {
        node* n = root_;
        if (!n) return end();

        while (!n->is_leafnode())
        {
            const InnerNode* inner = static_cast<const InnerNode*>(n);
            unsigned short slot = find_upper(inner, key);

            n = inner->childid[slot];
        }

        LeafNode* leaf = static_cast<LeafNode*>(n);

        unsigned short slot = find_upper(leaf, key);
        return iterator(leaf, slot);
    }

    //! Searches the B+ tree and returns both lower_bound() and upper_bound().
    std::pair<iterator, iterator> equal_range(const key_type& key) {
        return std::pair<iterator, iterator>(
            lower_bound(key), upper_bound(key));
    }

public:
    //! \name B+ Tree Object Comparison Functions
    //! \{

    //! Equality relation of B+ trees of the same type. B+ trees of the same
    //! size and equal elements (both key and data) are considered equal. Beware
    //! of the random ordering of duplicate keys.
    bool operator == (const BPTree& other) const {
        return (size() == other.size()) &&
               std::equal(begin(), end(), other.begin());
    }

    //! Inequality relation. Based on operator==.
    bool operator != (const BPTree& other) const {
        return !(*this == other);
    }

    //! Total ordering relation of B+ trees of the same type. It uses
    //! std::lexicographical_compare() for the actual comparison of elements.
    bool operator < (const BPTree& other) const {
        return std::lexicographical_compare(
            begin(), end(), other.begin(), other.end());
    }

    //! Greater relation. Based on operator<.
    bool operator > (const BPTree& other) const {
        return other < *this;
    }

    //! Less-equal relation. Based on operator<.
    bool operator <= (const BPTree& other) const {
        return !(other < *this);
    }

    //! Greater-equal relation. Based on operator<.
    bool operator >= (const BPTree& other) const {
        return !(*this < other);
    }

    //! \}

public:
    //! \name Fast Copy: Assign Operator and Copy Constructors
    //! \{

    //! Assignment operator. All the key/data pairs are copied.
    BPTree& operator = (const BPTree& other) {
        if (this != &other)
        {
            clear();

            key_less_ = other.key_comp();
            allocator_ = other.get_allocator();

            if (other.size() != 0)
            {
                stats_.leaves = stats_.inner_nodes = 0;
                if (other.root_) {
                    root_ = copy_recursive(other.root_);
                }
                stats_ = other.stats_;
            }

            if (self_verify) verify();
        }
        return *this;
    }

    //! Copy constructor. The newly initialized B+ tree object will contain a
    //! copy of all key/data pairs.
    BPTree(const BPTree& other)
        : root_(nullptr), head_leaf_(nullptr), tail_leaf_(nullptr),
          stats_(other.stats_),
          key_less_(other.key_comp()),
          allocator_(other.get_allocator()) {
        if (size() > 0)
        {
            stats_.leaves = stats_.inner_nodes = 0;
            if (other.root_) {
                root_ = copy_recursive(other.root_);
            }
            if (self_verify) verify();
        }
    }

private:
    //! Recursively copy nodes from another B+ tree object
    struct node * copy_recursive(const node* n) {
        if (n->is_leafnode())
        {
            const LeafNode* leaf = static_cast<const LeafNode*>(n);
            LeafNode* newleaf = allocate_leaf();

            newleaf->slotuse = leaf->slotuse;
            std::copy(leaf->slotdata, leaf->slotdata + leaf->slotuse,
                      newleaf->slotdata);

            if (head_leaf_ == nullptr)
            {
                head_leaf_ = tail_leaf_ = newleaf;
                newleaf->prev_leaf = newleaf->next_leaf = nullptr;
            }
            else
            {
                newleaf->prev_leaf = tail_leaf_;
                tail_leaf_->next_leaf = newleaf;
                tail_leaf_ = newleaf;
            }

            return newleaf;
        }
        else
        {
            const InnerNode* inner = static_cast<const InnerNode*>(n);
            InnerNode* newinner = allocate_inner(inner->level);

            newinner->slotuse = inner->slotuse;
            std::copy(inner->slotkey, inner->slotkey + inner->slotuse,
                      newinner->slotkey);

            for (unsigned short slot = 0; slot <= inner->slotuse; ++slot)
            {
                newinner->childid[slot] = copy_recursive(inner->childid[slot]);
            }

            return newinner;
        }
    }

    //! \}

public:
    //! \name Public Insertion Functions
    //! \{

    //! Attempt to insert a key/data pair into the B+ tree. If the tree does not
    //! allow duplicate keys, then the insert may fail if it is already present.
    std::pair<iterator, bool> insert(const value_type& x) {
        return insert_start(key_of_value::get(x), x);
    }

    //! Attempt to insert a key/data pair into the B+ tree. The iterator hint is
    //! currently ignored by the B+ tree insertion routine.
    iterator insert(iterator /* hint */, const value_type& x) {
        return insert_start(key_of_value::get(x), x).first;
    }

    //! Attempt to insert the range [first,last) of value_type pairs into the B+
    //! tree. Each key/data pair is inserted individually; to bulk load the
    //! tree, use a constructor with range.
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
        InputIterator iter = first;
        while (iter != last)
        {
            insert(*iter);
            ++iter;
        }
    }

    //! \}

private:
    //! \name Private Insertion Functions
    //! \{

    //! Start the insertion descent at the current root and handle root splits.
    //! Returns true if the item was inserted
    std::pair<iterator, bool>
    insert_start(const key_type& key, const value_type& value) {

        node* newchild = nullptr;
        key_type newkey = key_type();

        if (root_ == nullptr) {
            root_ = head_leaf_ = tail_leaf_ = allocate_leaf();
        }

        std::pair<iterator, bool> r =
            insert_descend(root_, key, value, &newkey, &newchild);

        if (newchild)
        {
            // this only occurs if insert_descend() could not insert the key
            // into the root node, this mean the root is full and a new root
            // needs to be created.
            InnerNode* newroot = allocate_inner(root_->level + 1);
            newroot->slotkey[0] = newkey;

            newroot->childid[0] = root_;
            newroot->childid[1] = newchild;

            newroot->slotuse = 1;

            root_ = newroot;
        }

        // increment size if the item was inserted
        if (r.second) ++stats_.size;

        return r;
    }

    /*!
     * Insert an item into the B+ tree.
     *
     * Descend down the nodes to a leaf, insert the key/data pair in a free
     * slot. If the node overflows, then it must be split and the new split node
     * inserted into the parent. Unroll / this splitting up to the root.
    */
    std::pair<iterator, bool> insert_descend(
        node* n, const key_type& key, const value_type& value,
        key_type* splitkey, node** splitnode) {

        if (!n->is_leafnode())
        {
            InnerNode* inner = static_cast<InnerNode*>(n);

            key_type newkey = key_type();
            node* newchild = nullptr;

            unsigned short slot = find_lower(inner, key);

            std::pair<iterator, bool> r =
                insert_descend(inner->childid[slot],
                               key, value, &newkey, &newchild);

            if (newchild)
            {
                if (inner->is_full())
                {
                    split_inner_node(inner, splitkey, splitnode, slot);

                    // check if insert slot is in the split sibling node
                    if (slot == inner->slotuse + 1 &&
                        inner->slotuse < (*splitnode)->slotuse)
                    {
                        // special case when the insert slot matches the split
                        // place between the two nodes, then the insert key
                        // becomes the split key.

                        InnerNode* split = static_cast<InnerNode*>(*splitnode);

                        // move the split key and it's datum into the left node
                        inner->slotkey[inner->slotuse] = *splitkey;
                        inner->childid[inner->slotuse + 1] = split->childid[0];
                        inner->slotuse++;

                        // set new split key and move corresponding datum into
                        // right node
                        split->childid[0] = newchild;
                        *splitkey = newkey;

                        return r;
                    }
                    else if (slot >= inner->slotuse + 1)
                    {
                        // in case the insert slot is in the newly create split
                        // node, we reuse the code below.

                        slot -= inner->slotuse + 1;
                        inner = static_cast<InnerNode*>(*splitnode);
                    }
                }

                // move items and put pointer to child node into correct slot
                std::copy_backward(
                    inner->slotkey + slot, inner->slotkey + inner->slotuse,
                    inner->slotkey + inner->slotuse + 1);
                std::copy_backward(
                    inner->childid + slot, inner->childid + inner->slotuse + 1,
                    inner->childid + inner->slotuse + 2);

                inner->slotkey[slot] = newkey;
                inner->childid[slot + 1] = newchild;
                inner->slotuse++;
            }

            return r;
        }
        else // n->is_leafnode() == true
        {
            LeafNode* leaf = static_cast<LeafNode*>(n);

            unsigned short slot = find_lower(leaf, key);

            if (!allow_duplicates &&
                slot < leaf->slotuse && key_equal(key, leaf->key(slot))) {
                return std::pair<iterator, bool>(iterator(leaf, slot), false);
            }

            if (leaf->is_full())
            {
                split_leaf_node(leaf, splitkey, splitnode);

                // check if insert slot is in the split sibling node
                if (slot >= leaf->slotuse)
                {
                    slot -= leaf->slotuse;
                    leaf = static_cast<LeafNode*>(*splitnode);
                }
            }

            // move items and put data item into correct data slot
            std::copy_backward(
                leaf->slotdata + slot, leaf->slotdata + leaf->slotuse,
                leaf->slotdata + leaf->slotuse + 1);

            leaf->slotdata[slot] = value;
            leaf->slotuse++;

            if (splitnode && leaf != *splitnode && slot == leaf->slotuse - 1)
            {
                // special case: the node was split, and the insert is at the
                // last slot of the old node. then the splitkey must be updated.
                *splitkey = key;
            }

            return std::pair<iterator, bool>(iterator(leaf, slot), true);
        }
    }

    //! Split up a leaf node into two equally-filled sibling leaves. Returns the
    //! new nodes and it's insertion key in the two parameters.
    void split_leaf_node(LeafNode* leaf,
                         key_type* out_newkey, node** out_newleaf) {

        unsigned short mid = (leaf->slotuse >> 1);

        LeafNode* newleaf = allocate_leaf();

        newleaf->slotuse = leaf->slotuse - mid;

        newleaf->next_leaf = leaf->next_leaf;
        if (newleaf->next_leaf == nullptr) {
            tail_leaf_ = newleaf;
        }
        else {
            newleaf->next_leaf->prev_leaf = newleaf;
        }

        std::copy(leaf->slotdata + mid, leaf->slotdata + leaf->slotuse,
                  newleaf->slotdata);

        leaf->slotuse = mid;
        leaf->next_leaf = newleaf;
        newleaf->prev_leaf = leaf;

        *out_newkey = leaf->key(leaf->slotuse - 1);
        *out_newleaf = newleaf;
    }

    //! Split up an inner node into two equally-filled sibling nodes. Returns
    //! the new nodes and it's insertion key in the two parameters. Requires the
    //! slot of the item will be inserted, so the nodes will be the same size
    //! after the insert.
    void split_inner_node(InnerNode* inner, key_type* out_newkey,
                          node** out_newinner, unsigned int addslot) {
        unsigned short mid = (inner->slotuse >> 1);

        // if the split is uneven and the overflowing item will be put into the
        // larger node, then the smaller split node may underflow
        if (addslot <= mid && mid > inner->slotuse - (mid + 1))
            mid--;

        InnerNode* newinner = allocate_inner(inner->level);

        newinner->slotuse = inner->slotuse - (mid + 1);

        std::copy(inner->slotkey + mid + 1, inner->slotkey + inner->slotuse,
                  newinner->slotkey);
        std::copy(inner->childid + mid + 1, inner->childid + inner->slotuse + 1,
                  newinner->childid);

        inner->slotuse = mid;

        *out_newkey = inner->key(mid);
        *out_newinner = newinner;
    }

private:
    //! \name Support Class Encapsulating Deletion Results
	//! Result flags of recursive deletion.
    enum result_flags_t {
        //! Deletion successful and no fix-ups necessary.
        btree_ok = 0,

        //! Deletion not successful because key was not found.
        btree_not_found = 1,

        //! Deletion successful, the last key was updated so parent slotkeys
        //! need updates.
        btree_update_lastkey = 2,

        //! Deletion successful, children nodes were merged and the parent needs
        //! to remove the empty node.
        btree_fixmerge = 4
    };

    //! B+ tree recursive deletion has much information which is needs to be
    //! passed upward.
    struct result_t {
        //! Merged result flags
        result_flags_t flags;

        //! The key to be updated at the parent's slot
        key_type lastkey;

        //! Constructor of a result with a specific flag, this can also be used
        //! as for implicit conversion.
        result_t(result_flags_t f = btree_ok) // NOLINT
            : flags(f), lastkey()
        { }

        //! Constructor with a lastkey value.
        result_t(result_flags_t f, const key_type& k)
            : flags(f), lastkey(k)
        { }

        //! Test if this result object has a given flag set.
        bool has(result_flags_t f) const {
            return (flags & f) != 0;
        }

        //! Merge two results OR-ing the result flags and overwriting lastkeys.
        result_t& operator |= (const result_t& other) {
            flags = result_flags_t(flags | other.flags);

            // we overwrite existing lastkeys on purpose
            if (other.has(btree_update_lastkey))
                lastkey = other.lastkey;

            return *this;
        }
    };

    //! \}

public:
    //! \name Public Erase Functions
    //! \{

    //! Erases one (the first) of the key/data pairs associated with the given
    //! key.
    bool erase_one(const key_type& key) {
        if (!root_) return false;

        result_t result = erase_one_descend(
            key, root_, nullptr, nullptr, nullptr, nullptr, nullptr, 0);

        if (!result.has(btree_not_found))
            --stats_.size;

        return !result.has(btree_not_found);
    }

    //! Erases all the key/data pairs associated with the given key. This is
    //! implemented using erase_one().
    size_type erase(const key_type& key) {
        size_type c = 0;

        while (erase_one(key))
        {
            ++c;
            if (!allow_duplicates) break;
        }

        return c;
    }

    //! Erase the key/data pair referenced by the iterator.
    void erase(iterator iter) {
        if (!root_) return;

        result_t result = erase_iter_descend(
            iter, root_, nullptr, nullptr, nullptr, nullptr, nullptr, 0);

        if (!result.has(btree_not_found))
            --stats_.size;
    }

private:
    //! \name Private Erase Functions
    //! \{

    /*!
     * Erase one (the first) key/data pair in the B+ tree matching key.
     *
     * Descends down the tree in search of key. During the descent the parent,
     * left and right siblings and their parents are computed and passed
     * down. Once the key/data pair is found, it is removed from the leaf. If
     * the leaf underflows 6 different cases are handled. These cases resolve
     * the underflow by shifting key/data pairs from adjacent sibling nodes,
     * merging two sibling nodes or trimming the tree.
     */
    result_t erase_one_descend(const key_type& key,
                               node* curr,
                               node* left, node* right,
                               InnerNode* left_parent, InnerNode* right_parent,
                               InnerNode* parent, unsigned int parentslot) {
        if (curr->is_leafnode())
        {
            LeafNode* leaf = static_cast<LeafNode*>(curr);
            LeafNode* left_leaf = static_cast<LeafNode*>(left);
            LeafNode* right_leaf = static_cast<LeafNode*>(right);

            unsigned short slot = find_lower(leaf, key);

            if (slot >= leaf->slotuse || !key_equal(key, leaf->key(slot)))
            {
                return btree_not_found;
            }

            std::copy(leaf->slotdata + slot + 1, leaf->slotdata + leaf->slotuse,
                      leaf->slotdata + slot);

            leaf->slotuse--;

            result_t myres = btree_ok;

            // if the last key of the leaf was changed, the parent is notified
            // and updates the key of this leaf
            if (slot == leaf->slotuse)
            {
                if (parent && parentslot < parent->slotuse)
                {
                    parent->slotkey[parentslot] = leaf->key(leaf->slotuse - 1);
                }
                else
                {
                    if (leaf->slotuse >= 1)
                    {
                        myres |= result_t(
                            btree_update_lastkey, leaf->key(leaf->slotuse - 1));
                    }
                    else
                    { }
                }
            }

            if (leaf->is_underflow() && !(leaf == root_ && leaf->slotuse >= 1))
            {
                // determine what to do about the underflow

                // case : if this empty leaf is the root, then delete all nodes
                // and set root to nullptr.
                if (left_leaf == nullptr && right_leaf == nullptr)
                {
                    free_node(root_);

                    root_ = leaf = nullptr;
                    head_leaf_ = tail_leaf_ = nullptr;

                    return btree_ok;
                }
                // case : if both left and right leaves would underflow in case
                // of a shift, then merging is necessary. choose the more local
                // merger with our parent
                else if ((left_leaf == nullptr || left_leaf->is_few()) &&
                         (right_leaf == nullptr || right_leaf->is_few()))
                {
                    if (left_parent == parent)
                        myres |= merge_leaves(left_leaf, leaf, left_parent);
                    else
                        myres |= merge_leaves(leaf, right_leaf, right_parent);
                }
                // case : the right leaf has extra data, so balance right with
                // current
                else if ((left_leaf != nullptr && left_leaf->is_few()) &&
                         (right_leaf != nullptr && !right_leaf->is_few()))
                {
                    if (right_parent == parent)
                        myres |= shift_left_leaf(
                            leaf, right_leaf, right_parent, parentslot);
                    else
                        myres |= merge_leaves(left_leaf, leaf, left_parent);
                }
                // case : the left leaf has extra data, so balance left with
                // current
                else if ((left_leaf != nullptr && !left_leaf->is_few()) &&
                         (right_leaf != nullptr && right_leaf->is_few()))
                {
                    if (left_parent == parent)
                        shift_right_leaf(
                            left_leaf, leaf, left_parent, parentslot - 1);
                    else
                        myres |= merge_leaves(leaf, right_leaf, right_parent);
                }
                // case : both the leaf and right leaves have extra data and our
                // parent, choose the leaf with more data
                else if (left_parent == right_parent)
                {
                    if (left_leaf->slotuse <= right_leaf->slotuse)
                        myres |= shift_left_leaf(
                            leaf, right_leaf, right_parent, parentslot);
                    else
                        shift_right_leaf(
                            left_leaf, leaf, left_parent, parentslot - 1);
                }
                else
                {
                    if (left_parent == parent)
                        shift_right_leaf(
                            left_leaf, leaf, left_parent, parentslot - 1);
                    else
                        myres |= shift_left_leaf(
                            leaf, right_leaf, right_parent, parentslot);
                }
            }

            return myres;
        }
        else // !curr->is_leafnode()
        {
            InnerNode* inner = static_cast<InnerNode*>(curr);
            InnerNode* left_inner = static_cast<InnerNode*>(left);
            InnerNode* right_inner = static_cast<InnerNode*>(right);

            node* myleft, * myright;
            InnerNode* myleft_parent, * myright_parent;

            unsigned short slot = find_lower(inner, key);

            if (slot == 0) {
                myleft =
                    (left == nullptr) ? nullptr :
                    static_cast<InnerNode*>(left)->childid[left->slotuse - 1];
                myleft_parent = left_parent;
            }
            else {
                myleft = inner->childid[slot - 1];
                myleft_parent = inner;
            }

            if (slot == inner->slotuse) {
                myright =
                    (right == nullptr) ? nullptr :
                    static_cast<InnerNode*>(right)->childid[0];
                myright_parent = right_parent;
            }
            else {
                myright = inner->childid[slot + 1];
                myright_parent = inner;
            }

            result_t result = erase_one_descend(
                key,
                inner->childid[slot],
                myleft, myright,
                myleft_parent, myright_parent,
                inner, slot);

            result_t myres = btree_ok;

            if (result.has(btree_not_found))
            {
                return result;
            }

            if (result.has(btree_update_lastkey))
            {
                if (parent && parentslot < parent->slotuse)
                {
                    parent->slotkey[parentslot] = result.lastkey;
                }
                else
                {
                    myres |= result_t(btree_update_lastkey, result.lastkey);
                }
            }

            if (result.has(btree_fixmerge))
            {
                // either the current node or the next is empty and should be
                // removed
                if (inner->childid[slot]->slotuse != 0)
                    slot++;

                // this is the child slot invalidated by the merge
                free_node(inner->childid[slot]);

                std::copy(
                    inner->slotkey + slot, inner->slotkey + inner->slotuse,
                    inner->slotkey + slot - 1);
                std::copy(
                    inner->childid + slot + 1,
                    inner->childid + inner->slotuse + 1,
                    inner->childid + slot);

                inner->slotuse--;

                if (inner->level == 1)
                {
                    // fix split key for children leaves
                    slot--;
                    LeafNode* child =
                        static_cast<LeafNode*>(inner->childid[slot]);
                    inner->slotkey[slot] = child->key(child->slotuse - 1);
                }
            }

            if (inner->is_underflow() &&
                !(inner == root_ && inner->slotuse >= 1))
            {
                // case: the inner node is the root and has just one child. that
                // child becomes the new root
                if (left_inner == nullptr && right_inner == nullptr)
                {
                    root_ = inner->childid[0];

                    inner->slotuse = 0;
                    free_node(inner);

                    return btree_ok;
                }
                // case : if both left and right leaves would underflow in case
                // of a shift, then merging is necessary. choose the more local
                // merger with our parent
                else if ((left_inner == nullptr || left_inner->is_few()) &&
                         (right_inner == nullptr || right_inner->is_few()))
                {
                    if (left_parent == parent)
                        myres |= merge_inner(
                            left_inner, inner, left_parent, parentslot - 1);
                    else
                        myres |= merge_inner(
                            inner, right_inner, right_parent, parentslot);
                }
                // case : the right leaf has extra data, so balance right with
                // current
                else if ((left_inner != nullptr && left_inner->is_few()) &&
                         (right_inner != nullptr && !right_inner->is_few()))
                {
                    if (right_parent == parent)
                        shift_left_inner(
                            inner, right_inner, right_parent, parentslot);
                    else
                        myres |= merge_inner(
                            left_inner, inner, left_parent, parentslot - 1);
                }
                // case : the left leaf has extra data, so balance left with
                // current
                else if ((left_inner != nullptr && !left_inner->is_few()) &&
                         (right_inner != nullptr && right_inner->is_few()))
                {
                    if (left_parent == parent)
                        shift_right_inner(
                            left_inner, inner, left_parent, parentslot - 1);
                    else
                        myres |= merge_inner(
                            inner, right_inner, right_parent, parentslot);
                }
                // case : both the leaf and right leaves have extra data and our
                // parent, choose the leaf with more data
                else if (left_parent == right_parent)
                {
                    if (left_inner->slotuse <= right_inner->slotuse)
                        shift_left_inner(
                            inner, right_inner, right_parent, parentslot);
                    else
                        shift_right_inner(
                            left_inner, inner, left_parent, parentslot - 1);
                }
                else
                {
                    if (left_parent == parent)
                        shift_right_inner(
                            left_inner, inner, left_parent, parentslot - 1);
                    else
                        shift_left_inner(
                            inner, right_inner, right_parent, parentslot);
                }
            }

            return myres;
        }
    }

    //! Merge two leaf nodes. The function moves all key/data pairs from right
    //! to left and sets right's slotuse to zero. The right slot is then removed
    //! by the calling parent node.
    result_t merge_leaves(LeafNode* left, LeafNode* right,
                          InnerNode* parent) {
        (void)parent;

        std::copy(right->slotdata, right->slotdata + right->slotuse,
                  left->slotdata + left->slotuse);

        left->slotuse += right->slotuse;

        left->next_leaf = right->next_leaf;
        if (left->next_leaf)
            left->next_leaf->prev_leaf = left;
        else
            tail_leaf_ = left;

        right->slotuse = 0;

        return btree_fixmerge;
    }

    //! Merge two inner nodes. The function moves all key/childid pairs from
    //! right to left and sets right's slotuse to zero. The right slot is then
    //! removed by the calling parent node.
    static result_t merge_inner(InnerNode* left, InnerNode* right,
                                InnerNode* parent, unsigned int parentslot) {

        // retrieve the decision key from parent
        left->slotkey[left->slotuse] = parent->slotkey[parentslot];
        left->slotuse++;

        // copy over keys and children from right
        std::copy(right->slotkey, right->slotkey + right->slotuse,
                  left->slotkey + left->slotuse);
        std::copy(right->childid, right->childid + right->slotuse + 1,
                  left->childid + left->slotuse);

        left->slotuse += right->slotuse;
        right->slotuse = 0;

        return btree_fixmerge;
    }

    //! Balance two leaf nodes. The function moves key/data pairs from right to
    //! left so that both nodes are equally filled. The parent node is updated
    //! if possible.
    static result_t shift_left_leaf(
        LeafNode* left, LeafNode* right,
        InnerNode* parent, unsigned int parentslot) {

        unsigned int shiftnum = (right->slotuse - left->slotuse) >> 1;

        // copy the first items from the right node to the last slot in the left
        // node.

        std::copy(right->slotdata, right->slotdata + shiftnum,
                  left->slotdata + left->slotuse);

        left->slotuse += shiftnum;

        // shift all slots in the right node to the left

        std::copy(right->slotdata + shiftnum, right->slotdata + right->slotuse,
                  right->slotdata);

        right->slotuse -= shiftnum;

        // fixup parent
        if (parentslot < parent->slotuse) {
            parent->slotkey[parentslot] = left->key(left->slotuse - 1);
            return btree_ok;
        }
        else {  // the update is further up the tree
            return result_t(btree_update_lastkey, left->key(left->slotuse - 1));
        }
    }

    //! Balance two inner nodes. The function moves key/data pairs from right to
    //! left so that both nodes are equally filled. The parent node is updated
    //! if possible.
    static void shift_left_inner(InnerNode* left, InnerNode* right,
                                 InnerNode* parent, unsigned int parentslot) {
        unsigned int shiftnum = (right->slotuse - left->slotuse) >> 1;

        // copy the parent's decision slotkey and childid to the first new key
        // on the left
        left->slotkey[left->slotuse] = parent->slotkey[parentslot];
        left->slotuse++;

        // copy the other items from the right node to the last slots in the
        // left node.
        std::copy(right->slotkey, right->slotkey + shiftnum - 1,
                  left->slotkey + left->slotuse);
        std::copy(right->childid, right->childid + shiftnum,
                  left->childid + left->slotuse);

        left->slotuse += shiftnum - 1;

        // fixup parent
        parent->slotkey[parentslot] = right->slotkey[shiftnum - 1];

        // shift all slots in the right node
        std::copy(
            right->slotkey + shiftnum, right->slotkey + right->slotuse,
            right->slotkey);
        std::copy(
            right->childid + shiftnum, right->childid + right->slotuse + 1,
            right->childid);

        right->slotuse -= shiftnum;
    }

    //! Balance two leaf nodes. The function moves key/data pairs from left to
    //! right so that both nodes are equally filled. The parent node is updated
    //! if possible.
    static void shift_right_leaf(LeafNode* left, LeafNode* right,
                                 InnerNode* parent, unsigned int parentslot) {
        unsigned int shiftnum = (left->slotuse - right->slotuse) >> 1;

        // shift all slots in the right node
        std::copy_backward(right->slotdata, right->slotdata + right->slotuse,
                           right->slotdata + right->slotuse + shiftnum);

        right->slotuse += shiftnum;

        // copy the last items from the left node to the first slot in the right
        // node.
        std::copy(left->slotdata + left->slotuse - shiftnum,
                  left->slotdata + left->slotuse,
                  right->slotdata);

        left->slotuse -= shiftnum;

        parent->slotkey[parentslot] = left->key(left->slotuse - 1);
    }

    //! Balance two inner nodes. The function moves key/data pairs from left to
    //! right so that both nodes are equally filled. The parent node is updated
    //! if possible.
    static void shift_right_inner(InnerNode* left, InnerNode* right,
                                  InnerNode* parent, unsigned int parentslot) {
        unsigned int shiftnum = (left->slotuse - right->slotuse) >> 1;

        // shift all slots in the right node

        std::copy_backward(
            right->slotkey, right->slotkey + right->slotuse,
            right->slotkey + right->slotuse + shiftnum);
        std::copy_backward(
            right->childid, right->childid + right->slotuse + 1,
            right->childid + right->slotuse + 1 + shiftnum);

        right->slotuse += shiftnum;

        // copy the parent's decision slotkey and childid to the last new key on
        // the right
        right->slotkey[shiftnum - 1] = parent->slotkey[parentslot];

        // copy the remaining last items from the left node to the first slot in
        // the right node.
        std::copy(left->slotkey + left->slotuse - shiftnum + 1,
                  left->slotkey + left->slotuse,
                  right->slotkey);
        std::copy(left->childid + left->slotuse - shiftnum + 1,
                  left->childid + left->slotuse + 1,
                  right->childid);

        // copy the first to-be-removed key from the left node to the parent's
        // decision slot
        parent->slotkey[parentslot] = left->slotkey[left->slotuse - shiftnum];

        left->slotuse -= shiftnum;
    }

};


#endif // BPTREE_H