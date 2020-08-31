/*
 * Author: Andrew Lam
 * Project: List Functions
 * Purpose: Low level functions that perform linked list operations.
 * Notes: Doubly linked list
 */

#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H

#include <iostream>
using namespace std;

template <typename T>
struct node{
    T _item;
    node<T>* _prev;
    node<T>* _next;
    node(const T& item=T(),
         node<T>* prev = nullptr,node<T>* next=nullptr):_item(item), _prev(prev), _next(next){}
    friend ostream& operator <<(ostream& outs, const node<T>& n){
        outs<<"["<<n._item<<"]->";
        return outs;
    }
};

//--------------------------------------------------------------------
//      prototypes
//--------------------------------------------------------------------
//initializes head to NULL
template <class T>
node<T>* init_head(node<T>* &head);

//deletes all the nodes in the list
template<class T>
void delete_all(node<T>*&head);

//true if head is NULL, false otherwise.
template <class T>
bool empty(const node<T>* head);

//makes a copy of the list, returns a pointer to the last node:
//use two walkers (source and dest), insert after walkerdest,
//increment both walkers till walkersource arrives at NULL.
//return last element of copy list(rear = copylist(front, otherfront))
template <class T>
node<T>* copy_list(node<T>* dest, const node<T>* src);

//insert at the beginning of the list:
template <class T>
node<T>* insert_head(node<T>*& head, const T& item);

//implement later, call insert after on the prev node,
//check that prev node exists
//insert_before:
template <class T>
node<T>* insert_before(node<T>* &head, node<T> before, const T& item);

//insert_after: if after is NULL, inserts at head
template <class T>
node<T>* insert_after(node<T>* &head, node<T>* after, const T& item);

//delete the node at the head of the list, return the item:
template <class T>
T delete_head(node<T>* &head);

//print the list and return outs
template<typename T>
ostream& print_list(node<T>* head, ostream& outs=cout);



//--------------------------------------------------------------------
//  definitions:
//--------------------------------------------------------------------
template <class T>
node<T>* init_head(node<T>* &head){
    head->_next = nullptr;
    head->_prev = nullptr;
    head = nullptr;
}

template<class T>
void delete_all(node<T>*&head){
    while(head != nullptr){
        node<T>* temp = head;
        head = head->_next;
        delete temp;
    }
}

template <class T>
bool empty(const node<T>* head){
    return (head == nullptr);
}

template <class T>
node<T>* copy_list(node<T>* dest, const node<T>* src){
    node<T>* walkerDest = new node<T>(src->_item);
    dest = walkerDest;
    node<T>* walkerSrc = new node<T>;
    walkerSrc->_next = src->_next;
    while(walkerSrc->_next != nullptr){
        insert_after(dest, walkerDest, walkerSrc->_next->_item);
        walkerDest = walkerDest->_next;
        walkerSrc = walkerSrc->_next;
    }
    return dest;
}

template<typename T>
node<T>* insert_head(node<T>*& head, const T& item){
    //three steps:
    //1. make a new node:
    node<T>* temp = new node<T>(item);
    //2. point this node to where head is pointing:
    temp->_prev = nullptr;
    temp->_next = head;
    //3. point head to this new node:
    if (head != nullptr){
        head->_prev = temp;
    }
    head = temp;
    
    return head;
}

template <class T>
node<T>* insert_after(node<T>* &head, node<T>* after, const T& item){
    if(after == nullptr){
        insert_head(head, item);
    }
    else{
        node<T>* temp = new node<T>(item);
        temp->_next = after->_next;
        after->_next = temp;
        temp->_prev = after;
        if(temp->_next != nullptr){
            temp->_next->_prev = temp;
        }
    }
}

template <class T>
T delete_head(node<T>* &head){
    T item = head->_item;
    node<T>* temp = head;
    // head->_next->_prev = nullptr;
    // head = head->_next;
    // init_head(temp);
    // delete temp;
    head = temp->_next;
    if(temp->_next != nullptr){
        temp->_next->_prev = temp->_prev;
    }
    if(temp->_prev != nullptr){
        temp->_prev->_next = temp->_next;
    }
    delete temp;

    return item;
}

template<typename T>
ostream& print_list(node<T>* head, ostream& outs){
    //for (int i=0; i<10; i++){}
    //h->>[ ]->[ ]->[ ]->|||
    //outs<<"H->";
    for (node<T>* walker = head;
         walker != nullptr;
         walker=walker->_next){
        outs<<*walker;
    }
    outs<<"|||";
    return outs;
}



//--------------------------------------------------------------------
//  test functions:
//--------------------------------------------------------------------
void test_node(){
    cout<<">>Testing node: printing three nodes: "<<endl;
    node<int> n1;           //0, nullptr
    node<int> n2(5);        //5, nullptr
    node<int> n3(6, &n1);   //6, address of n1
    cout<<n1<<n2<<n3<<endl;
}
void test_insert_head(){
    cout<<">>Testing insert_head: inserting 0..9 at head and printing: "<<endl;
    node<int>* head = nullptr;
    for (int i=0; i<10; i++){
        insert_head(head, i);
    }
    print_list(head);
    cout<<endl;
}
void test_delete_all(){
    cout <<  ">>Testing delete_all:" << endl;
    node<int>* head = new node<int>;
    init_head(head);
    for (int i=0; i<10; i++){
        insert_head(head, i);
    }
    print_list(head);
    cout << endl << "Deleting all..." << endl;
    delete_all(head);
    print_list(head);
    cout << endl;
}
void test_empty(){
    cout << ">>Testing empty:" << endl;
    node<int>* head = new node<int>;
    init_head(head);
    cout << "Empty? : " << empty(head) << endl;
    cout << "Inserting head..." << endl;
    insert_head(head, 99);
    cout << "Empty? : " << empty(head) << endl;
}
void test_insert_after(){
    cout << ">>Testing insert after: " << endl;
    node<int>* head = new node<int>;
    init_head(head);
    for (int i=0; i<10; i++){
        insert_head(head, i);
    }
    print_list(head) << endl;
    cout << "Inserting 99 after 4 nodes..." << endl;
    node<int>* walker = head;
    for(int i = 0; i < 3; i++){
        walker = walker->_next;
    }
    insert_after(head, walker, 99);
    print_list(head) << endl;
    cout<< "Inserting 42 after nullptr..." << endl;
    node<int>* nulltest = nullptr;
    insert_after(head, nulltest, 42);
    print_list(head) << endl;
}
void test_delete_head(){
    cout << ">>Testing delete head: " << endl;
    node<int>* head = new node<int>;
    init_head(head);
    for (int i=0; i<10; i++){
        insert_head(head, i);
    }
    print_list(head) << endl;
    cout << "Deleted head, returned item: " << delete_head(head) << endl;
    print_list(head) << endl;
    cout << "Deleted head, returned item: " << delete_head(head) << endl;
    print_list(head) << endl;
}
void test_copy_list(){
    cout << ">>Testing copy list: " << endl;
    node<int>* l1 = new node<int>;
    node<int>* l2 = new node<int>;
    node<int>* rear = new node<int>;
    init_head(l1);
    init_head(l2);
    for (int i=0; i<10; i++){
        insert_head(l1, i);
    }
    l2 = copy_list(l2, l1);
    cout << "First list: ";
    print_list(l1) << endl;
    cout << "Copied list: ";
    print_list(l2) << endl;
    cout << "Deleting first list (deep copy)..." << endl;
    delete_all(l1);
    cout << "Copied list: ";
    print_list(l2) << endl;
}

#endif // LIST_FUNCTIONS_H
