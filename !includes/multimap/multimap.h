#ifndef MULTI_MAP_H
#define MULTI_MAP_H

#include "../b_plus_tree/b_plus_tree.h"
#include "mpair.h"
using namespace std;

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it);
        Iterator operator ++(int unused);
        Iterator operator ++();
        MPair<K, V> operator *();
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs);
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs);

    private:
        typename map_base::Iterator _it;
    };

    MMap();

//Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

//  Modifiers
    void insert(const MPair<K, V> insert_me){
        bpt.insert(insert_me);
        key_count++;
    }
    void insert(const K& k, const V& v){
        MPair<K, V> tempPair{k, v};
        bpt.insert(tempPair);
        key_count++;
    }

    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const ;
    vector<V> &get(const K& key);

    // Iterator find(const K& key);
    int count(const K& key);
    // I have not written these yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    map_base bpt;
    int key_count;
};

//--------------------------------------------------------------------------

template <typename K, typename V>
MMap<K, V>::MMap(){
    key_count = 0;
}

template <typename K, typename V>
int MMap<K, V>::size() const{
    return key_count;
}

template <typename K, typename V>
bool MMap<K, V>::empty() const{
    if(key_count == 0) return true;
    else return false;
}

template <typename K, typename V>
vector<V>& MMap<K, V>::operator[](const K& key){
    vector<V>& v = bpt.get(key).value_list;
    return v;
}

template <typename K, typename V>
void MMap<K, V>::erase(const K& key){
    bpt.remove(key);
    key_count--;
}

#endif // MULTI_MAP_H