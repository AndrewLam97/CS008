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

template <typename T> //skip for now
void tree_insert(tree_node<T>* &root, const T& insert_me);

template <typename T> //recursive
tree_node<T>* tree_search(tree_node<T>* root, const T& target);
template <typename T>
bool tree_search(tree_node<T>* root, const T& target, //if not found, set found_ptr to false and return false
                 tree_node<T>* &found_ptr);

template<typename T>
void tree_print(tree_node<T>* root, int level=0, 
                                    ostream& outs=cout);

template<typename T>       //prints detailed info about each node
void tree_print_debug(tree_node<T>* root, int level=0, 
                                          ostream& outs=cout);

template <typename T>       //clear the tree, postorder traversal (left, right, root)
void tree_clear(tree_node<T>* &root);

template <typename T>       //erase target from the tree, 3 cases (0 children,1 child, 2 children)
bool tree_erase(tree_node<T>*& root, const T& target);

template <typename T>       //erase rightmost node from the tree
                            // store the item in max_value
void tree_remove_max(tree_node<T>* &root, T& max_value);

template <typename T>       //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root);

template <typename T>       //Add tree src to dest
void tree_add(tree_node<T>* & dest, const tree_node<T>* src);


template <typename T>       // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size);

//--------------------------------------------------------------------
//  definitions:
//--------------------------------------------------------------------


#endif // BST_FUNCTIONS_H