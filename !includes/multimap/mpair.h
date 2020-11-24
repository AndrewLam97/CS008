#ifndef MPAIR_H
#define MPAIR_H
#include <vector>
#include <iostream>
using namespace std;

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K()){
        key = k;
        vector<V> newVec;
        value_list = newVec;
    }
    MPair(const K& k, const V& v){
        key = k;
        value_list.push_back(v);
    }
    MPair(const K& k, const vector<V>& vlist){
        key = k;
        for(int i = 0; i < vlist.size(); i++){
            value_list.push_back(vlist[i]);
        }
    }
    //--------------------------------------------------------------------------------

    //You'll need to overload << for your vector:

    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me){
        outs << "[ ";
        for(int i = 0; i < print_me.value_list.size(); i++){
            outs << print_me.value_list[i] << " ";
        }
        outs << "]" << endl;
        return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return (lhs.key == rhs.key);
    }
    friend bool operator !=(const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        if(lhs.key != rhs.key) return true;
        else return false;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return (lhs.key < rhs.key);
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return (lhs.key <= rhs.key);
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return (lhs.key > rhs.key);
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        for(int i = 0; i < rhs.value_list.size(); i++){
            lhs.value_list.pushback(rhs.value_list[i]);
        }
        return lhs;
    }
};

//Vector overload
template <typename T>
ostream& operator<<(ostream& outs, const vector<T>& v) { 
        outs << "[ ";
        for(int i = 0; i < v.size(); i++){
            outs << v[i] << " ";
        }
        outs << "]" << endl;
        return outs;
    }

#endif // MPAIR_H