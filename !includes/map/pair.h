#ifndef PAIR_H
#define PAIR_H
#include <iostream>
using namespace std;

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()){
        this->key = k;
        this->value = v;
    }
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me){
        outs << print_me.value;
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key == rhs.key) return true;
        else return false;
    }
    friend bool operator !=(const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key != rhs.key) return true;
        else return false;
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key < rhs.key) return true;
        else return false;
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key > rhs.key) return true;
        else return false;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs.key <= rhs.key) return true;
        else return false;
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs){  //return rhs
        return rhs;
    }
};

#endif // PAIR_H