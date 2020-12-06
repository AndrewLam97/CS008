/*
 * Author: Andrew Lam
 * Project: BPlusTree
 * Purpose: BPlusTree Class
 * Notes: Header File.
 */
#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

template <class T>
class BPlusTree;

template <class T>
class BPlusTreeNode;

template <class T>
class BPlusTreeNode{
public:
    BPlusTreeNode(int _t, bool _leaf);          // Constructor 

    bool contains(const T& entry);              //true if entry can be found in the array
    T& get(const T& entry);                     //return a reference to entry in the tree
    //T* find(const T& entry);                  //return a pointer to this key. NULL if not there.
    BPlusTreeNode* find(T entry);
    int greaterThanOrEqualTo(const T& entry);   //return index of first element greater than or equal to entry

    int size() const;                           //count the number of elements in the tree
    bool empty() const;                         //true if the tree is empty

    void print(BPlusTreeNode<T>* cursor);
private:
    static const int t = 1;
    //static const int MIN = 1;
    //static const int MAX = 2;

    int data_count;                            //number of data elements
    T data[2*t-1];                           //holds the keys
    int child_count;                           //number of children
    BPlusTreeNode<T>* subset[2*t];             //subtrees
    
    bool leaf;
    bool is_leaf() const {return leaf;}

    BPlusTreeNode* nextNode;
    BPlusTreeNode* prevNode;

    //insert element functions
    void loose_insert(const T& entry);              //allows MAXIMUM+1 data elements in the root
    void splitChild(int i, BPlusTreeNode<T> *y);
    void fix_excess(int i);                         //fix excess of data elements in child i

    //remove element functions:
    bool remove(const T& entry);
    void loose_remove(const T& entry);              //allows MINIMUM-1 data elements in the root
    void fix_shortage(int i);                       //fix shortage of data elements in child i

    void remove_biggest(T& entry);                  //remove the biggest child of this tree->entry

    void removeIfLeaf(int i);
    void removeNotLeaf(int i);

    T getPrev(int i);
    T getNext(int i);

    void rotate_left(int i);                        //transfer one element LEFT from child i
    void rotate_right(int i);                       //transfer one element RIGHT from child i
    void merge_with_next_subset(int i);             //merge subset i with subset i+1

    void traverse();                                //traverse tree in ascending order
    void ll_traverse(vector<BPlusTreeNode<T>*>&ll);

friend class BPlusTree<T>;
};

template <class T>
class BPlusTree{
public:
    class Iterator{
        public:
            friend class BPlusTree;
            Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):it(_it), key_ptr(_key_ptr){}

            T operator *(){
                assert(key_ptr<it->data_count);
                return ll[key_ptr]->data[0];
            }

            Iterator operator++(int un_used){
                ++key_ptr;
                return *this;
            }

            Iterator operator++(){
                key_ptr++;
                return *this;
            }
            friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
                return (lhs==rhs);
            }

            friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
                return (lhs!=rhs);
            }
            void print_Iterator(){
            }
            bool is_null(){return !it;}


        private:
            BPlusTree<T>* it;
            int key_ptr;
    };

    BPlusTree( int _t=1, bool dups = false);

    void clear_tree();                          //clear this object (delete all nodes etc.)
    void copy_tree(const BPlusTree<T>& other);      //copy other into this object

    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    BPlusTreeNode<T>* find(const T& entry);      //return a pointer to node containing entry
    bool contains(const T& entry);
    T& get(const T& entry);                     //return a reference to entry in the tree
    //T* find(const T& entry);                  //return a pointer to this key. NULL if not there.

    void print_tree(int level = 0, ostream &outs=cout) const; //print a readable version of the tree
    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me){
        return outs;
    }
    vector<BPlusTreeNode<T>*> get_ll(){return ll;}
    int get_ll_size(){return ll.size();}
    int get_size(){return ll.size();}

    void traverse();                            //traverse tree in ascending order
    void ll_traverse();                         //traverse leafs in a linked list fashion

    void print();
    void print_ll();
private:
    BPlusTreeNode<T>* smallestNode();
    int size;
    vector<BPlusTreeNode<T>*>ll;
    bool dups_ok;                               //true if duplicate keys may be inserted
    BPlusTreeNode<T> *root;
    int t;
    //static const int MINIMUM = 2;
    //static const int MAXIMUM = 2 * MINIMUM - 1;
};

//---------------------------------------------------------------------
//B_PLUS_TREE
//B_PLUS_TREE
//B_PLUS_TREE
//---------------------------------------------------------------------

template <typename T>
BPlusTree<T>::BPlusTree(int _t, bool dups){
    this->dups_ok = dups;
    root = nullptr;
    size = 0;
    t = _t;
}

template <typename T>               /////////////////
void BPlusTree<T>::print(){
    if((root != nullptr)){
        root->print(root);
    }
}

template <typename T>
void BPlusTree<T>::print_ll(){
    //if(DEBUG)cout << "ll size: " << ll.size() << endl;
    //if(DEBUG)cout << "Printing ll: ";
    for(int x = 0; x<ll.size();x++){
        cout << ll[x]->data[0] << " ";
    }
    cout << endl;
}

template <typename T>
void BPlusTree<T>::traverse(){
    if((root != nullptr)){
        root->traverse();
    }
}

template <typename T>
void BPlusTree<T>::ll_traverse(){
    if(root != nullptr){
        ll.clear();
        root->ll_traverse(ll);
    }
}

template <typename T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& entry){
    if(root != nullptr){
        return root->find(entry);
    }
    
}

template <typename T>
T& BPlusTree<T>::get(const T& entry){
    if(root != nullptr){
        return root->get(entry);
    }
}

template <typename T>
bool BPlusTree<T>::contains(const T& entry){
    if(root != nullptr){
        return root->contains(entry);
    }
}

template <typename T>
BPlusTreeNode<T>* BPlusTree<T>::smallestNode(){
    BPlusTreeNode<T> *cur = root;
    while(!cur->leaf){
        cur = this->subset[0];
    }
    return cur;
}

template <typename T>
void BPlusTree<T>::insert(const T& entry){
    //tree empty
    if (root == NULL) { 
        root = new BPlusTreeNode<T>(t, true); 
        root->data[0] = entry;  
        root->data_count = 1;
        size++;
    } 
    else {
        if(contains(entry)&&dups_ok == false){
            return;
        }
        if (root->data_count == 2*t-1) { //root full, make new root
            BPlusTreeNode<T> *s = new BPlusTreeNode<T>(t, false); 

            s->subset[0] = root; 
  
            // split root 
            s->splitChild(0, root); 
  
            int i = 0; 
            if (s->data[0] < entry){
                i++; 
            }
            s->subset[i]->loose_insert(entry); 
  
            root = s; 
        } 
        else{
            root->loose_insert(entry); 
        }
        size++;
    }
    ll_traverse();
    //if(DEBUG)print_ll();
}

template <typename T>
void BPlusTree<T>::remove(const T& entry) 
{ 
    if (!root) 
    { 
        cout << "Tree is empty" << endl; 
        return; 
    } 
  
    //call the remove function on root 
    if(root->remove(entry)) size--; 
  
    //if root node has 0 keys, make its first child the new root 
    //if it has a child, otherwise set root as NULL 
    if (root->data_count==0) 
    { 
        BPlusTreeNode<T> *tmp = root; 
        if (root->leaf) 
            root = NULL; 
        else
            root = root->subset[0]; 
 
        delete tmp; 
    }
    ll_traverse();
    return; 
}

//---------------------------------------------------------------------
//B_PLUS_TREE_NODE
//B_PLUS_TREE_NODE
//B_PLUS_TREE_NODE
//---------------------------------------------------------------------

//UTIL
//UTIL
//UTIL

// Constructor for BTreeNode class 
template <typename T>
BPlusTreeNode<T>::BPlusTreeNode(int t1, bool leaf1) { 
    leaf = leaf1; 
    nextNode = nullptr;
    prevNode = nullptr;

    //data = new T[2*t-1]; 
    //subset = new BTreeNode<T> *[2*t]; 
  
    data_count = 0; 
} 

template <typename T>
void BPlusTreeNode<T>::traverse(){
    int i; 
    //cout << "Data Count: " << data_count << endl;
    for (i = 0; i < data_count; i++) { 
        if (leaf == false) {
            subset[i]->traverse(); 
        }
        cout << data[i] << " "; 
    } 
  
    // last child
    if (leaf == false) {
        subset[i]->traverse(); 
    }
}

template <typename T>
void BPlusTreeNode<T>::print(BPlusTreeNode<T>* cursor){
    queue<BPlusTreeNode*> q;
    q.push(cursor);
    while(!q.empty()){
        BPlusTreeNode* temp = q.front();
        q.pop();
        for(int i = 0; i < temp->data_count;i++){
            cout << temp->data[i] << " " << endl;
        }
        if(!temp->leaf){
            for(int j = 0; j < temp->data_count+1;j++){
            q.push(temp->subset[j]);
            }
        }
    }
}

template <typename T>
void BPlusTreeNode<T>::ll_traverse(vector<BPlusTreeNode<T>*>&ll){
    int i; 
    //cout << "Data Count: " << data_count << endl;
    for (i = 0; i < data_count; i++) { 
        if (leaf == false) {
            subset[i]->ll_traverse(ll); 
        }
         ll.push_back(this);
    } 
  
    // last child
    if (leaf == false) {
        subset[i]->ll_traverse(ll); 
    }
}

template <typename T>
BPlusTreeNode<T>* BPlusTreeNode<T>::find(T entry){ 
    // First greater than or equal to
    int i = 0; 
    while (i < data_count && entry > data[i]) {
        i++; 
    }
    // If found
    if (data[i] == entry) {
        return this; 
    }
  
    // If !found and leaf 
    if (leaf == true) {
        return nullptr;  
    }
    return subset[i]->find(entry); 
} 

template <typename T>
T& BPlusTreeNode<T>::get(const T& entry){ 
    // First greater than or equal to
    int i = 0; 
    while (i < data_count && entry > data[i]) {
        //if(DEBUG)cout << "i: " << i << ", " << entry << endl;
        i++; 
    }
  
    // If found
    if (data[i] == entry) {
        return data[i];
    }

    return subset[i]->get(entry); 
}

template <typename T>
bool BPlusTreeNode<T>::contains(const T& entry){
    if(find(entry) != nullptr){ return true; }
    else return false;
}

//INSERT
//INSERT
//INSERT

template <typename T>
int BPlusTreeNode<T>::greaterThanOrEqualTo(const T& entry){
    int i=0; 
    while (i<data_count && data[i] < entry) 
        ++i; 
    return i;
}

template <typename T>
void BPlusTreeNode<T>::loose_insert(const T& entry){
    // start at last element
    int i = data_count-1; 
  
    if (leaf == true) { 
        while (i >= 0 && data[i] > entry) { 
            data[i+1] = data[i]; 
            i--; 
        } 

        data[i+1] = entry; 
        data_count++;
    } 
    else { 
        // find pos 
        while (i >= 0 && data[i] > entry) 
            i--; 

        // is full? 
        if (subset[i+1]->data_count == 2*t-1) { 
            // split child if full 
            splitChild(i+1, subset[i+1]); 
 
            if (data[i+1] < entry) {
                i++; 
            }
        } 
        subset[i+1]->loose_insert(entry); 
    } 
}

template <typename T>
void BPlusTreeNode<T>::splitChild(int i, BPlusTreeNode *y) { 
    BPlusTreeNode<T> *newRightChild = new BPlusTreeNode<T>(y->t, y->leaf); 
    newRightChild->data_count = t - 1; 
  
    // copy last keys 
    for (int j = 0; j < t-1; j++) {
        newRightChild->data[j] = y->data[j+t]; 
    }
  
    // copy last children
    if (y->leaf == false) { 
        for (int j = 0; j < t; j++) {
            newRightChild->subset[j] = y->subset[j+t]; 
        }
    } 
  
    // update key count 
    y->data_count = t - 1; 
  
    for (int j = data_count; j >= i+1; j--) {
        subset[j+1] = subset[j]; 
    }
  
    // link child 
    subset[i+1] = newRightChild;
    newRightChild->nextNode = y->nextNode;
    y->nextNode = newRightChild;
    

  
    for (int j = data_count-1; j >= i; j--) {
        data[j+1] = data[j]; 
    }
  
    // Copy the middle key of y to this node 
    data[i] = y->data[t-1]; 

    // update key count
    data_count = data_count + 1; 
} 

//REMOVE
//REMOVE
//REMOVE


template <typename T>
bool BPlusTreeNode<T>::remove(const T& entry) { 
    int i = greaterThanOrEqualTo(entry); 
  
    // key present in node
    if (i < data_count && data[i] == entry) {  
        if (leaf) 
            removeIfLeaf(i); 
        else
            removeNotLeaf(i); 
    } 
    else{ 
        if (leaf) { 
            cout << "Key Not Found" << endl;
            return false; 
        } 

        bool last_child_flag = ( (i==data_count)? true : false ); 
  
        // child has shortage 
        if (subset[i]->data_count < t){ 
            fix_shortage(i); 
        }
        //If last child merged, remove on i-1 child, else remove on i child
        if (last_child_flag && i > data_count) {
            subset[i-1]->remove(entry); 
        }
        else{
            subset[i]->remove(entry); 
        }
    }
    return true; 
} 

template <typename T>
void BPlusTreeNode<T>::removeIfLeaf (int i) { 
    // Shift all keys after index left 
    for (int j=i+1; j<data_count; ++j){
        data[j-1] = data[j]; 
    }
    // Reduce key count 
    data_count--; 
  
    return; 
} 

template <typename T>
void BPlusTreeNode<T>::removeNotLeaf(int i) { 
    T k = data[i]; 

    //if child that's before entry has at least t keys, find prev in subset[i]
    //and recursively delete in subset
    if (subset[i]->data_count >= t) { 
        T prev = getPrev(i); 
        data[i] = prev; 
        subset[i]->remove(prev); 
    } 

    //if child in subset[i] has less than t keys, change to subset[i+1]
    //if subset[i+1] has at least t keys, find next entry in subtree
    //and recursively delete in subset[i+1]
    else if  (subset[i+1]->data_count >= t) { 
        T next = getNext(i); 
        data[i] = next; 
        subset[i+1]->remove(next); 
    } 
  
    //if both subset[i] and subset[i+1] have less than t keys, merge and
    //recursively delete from subset[i]
    else{ 
        merge_with_next_subset(i); 
        subset[i]->remove(k); 
    } 
    return; 
} 

template <typename T>
T BPlusTreeNode<T>::getPrev(int i) 
{ 
    //find rightmost leaf 
    BPlusTreeNode *cur=subset[i]; 
    while (!cur->leaf){
        cur = cur->subset[cur->data_count]; 
    }
    //last key 
    return cur->data[cur->data_count-1]; 
} 

template <typename T>
T BPlusTreeNode<T>::getNext(int i) 
{ 
    //start at subset[i+1] and move left until leaf
    BPlusTreeNode *cur = subset[i+1]; 
    while (!cur->leaf) 
        cur = cur->subset[0]; 
  
    // first key 
    return cur->data[0]; 
} 

template <typename T>
void BPlusTreeNode<T>::fix_shortage(int i) {
    //if prev child has too many keys, rotate right
    if (i!=0 && subset[i-1]->data_count>=t) 
        rotate_right(i); 
    //if next child has too many keys, rotate left
    else if (i!=data_count && subset[i+1]->data_count>=t) 
        rotate_left(i); 

    //merge subset[i] with next sibling
    //if subset[i] is last child, merge with prev sibling
    else{ 
        if (i != data_count) 
            merge_with_next_subset(i); 
        else
            merge_with_next_subset(i-1); 
    } 
    return; 
}

template <typename T>
void BPlusTreeNode<T>::rotate_right(int i) 
{ 
    //parent takes subset[i-1]'s last key
    //parent's data[i-1] is inserted to subset[i]

    BPlusTreeNode<T> *child=subset[i]; 
    BPlusTreeNode<T> *sibling=subset[i-1];  
  
    //shift subset[i]
    for (int j=child->data_count-1; j>=0; --j) 
        child->data[j+1] = child->data[j]; 
  
    //if subset[i] != leaf, shift all children
    if (!child->leaf) 
    { 
        for(int j=child->data_count; j>=0; --j) 
            child->subset[j+1] = child->subset[j]; 
    } 
  
    // right child gets data from parent 
    child->data[0] = data[i-1]; 
  
    //sibling's last child becomes subset[i]'s first child
    if(!child->leaf) 
        child->subset[0] = sibling->subset[sibling->data_count]; 

    //move key from sibling to parent
    data[i-1] = sibling->data[sibling->data_count-1]; 
    child->data_count += 1; 
    sibling->data_count -= 1; 
  
    return; 
} 

template<typename T>
void BPlusTreeNode<T>::rotate_left(int i) 
{
    BPlusTreeNode<T> *child=subset[i]; 
    BPlusTreeNode<T> *sibling=subset[i+1]; 
  
    //data[i] inserted as last key into subset[i]
    child->data[(child->data_count)] = data[i]; 
  

    //sibling's first child inserted as last child into subset[i]
    if (!(child->leaf)) 
        child->subset[(child->data_count)+1] = sibling->subset[0]; 
  
    //take key from sibling
    data[i] = sibling->data[0]; 
  
    //shift keys back 
    for (int j=1; j<sibling->data_count; ++j) 
        sibling->data[j-1] = sibling->data[j]; 
  
    //shift children back  
    if (!sibling->leaf) 
    { 
        for(int j=1; j<=sibling->data_count; ++j) 
            sibling->subset[j-1] = sibling->subset[j]; 
    } 

    //update key count
    child->data_count += 1; 
    sibling->data_count -= 1; 
  
    return; 
}

template <typename T>
void BPlusTreeNode<T>::merge_with_next_subset(int i) 
{ 
    BPlusTreeNode *child = subset[i]; 
    BPlusTreeNode *sibling = subset[i+1]; 
  
    //get key from current, insert into subset[i]'s t-1 pos
    child->data[t-1] = data[i]; 
  
    //copy keys from subset[i+1] to subset[i]
    for (int j=0; j<sibling->data_count; ++j) 
        child->data[j+t] = sibling->data[j]; 
  
    //copy children 
    if (!child->leaf) 
    { 
        for(int j=0; j<=sibling->data_count; ++j) 
            child->subset[j+t] = sibling->subset[j]; 
    } 

    //shift keys left to fill empty spot
    for (int j=i+1; j<data_count; ++j) 
        data[j-1] = data[j]; 
  
    //shift children
    for (int j=i+2; j<=data_count; ++j) 
        subset[j-1] = subset[j]; 
  
    //update key count 
    child->data_count += sibling->data_count+1; 
    data_count--; 
  
    //delete sibling post-merge
    delete(sibling); 
    return; 
} 

#endif // B_PLUS_TREE_H