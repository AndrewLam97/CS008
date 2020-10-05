/*
 * Author: Andrew Lam
 * Project: AVL Tree
 * Purpose: Low level functions that perform AVL operations.
 * Notes: AVL Tree
 */
#ifndef AVL_FUNCTIONS_H
#define AVL_FUNCTIONS_H
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

template <typename T>
struct tree_node
{
    T _item;
    tree_node<T> *_left;
    tree_node<T> *_right;
    int _height;
    int balance_factor()
    {
        //balance factor = height of the right subtree
        //                        - the height of the left subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0
        int heightLeft = -1;
        int heightRight = -1;
        if (this->_left != nullptr)
        {
            heightLeft = _left->_height;
        }
        if (this->_right != nullptr)
        {
            heightRight = _right->_height;
        }
        return (heightRight - heightLeft);
    }

    int height()
    {
        // Height of a node is 1 + height of the "taller" child
        //A leaf node has a height of zero: 1 + max(-1,-1)
        int heightLeft = -1;
        int heightRight = -1;
        if (this->_left != nullptr)
        {
            heightLeft = _left->_height;
        }
        if (this->_right != nullptr)
        {
            heightRight = _right->_height;
        }
        return (max(heightLeft, heightRight) + 1);
    }
    int update_height()
    {
        //set the _height member variable (call height();)
        _height = height();
    }

    tree_node(T item = T(), tree_node *left = NULL,
              tree_node *right = NULL) : _item(item), _left(left), _right(right)
    {
        //don't forget to set the _height.
        update_height();
    }
    friend ostream &operator<<(ostream &outs,
                               const tree_node<T> &t_node)
    {
        outs << "|" << t_node._item << "|";
    }
};

//--------------------------------------------------------------------
//      prototypes
//--------------------------------------------------------------------

template <typename T>
tree_node<T> *tree_insert(tree_node<T> *&root, const T &insert_me);

template <typename T> //recursive/
tree_node<T> *tree_search(tree_node<T> *root, const T &target);
template <typename T>
bool tree_search(tree_node<T> *root, const T &target, //if not found, set found_ptr to false and return false
                 tree_node<T> *&found_ptr);

// template<typename T> //postorder traversal
// void tree_print(tree_node<T>* root, int level=0, ostream& outs=cout);

template <typename T> //prints detailed info about each node
void tree_print_debug(tree_node<T> *root, int level = 0,
                      ostream &outs = cout);

template <typename T>
void inorder_print(tree_node<T> *root); //inorder traversal print

template <typename T>
void inorder(tree_node<T> *root, tree_node<T> *prev);

template <typename T> //clear the tree, postorder traversal (left, right, root)
void tree_clear(tree_node<T> *&root);

template <typename T> //erase target from the tree, 3 cases (0 children,1 child, 2 children)
tree_node<T> *tree_erase(tree_node<T> *&root, const T &target);

template <typename T> //erase rightmost node from the tree
                      // store the item in max_value
void tree_remove_max(tree_node<T> *&root, T &max_value);

template <typename T> //find minimum node in subtree with root
tree_node<T> *minimum_node(tree_node<T> *root);

template <typename T> //return copy of tree pointed to by root
tree_node<T> *tree_copy(tree_node<T> *root);

template <typename T> //Add tree src to dest
void tree_add(tree_node<T> *&dest, const tree_node<T> *src);

template <typename T> //helper function using binary search
tree_node<T> *tree_from_sorted_list_helper(const T *a, int size, int low, int high);
template <typename T> // sorted array -> tree
tree_node<T> *tree_from_sorted_list(const T *a, int size);

// ---------------- ROTATIONS --------------------------
template <typename T>
tree_node<T> *rotate_right(tree_node<T> *&root);
template <typename T>
tree_node<T> *rotate_left(tree_node<T> *&root);
template <typename T>
tree_node<T> *rotate(tree_node<T> *&root); //decide which rotate is needed based on balance factor

//--------------------------------------------------------------------
//  definitions:
//--------------------------------------------------------------------
template <typename T>
tree_node<T> *new_node(T item)
{
    tree_node<T> *temp = new tree_node<T>(item);
    temp->_left = nullptr;
    temp->_right = nullptr;
    return temp;
}

template <typename T>
tree_node<T> *rotate_right(tree_node<T> *&root)
{
    tree_node<T> *temp = root->_left;
    tree_node<T> *temp2 = temp->_right;
    temp->_right = root;
    root->_left = temp2;
    root->update_height();
    temp->update_height();
    return temp;
}

template <typename T>
tree_node<T> *rotate_left(tree_node<T> *&root)
{
    tree_node<T> *temp = root->_right;
    tree_node<T> *temp2 = temp->_left;
    temp->_left = root;
    root->_right = temp2;
    root->update_height();
    temp->update_height();
    return temp;
}

template <typename T> //find minimum node in subtree with root
tree_node<T>* minimum_node(tree_node<T>* root){
    while(root->_left != nullptr){
        root = root->_left;
    }
    return root;
}


template <typename T>
tree_node<T> *tree_insert(tree_node<T> *&root, const T &insert_me)
{
    if (root == NULL){
        return new_node(insert_me);
    }
    if(insert_me < root->_item){
        root->_left = tree_insert(root->_left, insert_me);
    } 
    else if(insert_me > root->_item){
        root->_right = tree_insert(root->_right, insert_me);
    }
    else
        return root;

    root->update_height();
    int bf = root->balance_factor();
    if (bf > 1){
        if (insert_me > root->_right->_item){
            return rotate_left(root);
        }
        else if (insert_me < root->_right->_item){
            root->_right = rotate_right(root->_right);
            return rotate_left(root);
        }
    }
    if (bf < -1){
        if (insert_me < root->_left->_item){
            return rotate_right(root);
        }
        else if (insert_me > root->_left->_item){
            root->_left = rotate_left(root->_right);
            return rotate_right(root);
        }
    }
    return root;
}

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target){
    if(root == nullptr) {
        return nullptr;
    }
    if(root->_item == target){ //base case when root == target or null
        return root;
    }
    else if(root->_item > target){ //root smaller than target
        return tree_search(root->_left, target);
    }
    else{ //root larger than target
        return tree_search(root->_right, target);
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

template <typename T>
tree_node<T>* tree_erase(tree_node<T>*& root, const T& target){  // Find the node and delete it
  if (root == nullptr)
    return root;
  if (target < root->_item)
    root->_left = tree_erase(root->_left, target);
  else if (target > root->_item)
    root->_right = tree_erase(root->_right, target);
  else {
    if ((root->_left == nullptr) || (root->_right == nullptr)) {
      tree_node<T>* temp = root->_left ? root->_left : root->_right;
      if (temp == nullptr) {
        temp = root;
        root = nullptr;
      } else
        *root = *temp;
      delete temp;
    } else {
      tree_node<T>* temp = minimum_node(root->_right);
      root->_item = temp->_item;
      root->_right = tree_erase(root->_right, temp->_item);
    }
  }

  if (root == nullptr)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->update_height();
  int bf = root->balance_factor();
  if (bf > 1) {
    if (root->_left->balance_factor() >= 0) {
      return rotate_right(root);
    } else {
      root->_left = rotate_left(root->_left);
      return rotate_right(root);
    }
  }
  if (bf < -1) {
    if (root->_right->balance_factor() <= 0) {
      return rotate_left(root);
    } else {
      root->_right = rotate_right(root->_right);
      return rotate_left(root);
    }
  }
  return root;
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

template <typename T>
void printTree(tree_node<T> *root, string indent, bool last) {
  if (root != nullptr) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    cout << root->key << endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}

#endif // AVL_FUNCTIONS_H