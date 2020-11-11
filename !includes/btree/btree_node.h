#ifndef BTREE_NODE_H
#define BTREE_NODE_H
#include <iostream>
#include <iomanip>
using namespace std;

template <typename T>
class BTreeNode { 
public: 
    BTreeNode(int _t, bool _leaf);   // Constructor 

    bool contains(const T& entry);              //true if entry can be found in the array
    T& get(const T& entry);                     //return a reference to entry in the tree
    //T* find(const T& entry);                    //return a pointer to this key. NULL if not there.
    BTreeNode *find(T entry);

    int size() const;                           //count the number of elements in the tree
    bool empty() const;                         //true if the tree is empty

private:
    int t;
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    int data_count;                                 //number of data elements
    T data[2*t-1];                            //holds the keys
    int child_count;                                //number of children
    BTreeNode<T>* subset[2*t];                 //subtrees
    
    bool leaf;
    bool is_leaf() const {return child_count==0;}   //true if this is a leaf node


    //insert element functions
    void loose_insert(const T& entry);              //allows MAXIMUM+1 data elements in the root
    void splitChild(int i, BTreeNode<T> *y);
    void fix_excess(int i);                         //fix excess of data elements in child i

    //remove element functions:
    void loose_remove(const T& entry);              //allows MINIMUM-1 data elements in the root
    void fix_shortage(int i);                       //fix shortage of data elements in child i

    void remove_biggest(T& entry);                  //remove the biggest child of this tree->entry
    void rotate_left(int i);                        //transfer one element LEFT from child i
    void rotate_right(int i);                       //transfer one element RIGHT from child i
    void merge_with_next_subset(int i);             //merge subset i with subset i+1

    void traverse(BTreeNode<T> *p);                        //traverse tree

friend class BTree; 
}; 

// Constructor for BTreeNode class 
template <typename T>
BTreeNode<T>::BTreeNode(int t1, bool leaf1) 
{ 
    // Copy the given minimum degree and leaf property 
    t = t1; 
    leaf = leaf1; 
  
    // Allocate memory for maximum number of possible keys 
    // and child pointers 
    data = new T[2*t-1]; 
    subset = new BTreeNode<T> *[2*t]; 
  
    // Initialize the number of keys as 0 
    data_count = 0; 
} 

template <typename T>
void BTreeNode<T>::traverse(BTreeNode *p){
    cout << endl;
    int i;
    for (i = 0; i < p->n; i++){
        if (p->is_leaf() == false){
            traverse(p->subset[i]);
        }
        cout << " " << p->data[i];
    }
    if (p->is_leaf() == false){
        traverse(p->subset[i]);
    }
    cout << endl;
}

template <typename T>
void BTreeNode<T>::loose_insert(const T& entry){
    // Initialize index as index of rightmost element 
    int i = data_count-1; 
  
    // If this is a leaf node 
    if (is_leaf() == true) 
    { 
        // The following loop does two things 
        // a) Finds the location of new key to be inserted 
        // b) Moves all greater keys to one place ahead 
        while (i >= 0 && data[i] > entry) 
        { 
            data[i+1] = data[i]; 
            i--; 
        } 
  
        // Insert the new key at found location 
        data[i+1] = entry; 
        data_count++; 
    } 
    else // If this node is not leaf 
    { 
        // Find the child which is going to have the new key 
        while (i >= 0 && data[i] > entry) 
            i--; 
  
        // See if the found child is full 
        if (subset[i+1]->data_count == MAXIMUM) 
        { 
            // If the child is full, then split it 
            splitChild(i+1, subset[i+1]); 
  
            // After split, the middle key of C[i] goes up and 
            // C[i] is splitted into two.  See which of the two 
            // is going to have the new key 
            if (data[i+1] < entry) 
                i++; 
        } 
        subset[i+1]->insertNonFull(entry); 
    } 
}

template <typename T>
void BTreeNode<T>::splitChild(int i, BTreeNode *y) 
{ 
    // Create a new node which is going to store (t-1) keys 
    // of y 
    BTreeNode<T> *z = new BTreeNode<T>(y->t, y->leaf); 
    z->data_count = MAXIMUM - 1; 
  
    // Copy the last (t-1) keys of y to z 
    for (int j = 0; j < t-1; j++) 
        z->keys[j] = y->keys[j+t]; 
  
    // Copy the last t children of y to z 
    if (y->leaf == false) 
    { 
        for (int j = 0; j < t; j++) 
            z->subset[j] = y->subset[j+t]; 
    } 
  
    // Reduce the number of keys in y 
    y->data_count = t - 1; 
  
    // Since this node is going to have a new child, 
    // create space of new child 
    for (int j = data_count; j >= i+1; j--) 
        subset[j+1] = subset[j]; 
  
    // Link the new child to this node 
    subset[i+1] = z; 
  
    // A key of y will move to this node. Find the location of 
    // new key and move all greater keys one space ahead 
    for (int j = data_count-1; j >= i; j--) 
        data[j+1] = data[j]; 
  
    // Copy the middle key of y to this node 
    data[i] = y->data[t-1]; 
  
    // Increment count of keys in this node 
    data_count = data_count + 1; 
} 

// Function to search key k in subtree rooted with this node 
template <typename T>
BTreeNode *BTreeNode<T>::find(T entry)
{ 
    // Find the first key greater than or equal to k 
    int i = 0; 
    while (i < data_count && entry > data[i]) 
        i++; 
  
    // If the found key is equal to k, return this node 
    if (data[i] == entry) 
        return this; 
  
    // If key is not found here and this is a leaf node 
    if (leaf == true) 
        return NULL; 
  
    // Go to the appropriate child 
    return subset[i]->find(entry); 
} 

#endif // BTREE_NODE_H