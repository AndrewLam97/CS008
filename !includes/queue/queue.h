/*
 * Author: Andrew Lam
 * Project: Stack and Queue
 * Purpose: Use a linked list to create templated stack and queue classes.
 * Notes: Doubly linked list
 */

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <cassert>
#include "../list_functions/list_functions.h"

template <typename T>
class queue{
public:
    queue():_front(nullptr){}
    //big three functions:
    queue(const queue& other);
    queue& operator=(const queue& rhs);
    ~queue();

    void push(const T& item);
    T pop();
    bool empty();
    T top();
    int getSize();

    friend ostream& operator <<(ostream& outs, const queue& s){
        print_list(s._front, outs);
        return outs;
    }
private:
    int size = 0;
    node<T>* _front;
    node<T>* _rear;
};

//big three functions:
template <typename T>
queue<T>::queue(const queue& other){
    //call a function to copy other into this object.
    _front = copy_list(_front, other._front);
}
template <typename T>
queue<T>& queue<T>::operator=(const queue& rhs){
    //check for self-reference
    //call function to clear this object.
    //call function to copy rhs into this object
    queue<T> temp(rhs);
    swap(temp._front, _front);
    return *this;
}
template <typename T>
queue<T>::~queue(){
    //call function to clear this object.
    size = 0;
    delete_all(_front);
}

template <typename T>
void queue<T>::push(const T& item){
    node<T>* temp = new node<T>;
    if(temp == nullptr){
        cout << "queue: push overflowed" << endl;
        return;
    }
    temp->_item = item;
    temp->_next = nullptr;

    if(_front == nullptr){
        _front = _rear = temp;
    }
    else{
        _rear->_next = temp;
        _rear = temp;
    }
    size++;
}
template <typename T>
T queue<T>::pop(){
    assert(!empty() && "queue: empty object cannot be popped.");
    //call function to remove node at head (_front) and return the item.
    //important to check for single element list (front == rear)
    if(_front == _rear){
        T tempItem = _front->_item;
        delete _front, _rear;
        _front = _rear = nullptr;
        size--;
        return tempItem;
    }
    else{
        size--;
        return delete_head(_front);
    }
}
template <typename T>
bool queue<T>::empty(){
    return _front==nullptr;
}
template <typename T>
int queue<T>::getSize(){
    int count = 0;
    node<T>* temp = new node<T>;
    temp = _front;
    while(temp!=nullptr){
        count++;
        temp = temp->_next;
    }
    size = count;
    return size;
}
template <typename T>
T queue<T>::top(){
    assert(!empty() && "queue: top of empty object does not exist.");
    //grab the first item and return it.
    return _front->_item;
}




//------------------------------------------------------------------
//  test functions:
//------------------------------------------------------------------

void test_queue_push(){
    cout<<"queue: pushing 0..9 into queue here: "<<endl;
    queue<int> q;
    for (int i= 0; i<10; i++){
        q.push(i);
    }
    cout<<q<<endl;
}
void test_queue_pop(){
    cout << "queue: pushing 0..9 into queue and popping once: " << endl;
    queue<int> q;
    for (int i= 0; i<10; i++){
        q.push(i);
    }
    q.pop();
    cout << q << endl;
    cout << "queue: popping previous queue again: " << endl;
    q.pop();
    cout << q << endl;
}
void test_queue_copy(){
    cout << "queue: testing copy constructor: " << endl;
    queue<int> q;
    for(int i = 0; i<5; i++){
        q.push(i);
    }
    queue<int> q1 = q;
    cout << "Origingal queue: " << q << endl;
    cout << "Copied queue: " << q1 << endl;
}
void test_queue_pop_empty(){
    cout<<"queue: popping empty queue"<<endl;
    queue<int> q;
    q.pop();
}
void test_queue_top_empty(){
    cout<<"queue: top of an empty queue."<<endl;
    queue<int> q;
    cout<<q.top()<<endl;;
}
void test_queue_size(){
    queue<int> q;
    for(int i = 0; i<5; i++){
        q.push(i);
    }
    queue<int> q1(q);
    cout << "q: " << q << endl;
    cout << "q size: " << q.getSize() << endl;
    cout << "Popping q..." << endl;
    q.pop();
    cout << "q: " << q << endl;
    cout << "q size: " << q.getSize() << endl;
    cout << "q1: " << q1 << endl;
    cout << "q1 size: " << q1.getSize() << endl;
    q1 = q;
    cout << "Copied q to q1... " << endl; 
    cout << "q1: " << q1 << endl;
    cout << "q1 size: " << q1.getSize();
}
void test_queue(){
    queue<int> q;
    for (int i= 0; i<10; i++){
        q.push(i);
    }
    cout << "q: " << q << endl;
    queue<int>q2(q);
    cout << "q2: " << q2 << endl;
    while (!q2.empty()){
        cout << "{ " << q2.pop() << " } " << q2 << endl;
    }
    cout << "Assigning q back to q2: " <<  endl;
    q2 = q;
    cout << "q: " << q << endl << "q2: " << q2 << endl;
}

#endif // QUEUE_H
