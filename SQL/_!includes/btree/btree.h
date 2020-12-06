/*
 * Author: Andrew Lam
 * Project: BTree
 * Purpose: BTree Class
 * Notes: Header File.
 */
#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

template <class T>
class BTree;

template <class T>
class BTreeNode;

template <class T>
class BTreeNode { 
public: 
    BTreeNode(int _t, bool _leaf);              // Constructor 

    bool contains(const T& entry);              //true if entry can be found in the array
    T& get(const T& entry);                     //return a reference to entry in the tree
    //T* find(const T& entry);                  //return a pointer to this key. NULL if not there.
    BTreeNode* find(T entry);
    int greaterThanOrEqualTo(const T& entry);   //return index of first element greater than or equal to entry

    int size() const;                           //count the number of elements in the tree
    bool empty() const;                         //true if the tree is empty

    void dfs_traverse();                        //DFS traversal to pick up and print nodes

    void print(int indent) const;

private:
    static const int t = 3;
    //static const int MINIMUM = 1;
    //static const int MAXIMUM = 2 * MINIMUM;

    int data_count;                            //number of data elements
    T data[2*t-1];                             //holds the keys
    int child_count;                           //number of children
    BTreeNode<T>* subset[2*t];                 //subtrees
    
    bool leaf;
    //bool is_leaf() const {return child_count==0;}   //true if this is a leaf node
    bool is_leaf() const {return leaf;}

    //insert element functions
    void loose_insert(const T& entry);              //allows MAXIMUM+1 data elements in the root
    void splitChild(int i, BTreeNode<T> *y);
    void fix_excess(int i);                         //fix excess of data elements in child i

    //remove element functions:
    void loose_remove(const T& entry);              //allows MINIMUM-1 data elements in the root
    void fix_shortage(int i);                       //fix shortage of data elements in child i

    void remove_biggest(T& entry);                  //remove the biggest child of this tree->entry

    void remove(const T& entry);

    void removeIfLeaf(int i);
    void removeNotLeaf(int i);

    T getPrev(int i);
    T getNext(int i);

    void rotate_left(int i);                        //transfer one element LEFT from child i
    void rotate_right(int i);                       //transfer one element RIGHT from child i
    void merge_with_next_subset(int i);             //merge subset i with subset i+1

    void traverse();                                //traverse tree in ascending order

friend class BTree<T>; 
}; 

template <class T>
class BTree {
public:
    BTree( int _t, bool dups = false);

    //big three:
    //BTree(const BTree<T>& other);
    //~BTree();
    //BTree<T>& operator =(const BTree<T>& RHS);

    void clear_tree();                          //clear this object (delete all nodes etc.)
    void copy_tree(const BTree<T>& other);      //copy other into this object

    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    T& get(const T& entry);                     //return a reference to entry in the tree
    //T* find(const T& entry);                    //return a pointer to this key. NULL if not there.
    BTreeNode<T>* find(T entry);

    void print_tree(int level = 0, ostream &outs=cout) const; //print a readable version of the tree
    friend ostream& operator<<(ostream& outs, const BTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }
    void traverse();                            //traverse tree in ascending order
    void dfs_traverse();                        //traverse tree using DFS

    void print();

private:
    bool dups_ok;                               //true if duplicate keys may be inserted

    BTreeNode<T> *root;

    int t;
    static const int MINIMUM = 2;
    static const int MAXIMUM = 2 * MINIMUM - 1;
};




template <typename T>
void BTree<T>::print(){
    root->dfs_traverse();
}

template <typename T>
void BTree<T>::traverse(){
    if((root != nullptr)){
        root->traverse();
    }
}

template <typename T>
void BTreeNode<T>::print(int indent) const{
    const int EXTRA_INDENTATION = 4;
    size_t i;

    cout << setw(indent) << "";

    for(i = 0; i < data_count; i++){
        cout << data[i] << " ";
    }
    cout << endl;

    for(i = 0; i < child_count; ++i){
        subset[i]->print(indent + EXTRA_INDENTATION);
    }
}

template <typename T>
BTree<T>::BTree(int _t, bool dups){
    this->dups_ok = dups;
    root = nullptr;
    t = _t;
}

template <typename T>
void BTree<T>::insert(const T& entry){
    //tree empty
    if (root == NULL) { 
        root = new BTreeNode<T>(t, true); 
        root->data[0] = entry;  
        root->data_count = 1;   
    } 
    else { 
        if (root->data_count == 2*t-1) { 
            BTreeNode<T> *s = new BTreeNode<T>(t, false); 
  
            s->subset[0] = root; 
  
            // split root 
            s->splitChild(0, root); 
  
            int i = 0; 
            if (s->data[0] < entry) 
                i++; 
            s->subset[i]->loose_insert(entry); 
  
            root = s; 
        } 
        else
            root->loose_insert(entry); 
    } 
}

template <typename T>
T& BTree<T>::get(const T& entry){
    if(root == nullptr){
        // T emptyT = NULL;
        // T &ref = emptyT;
        // return ref;
    }
    else{
        return root->get(entry);
    }
}

template <typename T>
void BTree<T>::remove(const T& entry) 
{ 
    if (!root) 
    { 
        cout << "Empty tree" << endl; 
        return; 
    } 
  
    //call the remove function on root 
    root->remove(entry); 
  
    //if root node has 0 keys, make its first child the new root 
    //if it has a child, otherwise set root as NULL 
    if (root->data_count==0) 
    { 
        BTreeNode<T> *tmp = root; 
        if (root->leaf) 
            root = NULL; 
        else
            root = root->subset[0]; 
 
        delete tmp; 
    } 
    return; 
} 

//---------------------------------------------------------------------------------
//BTreeNode
//BTreeNode
//BTreeNode
//BTreeNode
//BTreeNode
//---------------------------------------------------------------------------------

// template <typename T>
// T* BTree<T>::find(const T& entry){
//     if(root == nullptr){
//         return NULL;
//     }
//     else{
//         return root->find(entry);
//     }
// }

//---------------------------------------------------------------
//     P R I N T  E T C.
//---------------------------------------------------------------
// template <typename T>
// void BTree<T>::print_tree(int level, ostream& outs) const{
//     //1. print the last child (if any)
//     //2. print all the rest of the data and children
//     if (leaf == false) {
//         subset[i]->traverse(); 
//     }
// }

// Constructor for BTreeNode class 
template <typename T>
BTreeNode<T>::BTreeNode(int t1, bool leaf1) { 
    leaf = leaf1; 

    //data = new T[2*t-1]; 
    //subset = new BTreeNode<T> *[2*t]; 
  
    data_count = 0; 
} 

template <typename T>
void BTreeNode<T>::traverse(){
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
        //cout << endl;
    }
    //cout << endl;
}

// template <typename T>
// void BTreeNode<T>::dfs_traverse(){
//     stack<BTreeNode<T>*> stack;
//     stack.push(this);
//     while (!stack.empty())
//     {
//         BTreeNode* current = stack.top();
//         stack.pop();
//         int i;
//         for (i = 0; i < data_count; i++)
//         {
//             if (leaf == false)
//                 stack.push(current->subset[i]); 
//             cout << " " << current->data[i];
//         }
//         if (leaf == false)
//             stack.push(current->subset[i]);
//     }
// }

template <typename T>
void BTreeNode<T>::dfs_traverse(){
    queue<BTreeNode<T>*> q;
    q.push(this);

    while(!q.empty()){
        BTreeNode<T>* r = q.front();
        q.pop();
        int i;
        for (i = 0; i < data_count; i++)
            {
                if (leaf == false)
                    q.push(r->subset[i]); 
                cout << " " << r->data[i];
            }
            if (leaf == false)
                q.push(r->subset[i]);
    }
}

//FIX
template <typename T>
BTreeNode<T>* BTree<T>::find(T entry){
    if(root == nullptr){
        return NULL;
    }
    else{
        return root->find(entry);
    }
}

template <typename T>
int BTreeNode<T>::greaterThanOrEqualTo(const T& entry){
    int i=0; 
    while (i<data_count && data[i] < entry) 
        ++i; 
    return i;
}

template <typename T>
void BTreeNode<T>::loose_insert(const T& entry){
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
void BTreeNode<T>::splitChild(int i, BTreeNode *y) { 
    BTreeNode<T> *z = new BTreeNode<T>(y->t, y->leaf); 
    z->data_count = t - 1; 
  
    // copy last keys 
    for (int j = 0; j < t-1; j++) {
        z->data[j] = y->data[j+t]; 
    }
  
    // copy last children
    if (y->leaf == false) { 
        for (int j = 0; j < t; j++) {
            z->subset[j] = y->subset[j+t]; 
        }
    } 
  
    // update key count 
    y->data_count = t - 1; 
  
    for (int j = data_count; j >= i+1; j--) {
        subset[j+1] = subset[j]; 
    }
  
    // link child 
    subset[i+1] = z; 
  
    for (int j = data_count-1; j >= i; j--) {
        data[j+1] = data[j]; 
    }
  
    // Copy the middle key of y to this node 
    data[i] = y->data[t-1]; 

    // update key count
    data_count = data_count + 1; 
} 

template <typename T>
BTreeNode<T> *BTreeNode<T>::find(T entry){ 
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
        return NULL;  
    }
    return subset[i]->find(entry); 
} 

template <typename T>
T& BTreeNode<T>::get(const T& entry){ 
    // First greater than or equal to
    int i = 0; 
    while (i < data_count && entry > data[i]) {
        //cout << "i: " << i << ", " << entry << endl;
        i++; 
    }
  
    // If found
    if (data[i] == entry) {
        //auto& ref = data[i]; 
        //cout << "final i: " << i << ", final entry: " << entry << endl;
        return data[i];
    }

    // // If !found and leaf 
    // if (leaf == true) 
    //     T emptyT = NULL;
    //     T &ref = emptyT;
    //     return ref;  

    return subset[i]->get(entry); 
} 


//-----------------------------------------------------------------------
//REMOVE
//-----------------------------------------------------------------------
template <typename T>
void BTreeNode<T>::remove(const T& entry) { 
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
            cout << "Key not present" << endl; 
            return; 
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
    return; 
} 

template <typename T>
void BTreeNode<T>::removeIfLeaf (int i) { 
    // Shift all keys after index left 
    for (int j=i+1; j<data_count; ++j){
        data[j-1] = data[j]; 
    }
    // Reduce key count 
    data_count--; 
  
    return; 
} 

template <typename T>
void BTreeNode<T>::removeNotLeaf(int i) { 
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
T BTreeNode<T>::getPrev(int i) 
{ 
    //find rightmost leaf 
    BTreeNode *cur=subset[i]; 
    while (!cur->leaf){
        cur = cur->subset[cur->data_count]; 
    }
    //last key 
    return cur->data[cur->data_count-1]; 
} 

template <typename T>
T BTreeNode<T>::getNext(int i) 
{ 
    //start at subset[i+1] and move left until leaf
    BTreeNode *cur = subset[i+1]; 
    while (!cur->leaf) 
        cur = cur->subset[0]; 
  
    // first key 
    return cur->data[0]; 
} 

template <typename T>
void BTreeNode<T>::fix_shortage(int i) {
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
void BTreeNode<T>::rotate_right(int i) 
{ 
    //parent takes subset[i-1]'s last key
    //parent's data[i-1] is inserted to subset[i]

    BTreeNode<T> *child=subset[i]; 
    BTreeNode<T> *sibling=subset[i-1];  
  
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
void BTreeNode<T>::rotate_left(int i) 
{
    BTreeNode<T> *child=subset[i]; 
    BTreeNode<T> *sibling=subset[i+1]; 
  
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
void BTreeNode<T>::merge_with_next_subset(int i) 
{ 
    BTreeNode *child = subset[i]; 
    BTreeNode *sibling = subset[i+1]; 
  
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
#endif // BTREE_H