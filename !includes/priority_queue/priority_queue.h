/*
 * Author: Andrew Lam
 * Project: Priority Queue
 * Purpose: Priority Queue Header File
 * Notes: Based upon heap
 */
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../heap/heap.h"
#include <iostream>
using namespace std;

template <typename T>
struct info{
    T item;
    int priority;
    
    info(){
        this->item = NULL;
        this->priority = -1;
    }
    info(T i, int p){
        this->item = i;
        this->priority = p;
    }
    
    friend ostream& operator <<(ostream& outs, const info<T>& print_me);
    
    friend bool operator <(const info<T>& lhs, const info<T>& rhs);
};

template <typename T>
class PQueue
{
public:
    PQueue();

    bool insert(const T& value, int p); //insert value and priority pair
    bool insert(const info<T>& insert_me); //insert info struct
    T Pop(); //pop priority queue, return top item 

    bool is_empty() const;
    int size() const; //return priority queue size
    void print_tree(); //repeatedly prints and pops priority queue
    friend ostream& operator <<(ostream& outs, const PQueue<T>& print_me);

private:
    MaxHeap<int,T> heap;
};

template <typename T>
PQueue<T>::PQueue(){}

template <typename T>
bool PQueue<T>::insert(const T& value, int p){
    heap.insert(p, value);
    if(heap.getMax() == value) return true;
    else return false;
}

template <typename T>
bool PQueue<T>::insert(const info<T>& insert_me){
    heap.insert(insert_me.priority, insert_me.item);
    if(heap.getMax() == insert_me.item) return true;
    else return false;
}

template <typename T>
T PQueue<T>::Pop(){
    T temp = heap.getMax();
    heap.popMax();
    return temp;
}

template <typename T>
bool PQueue<T>::is_empty() const{
    return heap.isEmpty();
}

template <typename T>
int PQueue<T>::size() const{
    return heap.getSize();
}

template <typename T>
void PQueue<T>::print_tree(){
    while (!heap.isEmpty())
    {
        cout << heap.getMax() << endl;
        heap.popMax();
    }
}

#endif // PRIORITY_QUEUE_H