/*
 * Author: Andrew Lam
 * Project: Hash Table
 * Purpose: Double and Chained Hash Tables
 * Notes: Base File for holding enumeration and Record struct
 */
#ifndef HASH_TABLE_BASE_H
#define HASH_TABLE_BASE_H

enum Usage {Used, Usable, Deleted};

template <typename T>
struct Record{
    T item;
    int key;
    enum Usage info;
    int orig;

    bool operator==(const Record &rec1){
        return(item == rec1.item && key == rec1.key && info == rec1.info);
    }
};

#endif // HASH_TABLE_BASE_H