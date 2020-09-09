/*
 * Author: Andrew Lam
 * Project: DEQUE
 * Purpose: Use doubly linked list functions to design a deque
 * Notes:
 */

#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>
#include <cassert>
#include "../list_functions/list_functions.h"

template <typename T>
class deque{
public:
    deque():_front(nullptr),_rear(nullptr){}
    //Big 3
    deque(const deque& other);
    deque& operator=(const deque& rhs);
    ~deque();

    void pushFront(const T& item);
    void pushRear(const T& item);
    T popFront();
    T popRear();
    T getFront();
    T getRear();

    bool empty();
    int getSize();

    friend ostream& operator <<(ostream& outs, const deque& s){
        print_list(s._front, outs);
        return outs;
    }
private:
    int size = 0;
    node<T>* _front;
    node<T>* _rear;
};

// template <typename T>
// deque<T>::deque(){
//     _front = rear = nullptr;
//     size = 0;
// }

//big three functions:
template <typename T>
deque<T>::deque(const deque& other){
    //call a function to copy other into this object.
    _front = copy_list(_front, other._front);
}
template <typename T>
deque<T>& deque<T>::operator=(const deque& rhs){
    //check for self-reference
    //call function to clear this object.
    //call function to copy rhs into this object
    deque<T> temp(rhs);
    swap(temp._front, _front);
    return *this;
}
template <typename T>
deque<T>::~deque(){
    //call function to clear this object.
    size = 0;
    delete_all(_front);
}

template <typename T>
void deque<T>::pushRear(const T& item){
    node<T>* temp = new node<T>;
    if(temp == nullptr){
        cout << "deque: push overflowed" << endl;
        return;
    }
    temp->_item = item;
    temp->_prev = _rear; //
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
void deque<T>::pushFront(const T& item){
    node<T>* temp = new node<T>;
    if(temp == nullptr){
        cout << "deque: push overflowed" << endl;
        return;
    }
    temp->_item = item;
    temp->_prev = nullptr; //
    temp->_next = _front;
    if(_front == nullptr){
        _rear = _front = temp;
    }
    else{
        _front->_prev = temp;
        _front = temp;
    }
    size++;
}
template <typename T>
T deque<T>::popFront(){
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
T deque<T>::popRear(){
    assert(!empty() && "queue: empty object cannot be popped.");
    T tempItem = _rear->_item;
    if(_front == _rear){
        delete _front, _rear;
        _front = _rear = nullptr;
    }
    else{
        node<T>* temp = _rear;
        _rear = _rear->_prev;
        _rear->_next = nullptr;
        delete temp;
    }
    size--;
    return tempItem;
}
template <typename T>
T deque<T>::getFront(){
    assert(!empty() && "queue: top of empty object does not exist.");
    return _front->_item;
}
template <typename T>
T deque<T>::getRear(){
    assert(!empty() && "queue: rear of empty object does not exist.");
    return _rear->_item;
}

template <typename T>
bool deque<T>::empty(){
    return _front==nullptr;
}
template <typename T>
int deque<T>::getSize(){
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




//------------------------------------------------------------------
//  test functions:
//------------------------------------------------------------------
void test_deque_push(){
    cout<<"deque: pushing 0..9 into deque here: "<< endl;
    deque<int> dq;
    for (int i= 0; i<10; i++){
        dq.pushRear(i);
    }
    cout << dq << endl;
    cout << "deque: pushing 99, 101, 123 to front: " << endl;
    dq.pushFront(99);
    dq.pushFront(101);
    dq.pushFront(123);
    cout << dq << endl;
}

void test_deque_pop(){
    cout<<"deque: pushing 0..9 into deque: "<< endl;
    deque<int> dq;
    for (int i= 0; i<10; i++){
        dq.pushRear(i);
    }
    cout << dq << endl;
    cout << "Popped Front [" << dq.popFront() << "]" << " New Deque: " << dq << endl;
    cout << "Popped Rear [" << dq.popRear() << "]" << " New Deque: " << dq << endl;
}
#endif // DEQUE_H