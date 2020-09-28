#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE
#include "../../!includes/bst_functions/bst_functions.h"

template <typename T>
class BST{
public:
    BST();
    BST(const T* sorted_list, int size); //int size = -1
 
 //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
 
    BST(const BST<T>& copy_me);
    BST<T>& operator =(const BST<T>& rhs);
    ~BST();
 
 //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
 
    void insert(const T& insert_me);
    void erase(const T& target);
    bool search(const T& target);
    bool search(const T& target, tree_node<T>* & found_ptr);
 
    friend ostream& operator <<(ostream& outs, const BST<T>& tree){
        //tree_print(root, 0, outs);
    }
    BST<T>& operator +=(const BST<T>& rhs);

    tree_node<T>* getRoot(){
        return root;
    }
private:
    tree_node<T>* root;
};

template <typename T> //default ctor
BST<T>::BST(){
    root = nullptr;
}

template <typename T> //sorted list ctor
BST<T>::BST(const T* sorted_list, int size){
    root = tree_from_sorted_list(sorted_list, size);
}

template <typename T> //cctor
BST<T>::BST(const BST<T>& copy_me){
    root = copy_me;
}

template <typename T> //copy swap idiom for assignment
BST<T>& BST<T>::operator =(const BST<T>& rhs){
    BST<T> temp(rhs);
    swap(temp->root, root);
    return *this;
}

template <typename T>
BST<T>::~BST(){
    tree_clear(root);
    root = nullptr;
}

template <typename T>
void BST<T>::insert(const T& insert_me){
    root = tree_insert(root, insert_me);
}

template <typename T>
void BST<T>::erase(const T& target){
    tree_erase(root, target);
}

// template <typename T>
// bool BST<T>::search(const T& target, tree_node<T>* & found_ptr){
//     return tree_search(root, target, found_ptr);
// }

template <typename T>
bool BST<T>::search(const T& target){
    if(tree_search(root, target) != nullptr) return true;
    else return false;
}

template <typename T>
BST<T>& BST<T>::operator +=(const BST<T>& rhs){
    tree_add(root, rhs);
}
#endif // BINARY_SEARCH_TREE