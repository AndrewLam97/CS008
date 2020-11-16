#ifndef MPAIR_H
#define MPAIR_H
#include <vector>
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
    MPair(const K& k=K());
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
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me);
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
};

#endif // MPAIR_H