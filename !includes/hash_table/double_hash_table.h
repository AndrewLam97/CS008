/*
 * Author: Andrew Lam
 * Project: Hash Table
 * Purpose: Double Hash Table Header File
 * Notes: Uses secondary hash function to handle collisions
 */

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H
#include "hash_table_base.h"
#include <cstdlib>
#include <iomanip>
#include <cassert>
#include <iostream>
using namespace std;

template <typename T>
class Double_Hash_Table{
public:
    Double_Hash_Table();
    Double_Hash_Table(int CAPACITY);

    Double_Hash_Table(const Double_Hash_Table<T>& copy_me);
    Double_Hash_Table<T>& operator = (const Double_Hash_Table<T>& rhs);
    ~Double_Hash_Table();

    int hash_func1(int key, int CAPACITY);
    int hash_func2(int key, int CAPACITY);
    int findIndex(int key);

    bool insert(const Record<T> insert_me);
    bool remove(const int  key);
    Record<T> search(const int pos);

    void printTable();
    int getSize();

private:
    const int MIN_TABLE_SIZE = 10;
    int size = 0;
    int CAPACITY;

    Record<T> *table;
};

template <typename T>
int Double_Hash_Table<T>::getSize(){
    return this->size;
}

template <typename T>
int Double_Hash_Table<T>::hash_func1(int key, int CAPACITY){
    return key % CAPACITY;
}

template <typename T>
int Double_Hash_Table<T>::hash_func2(int key, int CAPACITY){
    return 1 + (key % (CAPACITY - 2));
}

template <typename T>
Double_Hash_Table<T>::Double_Hash_Table(int CAPACITY){
    if (CAPACITY < MIN_TABLE_SIZE){
        cout<<"Table Size Too Small"<<endl;
    }
    this->size = 0;
    this->CAPACITY = CAPACITY;
    this->table = new Record<T> [this->CAPACITY];
    if (this->table == NULL)
    {
        cout<<"Table Size Too Small"<<endl;
    }
    for (int i = 0; i < this->CAPACITY; i++)
    {
        this->table[i].info = Usable;
        this->table[i].key = NULL;
        this->table[i].item = NULL;
        this->table[i].orig = NULL;
    }
}

template <typename T>
Double_Hash_Table<T>::~Double_Hash_Table(){
    size = 0;
    delete []table;
}

template <typename T>
int Double_Hash_Table<T>::findIndex(int key){
    int hashIndex = hash_func1(key, CAPACITY);
    int stepIndex = hash_func2(key, CAPACITY);
    int count = 0;

    while((table[hashIndex].info != Usable)&& table[hashIndex].key != key){
        hashIndex = hashIndex + stepIndex;
        hashIndex = hashIndex % CAPACITY;
        if(count > CAPACITY){
            return -1;
        }
        count++;
    }
    return hashIndex;
} 

template <typename T>
bool Double_Hash_Table<T>::insert(const Record<T> insert_me){
    int pos = findIndex(insert_me.key);
    if(pos == -1){
        return false;
    }
    if(table[pos].info != Used){
        table[pos].info = Used;
        table[pos].item = insert_me.item;
        table[pos].key = insert_me.key;
        table[pos].orig = hash_func1(insert_me.key, CAPACITY);
        size++;
        return true;
    }
    return false;
}

template <typename T>
bool Double_Hash_Table<T>::remove(const int key){
    int pos = findIndex(key);
    if(this->table[pos].info == Used){
        //Record<T> temp = {NULL, NULL, Deleted, NULL};
        //table[pos] = temp;
        table[pos].info = Deleted;
        size--;
        return true;
    }
    return false;
}

template <typename T>
Record<T> Double_Hash_Table<T>::search(const int pos){
    if(table[pos].info == Deleted){
        Record<T> fail = {-1, -1, Deleted, -1};
        return fail;
    }
    else return table[pos];
}

template <typename T>
void Double_Hash_Table<T>::printTable(){
    for (int i = 0; i < CAPACITY; i++)
    {
        Record<T> tempRec = table[i];
        if (tempRec.info == Usable){
            cout<< "[" << setw(3) << setfill('0') << i << "] " <<endl;
        }
            
        if (tempRec.info == Deleted){
            cout<< "[" << setw(3) << setfill('0') << i << "] ----------" <<endl;
        }
        if(tempRec.info == Used){
            cout<< "[" << setw(3) << setfill('0') << i << "] " << tempRec.key << ":" << tempRec.item;
            cout << "(" << setw(3) << setfill('0') << tempRec.orig << ")";
            if(tempRec.orig != i){
                cout << " *";
            }
            cout << endl;
        }
    }
}

#endif // DOUBLE_HASH_TABLE_H