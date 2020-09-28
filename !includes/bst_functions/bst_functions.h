/*
 * Author: Andrew Lam
 * Project: BST Functions
 * Purpose: Low level functions that perform BST operations.
 * Notes: Binary Search Tree
 */
#ifndef BST_FUNCTIONS_H
#define BST_FUNCTIONS_H
#include <iostream>
#include <algorithm>
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

template <typename T> //recursive
tree_node<T>* tree_search(tree_node<T>* root, const T& target);
template <typename T>
bool tree_search(tree_node<T>* root, const T& target, //if not found, set found_ptr to false and return false
                 tree_node<T>* &found_ptr);

template<typename T> //postorder traversal
void tree_print(tree_node<T>* root, int level=0, ostream& outs=cout);

template<typename T>       //prints detailed info about each node
void tree_print_debug(tree_node<T>* root, int level=0, 
                                          ostream& outs=cout);

template<typename T>
void inorder(tree_node<T>* root); //inorder traversal

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


template <typename T>       // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size);

//--------------------------------------------------------------------
//  definitions:
//--------------------------------------------------------------------
template <typename T>
tree_node<T>* tree_insert(tree_node<T>* &root, const T& insert_me){
    if(root == nullptr){
        tree_node<T>* temp =  new tree_node<T>(insert_me, nullptr, nullptr);
        return temp;
    }
    if(insert_me < root->_item) root->_left = tree_insert(root->_left, insert_me);
    else root->_right = tree_insert(root->_right, insert_me);
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

template<typename T>
void tree_print(tree_node<T>* root, int level=0, ostream& outs=cout){ //postorder
    if(root != nullptr){
        if(root->_left){
            tree_print(root->_left, level+3);
        }
        if(root->right){
            tree_print(root->_right, level+3);
        }
        if(level){
            outs << setw(level) << ' ';
        }
        cout << root->_item << endl;
    }
}

template<typename T>
void inorder(tree_node<T>* root){
    if(root != nullptr){
        inorder(root->_left);
        cout << root->_item << " ";
        inorder(root->_right);
    }
}

template<typename T>       //prints detailed info about each node
void tree_print_debug(tree_node<T>* root, int level=0, ostream& outs=cout){
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
    tree_clear(root->left);
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
#endif // BST_FUNCTIONS_H