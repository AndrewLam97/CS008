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
    // node<T>* walker = _front;
    // while(walker->_next == nullptr){
    //     walker = walker->_next;
    // }
    // _rear = walker;
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
        //delete _front, _rear;
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
    cout<<"testing deque pop: pushing 0..9 into deque: "<< endl;
    deque<int> dq;
    for (int i= 0; i<10; i++){
        dq.pushRear(i);
    }
    cout << dq << endl;
    while (!dq.empty()){
        cout << "{ " << dq.popRear() << " } " << dq << endl;
    }


}

void test_deque_copy(){
    cout << "deque: testing copy constructor: " << endl;
    deque<int> dq;
    for(int i = 0; i<5; i++){
        dq.pushRear(i);
    }
    deque<int> dq1 = dq;
    cout << "Origingal deque: " << dq << endl;
    cout << "Copied deque: " << dq1 << endl;
}
void test_deque_pop_empty(){
    cout<<"deque: popping empty deque"<<endl;
    deque<int> dq;
    dq.popRear();
}
void test_deque_getFront_empty(){
    cout<<"deque: top of an empty deque."<<endl;
    deque<int> dq;
    cout<<dq.getFront()<<endl;;
}
void test_deque_size(){
    deque<int> dq;
    for(int i = 0; i<5; i++){
        dq.pushRear(i);
    }
    deque<int> dq1(dq);
    cout << "dq: " << dq << endl;
    cout << "dq size: " << dq.getSize() << endl;
    cout << "Popping dq..." << endl;
    dq.popFront();
    cout << "dq: " << dq << endl;
    cout << "dq size: " << dq.getSize() << endl;
    cout << "dq1: " << dq1 << endl;
    cout << "dq1 size: " << dq1.getSize() << endl;
    dq1 = dq;
    cout << "Copied dq to dq1... " << endl; 
    cout << "dq1: " << dq1 << endl;
    cout << "dq1 size: " << dq1.getSize();
}
void test_deque(){
    deque<int> dq;
    cout << "Pushing 1..9 to Rear..." << endl;
    for(int i = 1; i<10; i++){
        dq.pushRear(i);
    }
    cout << dq << endl;
    cout << "Pushing 0 to Front" << endl;
    dq.pushFront(0);
    cout << dq << endl;

    cout << "Creating dq1 from dq using cctor..." << endl;
    deque<int> dq1(dq);
    cout << "dq: " << dq << endl;
    cout << "dq1: " << dq1 << endl;

    cout << "Popping dq from Rear..." << endl;
    while (!dq.empty()){
        cout << "{ " << dq.popRear() << " } " << dq << endl;
    }

    cout << "Assigning dq1 back to dq: " <<  endl;
    dq = dq1;
    cout << "dq: " << dq << endl;

    cout << "Popping dq1 from Front..." << endl;
    while (!dq1.empty()){
        cout << "{ " << dq1.popFront() << " } " << dq1 << endl;
    }

   
}
#endif // DEQUE_H