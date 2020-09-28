/*
 * Author: Andrew Lam
 * Project: BST Functions
 * Purpose: Low level functions that perform BST operations.
 * Notes: Binary Search Tree
 */
#ifndef BST_FUNCTIONS_H
#define BST_FUNCTIONS_H
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
struct tree_node{
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;
    int balance_factor(){
        //balance factor = height of the right subtree 
        //                        - the height of the left subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0
        int heightLeft = -1;
        int heightRight = -1;
        if(this->_left != nullptr){
            heightLeft = _left->_height;
        }
        if(this->_left != nullptr){
            heightRight = _right->_height;
        }
        return (heightRight - heightLeft);
    }

    int height(){
        // Height of a node is 1 + height of the "taller" child
        //A leaf node has a height of zero: 1 + max(-1,-1)
        int heightLeft = -1;
        int heightRight = -1;
        if(this->_left != nullptr){
            heightLeft = _left->_height;
        }
        if(this->_left != nullptr){
            heightRight = _right->_height;
        }
        return (max(heightLeft, heightRight)+1);
    }
    int update_height(){
        //set the _height member variable (call height();)
        _height = height();
    }

    tree_node(T item=T(), tree_node* left=NULL, 
                          tree_node* right=NULL):
                    _item(item), _left(left), _right(right)
    {
        //don't forget to set the _height.
        update_height();
    }
    friend ostream& operator <<(ostream& outs, 
                                const tree_node<T>& t_node){
        outs<<"|"<<t_node._item<<"|";
    }
};

//--------------------------------------------------------------------
//      prototypes
//--------------------------------------------------------------------

template <typename T>
tree_node<T>* tree_insert(tree_node<T>* &root, const T& insert_me);

template <typename T> //recursive/
tree_node<T>* tree_search(tree_node<T>* root, const T& target);
template <typename T>
bool tree_search(tree_node<T>* root, const T& target, //if not found, set found_ptr to false and return false
                 tree_node<T>* &found_ptr);

// template<typename T> //postorder traversal
// void tree_print(tree_node<T>* root, int level=0, ostream& outs=cout);

template<typename T>       //prints detailed info about each node
void tree_print_debug(tree_node<T>* root, int level=0, 
                                          ostream& outs=cout);

template<typename T>
void inorder_print(tree_node<T>* root); //inorder traversal print

template <typename T>
void inorder(tree_node<T>* root, tree_node<T>* prev);

template <typename T>       //clear the tree, postorder traversal (left, right, root)
void tree_clear(tree_node<T>* &root);

template <typename T>       //erase target from the tree, 3 cases (0 children,1 child, 2 children)
bool tree_erase(tree_node<T>*& root, const T& target);

template <typename T>       //erase rightmost node from the tree
                            // store the item in max_value
void tree_remove_max(tree_node<T>* &root, T& max_value);

template <typename T> //find minimum node in subtree with root
tree_node<T>* minimum_node(tree_node<T>* root);

template <typename T>       //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root);

template <typename T>       //Add tree src to dest
void tree_add(tree_node<T>* & dest, const tree_node<T>* src);

template <typename T> //helper function using binary search
tree_node<T>* tree_from_sorted_list_helper(const T* a, int size, int low, int high);
template <typename T>       // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size);





//--------------------------------------------------------------------
//  definitions:
//--------------------------------------------------------------------
template <typename T>
tree_node<T>* new_node(T item){
    tree_node<T>* temp = new tree_node<T>(item);
    temp->_left = nullptr;
    temp->_right = nullptr;
    return temp;
}

template <typename T>
tree_node<T>* tree_insert(tree_node<T>* &root, const T& insert_me){
    if(root == nullptr){
        return new_node(insert_me);
    }
    if(insert_me < root->_item){
        root->_left = tree_insert(root->_left, insert_me);
    } 
    else{
        root->_right = tree_insert(root->_right, insert_me);
    }
    return root;
}

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target){
    if(root->_item == target || root==nullptr){ //base case when root == target or null
        return root;
    }
    else if(root->_item > target){ //root smaller than target
        return tree_search(root->_left, target);
    }
    else{ //root larger than target
        return tree_search(root->_right, target);
    }
}

template <typename T>
bool tree_search(tree_node<T>* root, const T& target, tree_node<T>* &found_ptr){
    // found_ptr = tree_search(root, target); 
    // if(found_ptr == nullptr){
    //     return false;
    // }
    // else{
    //     return true;
    // }
    while (root != nullptr && root->_item != target)
	{
		// update parent node as current node
		found_ptr = root;

		// if given key is less than the current node, go to left subtree
		// else go to right subtree
		if (target < root->_item)
			root = root->_left;
		else
			root = root->_right;
	}
}

// template<typename T>
// void tree_print(tree_node<T>* root, int level, ostream& outs){ //postorder
//     if(root != nullptr){
//         if(root->_left){
//             tree_print(root->_left, level+3);
//         }
//         if(root->_right){
//             tree_print(root->_right, level+3);
//         }
//         if(level){
//             outs << setw(level) << ' ';
//         }
//         cout << root->_item << endl;
//     }
// }

int COUNT = 10;
template <typename T>
void tree_print_util(tree_node<T>* root, int space){
    if(root == nullptr){
        return;
    }
    space += COUNT;
    tree_print_util(root->_right, space);
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<root->_item<<endl;
    tree_print_util(root->_left, space); 
}

template <typename T>
void tree_print(tree_node<T>* root){
    tree_print_util(root, 0);
}

template<typename T>
void inorder_print(tree_node<T>* root){
    if(root != nullptr){
        inorder_print(root->_left);
        cout << root->_item << " ";
        inorder_print(root->_right);
    }
}

template<typename T>       //prints detailed info about each node
void tree_print_debug(tree_node<T>* root, int level, ostream& outs){
    if(root != nullptr){
        if(root->_left){
            tree_print(root->_left, level+3);
        }
        if(root->right){
            tree_print(root->_right, level+3);
        }
        if(level){
            outs << setw(level) << 'l:' << level << ' ';
        }
        cout << root->_item << endl;
    }
}

template <typename T>       //clear the tree, postorder traversal (left, right, root), *doesn't set root to null*
void tree_clear(tree_node<T>* &root){
    if(root == nullptr){
        return;
    }
    tree_clear(root->_left);
    tree_clear(root->_right);
    delete root;
}

template <typename T>       //erase target from the tree, 3 cases (0 children,1 child, 2 children)
bool tree_erase(tree_node<T>*& root, const T& target){
    tree_node<T>* parent = nullptr;
    tree_node<T>* current = root;

    tree_search(current, target, parent);
    if(current == nullptr) return false;

    if(current->_left == nullptr && current->_right == nullptr){ //current = leaf
        if(current != root){
            if(parent->_left == current) parent->_left = nullptr;
            else parent->_right = nullptr;
        }
        else root = nullptr;
        delete current;
    }
    else if(current->_left && current->_right){
        tree_node<T>* temp = minimum_node(current->_right);
        T tempItem = temp->_item;
        tree_erase(root, temp->_item);
        current->_item = tempItem;
    }
    else{
        tree_node<T>* temp = (current->_left) ? current->_left : current->_right;
        if(current != root){
            if(current == parent->_left) parent->_left = temp;
            else parent->_right = temp;
        }
        else root = temp;
        delete current;
    }
}

template <typename T> //find minimum node in subtree with root
tree_node<T>* minimum_node(tree_node<T>* root){
    while(root->_left != nullptr){
        root = root->_left;
    }
    return root;
}

template <typename T>       // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size){
    return tree_from_sorted_list_helper(a, size, 0, size-1);
}

template <typename T> //helper function using binary search
tree_node<T>* tree_from_sorted_list_helper(const T* a, int size, int low, int high){
    if(low <= high){
        int mid = ((low + high) / 2) + low;
        tree_node<T>* root = new tree_node<T>(a[mid]);
        root->_left = tree_from_sorted_list_helper(a, low, mid-1);
        root->_right = tree_from_sorted_list_helper(a, mid+1, high);
        return root;
    }
    return nullptr;
}

template <typename T>       //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root){
    tree_node<T>* temp;
    if(root != nullptr){
        tree_node<T>* temp = new tree_node<T>;
        temp->_item = root->_item;
        temp->_left = tree_copy(root->_left);
        temp->_right = tree_copy(root->_right);
    }
    else return nullptr;
    return temp;
}

template <typename T>
void inorder(tree_node<T>* root, tree_node<T>* prev){
    if(root == nullptr) return;
    inorder(root->_left, prev);
    prev->_left = nullptr;
    prev->_right = root;
    prev = root;
    inorder(root->_right, prev);
}

template <typename T>
tree_node<T>* flatten(tree_node<T>* parent){
    tree_node<T>* temp = new tree_node<T>(-1);
    tree_node<T>* prev = temp;

    inorder(parent, prev);

    prev->_left = nullptr;
    prev->_right = nullptr;
    tree_node<T>* res = temp->_right;
    delete temp;
    return res;
}

template <typename T>
vector<T> mergesort_vectors(vector<T> first, vector<T> second){
    vector<T> mergedVec = first;
    mergedVec.insert(mergedVec.end(), second.begin(), second.end());
    sort(mergedVec);
    return mergedVec;
}

template <typename T>       //Add tree src to dest
void tree_add(tree_node<T>* & dest, const tree_node<T>* src){
    vector<T> dVec;
    vector<T> sVec;
    tree_node<T>* dWalker = dest;
    tree_node<T>* sWalker = src;

    while(dWalker != nullptr){
        dVec.push_back(dWalker->_item);
        dWalker = dWalker->_right;
    }
    while(sWalker != nullptr){
        sVec.push_back(sWalker->_item);
        sWalker = sWalker->_right;
    }
    vector<T> mergedVec = mergesort_vectors(dWalker, sWalker);
    tree_node<T>* ret = new tree_node<T>;
    for(auto i:mergedVec){
        tree_insert(ret,i);
    }
}
#endif // BST_FUNCTIONS_H