/*
 * Author: Andrew Lam
 * Project: Stack and Queue
 * Purpose: Use a linked list to create templated stack and queue classes.
 * Notes: Doubly linked list
 */

#ifndef MY_STACK_H
#define MY_STACK_H
#include <iostream>
#include <cassert>
#include "../list_functions/list_functions.h"

template <typename T>
class stack{
public:
    stack():_top(nullptr){}
    //big three functions:
    stack(const stack& other);
    stack& operator=(const stack& rhs);
    ~stack();

    void push(const T& item);
    T pop();
    bool empty();
    T top();

    friend ostream& operator <<(ostream& outs, const stack& s){
        print_list(s._top, outs);
        return outs;
    }
private:
    node<T>* _top;
};

//big three functions:
template <typename T>
stack<T>::stack(const stack& other){
    _top = copy_list(_top, other._top);
}
template <typename T>
stack<T>& stack<T>::operator=(const stack& rhs){
    //check for self-reference
    //call function to clear this object.
    //call function to copy rhs into this object
    //using copy swap 
    stack<T> temp(rhs);
    swap(temp._top, _top);
    return *this;
}
template <typename T>
stack<T>::~stack(){
    //call function to clear this object.
    delete_all(_top);
}

template <typename T>
void stack<T>::push(const T& item){
    insert_head(_top, item);
}
template <typename T>
T stack<T>::pop(){
    assert(!empty() && "stack: empty object cannot be popped.");
    //call function to remove node at head (_top) and return the item.
    return delete_head(_top);
}
template <typename T>
bool stack<T>::empty(){
    return _top==nullptr;
}
template <typename T>
T stack<T>::top(){
    assert(!empty() && "stack: top of empty object does not exist.");
    //grab the first item and return it.
    return _top->_item;
}

//------------------------------------------------------------------
//  test functions:
//------------------------------------------------------------------

void test_stack_push(){
    cout<<"stack: pushing 0..9 into stack here: "<<endl;
    stack<int> s;
    for (int i= 0; i<10; i++){
        s.push(i);
    }
    cout<<s<<endl;
}
void test_stack_pop_empty(){
    cout<<"stack: popping empty stack"<<endl;
    stack<int> s;
    s.pop();
}
void test_stack_top_empty(){
    cout<<"stack: top of an empty stack."<<endl;
    stack<int> s;
    cout<<s.top()<<endl;;
}
void test_stack_cctor(){
    cout << ">>Testing stack cctor: pushing 0..9 into stack and copying: " << endl;
    stack<int> s1;
    for (int i= 0; i<10; i++){
        s1.push(i);
    }
    cout << "s1: " << s1 << endl;
    stack<int>s2(s1);
    cout << "s2: " << s2 << endl;
}
void test_stack_assignment(){

    cout << ">>Testing stack assignment operator: pushing 0..9 into s1: " << endl;
    stack<int> s1;
    for (int i= 0; i<10; i++){
        s1.push(i);
    }
    cout << "s1: " << s1 << endl;
    cout << "Creating s2: pushing 5..0" << endl;
    stack<int> s2;
    for (int i= 5; i>0; i--){
        s2.push(i);
    }
    cout << "s2: " << s2 << endl;
    cout << "Assigning s2 to s1 (s1 = s2)" << endl;
    s1 = s2;
    cout << "s1: " << s1 << endl;
}
void test_stack(){
    stack<int> s;
    for (int i= 0; i<10; i++){
        s.push(i);
    }
    cout << "s: " << s << endl;
    stack<int>s2(s);
    cout << "s2: " << s2 << endl;
    while (!s2.empty()){
        cout << "{ " << s2.pop() << " } " << s2 << endl;
    }
    cout << "Assigning s back to s2: " <<  endl;
    s2 = s;
    cout << "s: " << s << endl << "s2: " << s2 << endl;
}

#endif // MY_STACK_H
