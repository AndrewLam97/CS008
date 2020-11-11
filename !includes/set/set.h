/*
 * Author: Andrew Lam
 * Project: Set
 * Purpose: Set Class
 * Notes: Header File.
 */
#ifndef SET_H
#define SET_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

template <class T>
class Set;

template <class T>
class SetNode;

template <class T>
class SetNode { 
public: 
    SetNode(int _t, bool _leaf);              // Constructor 

    bool contains(const T& entry);              //true if entry can be found in the array
    T& get(const T& entry);                     //return a reference to entry in the tree
    //T* find(const T& entry);                  //return a pointer to this key. NULL if not there.
    SetNode *find(T entry);
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
    SetNode<T>* subset[2*t];                   //subSets
    vector<T> elements_vec;                    //for use in union
    
    bool leaf;
    //bool is_leaf() const {return child_count==0;}   //true if this is a leaf node
    bool is_leaf() const {return leaf;}

    //insert element functions
    void loose_insert(const T& entry);              //allows MAXIMUM+1 data elements in the root
    void splitChild(int i, SetNode<T> *y);
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
    vector<T> get_elements();

friend class Set<T>; 
}; 

template <class T>
class Set {
public:
    Set( int _t, bool dups = false);

    //big three:
    //Set(const Set<T>& other);
    //~Set();
    //Set<T>& operator =(const Set<T>& RHS);

    void clear_tree();                          //clear this object (delete all nodes etc.)
    void copy_tree(const Set<T>& other);      //copy other into this object

    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    T& get(const T& entry);                     //return a reference to entry in the tree
    //T* find(const T& entry);                    //return a pointer to this key. NULL if not there.
    SetNode<T>* find(T entry);

    void print_tree(int level = 0, ostream &outs=cout) const; //print a readable version of the tree
    friend ostream& operator<<(ostream& outs, const Set<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }
    void traverse();                            //traverse tree in ascending order
    void dfs_traverse();                        //traverse tree using DFS

    void print();

    void set_union(Set<T> source_set);
    void set_intersect(Set<T> source_set);
    vector<T> get_elements() {return root->get_elements();}
    vector<T> get_vec(){return root->elements_vec;}

private:
    bool dups_ok;                               //true if duplicate keys may be inserted

    SetNode<T> *root;

    int t;
    static const int MINIMUM = 2;
    static const int MAXIMUM = 2 * MINIMUM - 1;
};

template <typename T>
void Set<T>::set_union(Set<T> source_set){
    //cout << "Creating union..." << endl;
    vector<T> source_vec = source_set.get_elements();

    for(auto x : source_vec){
        //cout <<  x << " ";
        insert(x);
    }
    cout << endl;

    // for(T x : source_vec){
    //     cout << "Adding " << x << " to union" << endl;
    //     insert(x);
    // }
}

template <typename T>
void Set<T>::print(){
    root->dfs_traverse();
}


template <typename T>
void SetNode<T>::print(int indent) const{
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
Set<T>::Set(int _t, bool dups){
    this->dups_ok = dups;
    root = nullptr;
    t = _t;
}

template <typename T>
void Set<T>::insert(const T& entry){
    if(find(entry) != NULL){
        cout << entry << " already present in set." << endl;
        return;
    }
    //tree empty
    if (root == NULL) { 
        root = new SetNode<T>(t, true); 
        root->data[0] = entry;  
        root->data_count = 1;   
    } 
    else { 
        if (root->data_count == 2*t-1) { 
            SetNode<T> *s = new SetNode<T>(t, false); 
  
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
T& Set<T>::get(const T& entry){
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
void Set<T>::remove(const T& entry) 
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
        SetNode<T> *tmp = root; 
        if (root->leaf) 
            root = NULL; 
        else
            root = root->subset[0]; 
 
        delete tmp; 
    } 
    return; 
} 

//---------------------------------------------------------------------------------
//SetNode
//SetNode
//SetNode
//SetNode
//SetNode
//---------------------------------------------------------------------------------

// template <typename T>
// T* Set<T>::find(const T& entry){
//     if(root == nullptr){
//         return NULL;
//     }
//     else{
//         return root->find(entry);
//     }
// }

template <typename T>
void Set<T>::traverse(){
    if((root != nullptr)){
        root->traverse();
    }
}

//---------------------------------------------------------------
//     P R I N T  E T C.
//---------------------------------------------------------------
// template <typename T>
// void Set<T>::print_tree(int level, ostream& outs) const{
//     //1. print the last child (if any)
//     //2. print all the rest of the data and children
//     if (leaf == false) {
//         subset[i]->traverse(); 
//     }
// }

// Constructor for SetNode class 
template <typename T>
SetNode<T>::SetNode(int t1, bool leaf1) { 
    leaf = leaf1; 

    //data = new T[2*t-1]; 
    //subset = new SetNode<T> *[2*t]; 
  
    data_count = 0; 
} 

template <typename T>
void SetNode<T>::traverse(){
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

template <typename T>
vector<T> SetNode<T>::get_elements(){
    int i; 
    for (i = 0; i < data_count; i++) { 
        if (leaf == false) {
            subset[i]->traverse(); 
        }
        //cout << "Pushing " << data[i] << " " << endl; 
        elements_vec.push_back(data[i]);
        //cout << "Updated Vec:" << endl;
        // for(auto x: elements_vec){
        //     cout << x << " ";
        // }
    } 
    if (leaf == false) {
        subset[i]->traverse(); 
    }

    return elements_vec;
}


// template <typename T>
// void SetNode<T>::dfs_traverse(){
//     stack<SetNode<T>*> stack;
//     stack.push(this);
//     while (!stack.empty())
//     {
//         SetNode* current = stack.top();
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
void SetNode<T>::dfs_traverse(){
    queue<SetNode<T>*> q;
    q.push(this);

    while(!q.empty()){
        SetNode<T>* r = q.front();
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

template <typename T>
SetNode<T>* Set<T>::find(T entry){
    if(root == nullptr){
        return NULL;
    }
    else{
        return root->find(entry);
    }
}

template <typename T>
int SetNode<T>::greaterThanOrEqualTo(const T& entry){
    int i=0; 
    while (i<data_count && data[i] < entry) 
        ++i; 
    return i;
}

template <typename T>
void SetNode<T>::loose_insert(const T& entry){
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
void SetNode<T>::splitChild(int i, SetNode *y) { 
    SetNode<T> *z = new SetNode<T>(y->t, y->leaf); 
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
SetNode<T> *SetNode<T>::find(T entry){ 
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
T& SetNode<T>::get(const T& entry){ 
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
void SetNode<T>::remove(const T& entry) { 
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
void SetNode<T>::removeIfLeaf (int i) { 
    // Shift all keys after index left 
    for (int j=i+1; j<data_count; ++j){
        data[j-1] = data[j]; 
    }
    // Reduce key count 
    data_count--; 
  
    return; 
} 

template <typename T>
void SetNode<T>::removeNotLeaf(int i) { 
    T k = data[i]; 

    //if child that's before entry has at least t keys, find prev in subset[i]
    //and recursively delete in subset
    if (subset[i]->data_count >= t) { 
        T prev = getPrev(i); 
        data[i] = prev; 
        subset[i]->remove(prev); 
    } 

    //if child in subset[i] has less than t keys, change to subset[i+1]
    //if subset[i+1] has at least t keys, find next entry in suSet
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
T SetNode<T>::getPrev(int i) 
{ 
    //find rightmost leaf 
    SetNode *cur=subset[i]; 
    while (!cur->leaf){
        cur = cur->subset[cur->data_count]; 
    }
    //last key 
    return cur->data[cur->data_count-1]; 
} 

template <typename T>
T SetNode<T>::getNext(int i) 
{ 
    //start at subset[i+1] and move left until leaf
    SetNode *cur = subset[i+1]; 
    while (!cur->leaf) 
        cur = cur->subset[0]; 
  
    // first key 
    return cur->data[0]; 
} 

template <typename T>
void SetNode<T>::fix_shortage(int i) {
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
void SetNode<T>::rotate_right(int i) 
{ 
    //parent takes subset[i-1]'s last key
    //parent's data[i-1] is inserted to subset[i]

    SetNode<T> *child=subset[i]; 
    SetNode<T> *sibling=subset[i-1];  
  
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
void SetNode<T>::rotate_left(int i) 
{
    SetNode<T> *child=subset[i]; 
    SetNode<T> *sibling=subset[i+1]; 
  
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
void SetNode<T>::merge_with_next_subset(int i) 
{ 
    SetNode *child = subset[i]; 
    SetNode *sibling = subset[i+1]; 
  
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
#endif // SET_H