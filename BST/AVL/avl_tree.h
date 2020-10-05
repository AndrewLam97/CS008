/*
 * Author: Andrew Lam
 * Project: AVL Tree
 * Purpose: AVL Class using avl_functions.h
 * Notes: AVL Tree
 */
#ifndef AVL_TREE
#define AVL_TREE
#include "../../!includes/avl_functions/avl_functions.h"

template <typename T>
class AVL{
public:
    AVL();
    //AVL(const T* sorted_list, int size); //int size = -1
 
 //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
 
    AVL(const AVL<T>& copy_me);
    AVL<T>& operator =(const AVL<T>& rhs);
    ~AVL();
 
 //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
 
    void insert(const T& insert_me);
    void erase(const T& target);
    bool search(const T& target);
    bool search(const T& target, tree_node<T>* & found_ptr);
 
    friend ostream& operator <<(ostream& outs, const AVL<T>& tree){
        //tree_print(root, 0, outs);
    }
    AVL<T>& operator +=(const AVL<T>& rhs);

    tree_node<T>* getRoot(){
        return root;
    }
private:
    tree_node<T>* root;
};

template <typename T> //default ctor
AVL<T>::AVL(){
    root = nullptr;
}

template <typename T> //cctor
AVL<T>::AVL(const AVL<T>& copy_me){
    root = copy_me;
}

template <typename T> //copy swap idiom for assignment
AVL<T>& AVL<T>::operator =(const AVL<T>& rhs){
    AVL<T> temp(rhs);
    swap(temp->root, root);
    return *this;
}

template <typename T>
AVL<T>::~AVL(){
    tree_clear(root);
    root = nullptr;
}

template <typename T>
void AVL<T>::insert(const T& insert_me){
    root = tree_insert(root, insert_me);
}

template <typename T>
void AVL<T>::erase(const T& target){
    tree_erase(root, target);
}

template <typename T>
bool AVL<T>::search(const T& target){
    if(tree_search(root, target) != nullptr) return true;
    else return false;
}

// template <typename T>
// AVL<T>& AVL<T>::operator +=(const AVL<T>& rhs){
//     tree_add(root, rhs);
// }

#endif // AVL_TREE