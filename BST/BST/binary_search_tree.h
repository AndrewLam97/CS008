#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE
#include "../../!includes/bst_functions/bst_functions.h"

template <typename T>
class BST{
public:
 BST();
 BST(const T* sorted_list, int size=-1);
 
 //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
 
 BST(const BST<T>& copy_me);
 BST<T>& operator =(const BST<T>& rhs);
 ~BST();
 
 //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
 
 void insert(const T& insert_me);
 void erase(const T& target);
 bool search(const T& target, tree_node<T>* & found_ptr);
 
 friend ostream& operator <<(ostream& outs, const BST<T>& tree);
 BST<T>& operator +=(const BST<T>& rhs);
private:
 tree_node<T>* root;
};

#endif