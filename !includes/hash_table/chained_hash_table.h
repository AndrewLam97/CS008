/*
 * Author: Andrew Lam
 * Project: Hash Table
 * Purpose: Chained Hash Table Header File
 * Notes: Uses AVL
 */

#ifndef CHAINED_HASH_TABLE_H
#define CHAINED_HASH_TABLE_H
#include "../../BST/AVL/avl_array.h"
#include "hash_table_base.h"
#include <cstdlib>
#include <iomanip>
#include <cassert>
#include <iostream>
using namespace std;

template <typename T>
class Chained_Hash_Table{
public:
    Chained_Hash_Table();
    Chained_Hash_Table(int CAPACITY);

    Chained_Hash_Table(const Chained_Hash_Table<T>& copy_me);
    Chained_Hash_Table<T>& operator = (const Chained_Hash_Table<T>& rhs);
    ~Chained_Hash_Table();

    int hash_func1(int key, int CAPACITY);
    int findIndex(int key);

    bool insert(int key, int value);
    bool remove(const int  key);
    int search(const int pos);

    void printTable();

private:
    const int MIN_TABLE_SIZE = 10;
    int size;
    int CAPACITY;

    avl_array<int, int, std::uint16_t, 2048, true> *table;
};

template <typename T>
int Chained_Hash_Table<T>::hash_func1(int key, int CAPACITY){
    return key % CAPACITY;
}

template <typename T>
Chained_Hash_Table<T>::Chained_Hash_Table(int CAPACITY){
    if (CAPACITY < MIN_TABLE_SIZE){
        cout<<"Table Size Too Small"<<endl;
    }
    this->CAPACITY = CAPACITY;
    this->table = new avl_array<int, int, std::uint16_t, 2048, true> [this->CAPACITY];
    if (this->table == NULL)
    {
        cout<<"Table Size Too Small"<<endl;
    }
}

template <typename T>
Chained_Hash_Table<T>::~Chained_Hash_Table(){
    size = 0;
    delete []table;
}

template <typename T>
int Chained_Hash_Table<T>::findIndex(int key){
    int hashIndex = hash_func1(key, CAPACITY);
    return hashIndex;
} 

template <typename T>
bool Chained_Hash_Table<T>::insert(int key, int value){
    int pos = findIndex(key);
    if(pos == -1){
        return false;
    }
    table[pos].insert(key, value);
    return false;
}

template <typename T>
bool Chained_Hash_Table<T>::remove(const int key){
    int pos = findIndex(key);
    table[pos].erase(key);
    return true;
}

template <typename T>
int Chained_Hash_Table<T>::search(int key){
    int hashIndex = hash_func1(key, CAPACITY);
    return *table[hashIndex].find(key);
}

template <typename T>
void Chained_Hash_Table<T>::printTable(){
    for (int i = 0; i < CAPACITY; i++)
    {
        cout<< "[" << setw(3) << setfill('0') << i << "] ";

        for (auto it = table[i].begin(); it != table[i].end(); ++it) {
            int tempKey = it.key();
            std::cout << "[" << tempKey << ":" << *it << "]" << "->";
        } 
        cout << " ||||" << endl;
    }
}

#endif // CHAINED_HASH_TABLE_H