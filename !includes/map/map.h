#ifndef MAP_H
#define MAP_H
#include <string>

#include "pair.h"
#include "../btree/btree.h"

template <typename K, typename V>
class Map
{
public:
    typedef BTree<Pair<K, V> > map_base;
    // class Iterator{
    // public:
    //     friend class Map;
    //     Iterator(typename map_base::Iterator it);
    //     Iterator operator ++(int unused);
    //     Iterator operator ++();
    //     Pair<K, V> operator *();
    //     friend bool operator ==(const Iterator& lhs, const Iterator& rhs);
    //     friend bool operator !=(const Iterator& lhs, const Iterator& rhs);
    // private:
    //     typename map_base::Iterator _it;

    // };

    Map();
//--Iterators
    //Iterator begin();
    //Iterator end();

//--Capacity
    int size() const;
    bool empty() const;

//--Element Access
    V& operator[](const K& key);
    V& at(const K& key);
    const V& at(const K& key) const;


//--Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

//--Operations:
    //Iterator find(const K& key);
    bool contains(const Pair<K, V>& target) const;

    // I have not written these yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    //bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;
    map_base bt{3};
};

//-----------------------------------------------------------------------------

 template <typename K, typename V>
 Map<K, V>::Map(){
     key_count = 0;
}

template <typename K, typename V>
int Map<K, V>::size() const{
    return this->key_count;
}

template <typename K, typename V>
bool Map<K, V>::empty() const{
    if(key_count == 0) return true;
    else return false;
}

template <typename K, typename V>
V& Map<K, V>::operator[](const K& key){
    V& ValueRef = bt.get(key).value;
    return ValueRef;
}

template <typename K, typename V>
void Map<K, V>::insert(const K& k, const V& v){
    Pair<K, V> tempPair = {k, v};
    bt.insert(tempPair);
    key_count++;
}

template <typename K, typename V>
void Map<K, V>::erase(const K& key){
    bt.remove(key);
    key_count--;
}


#endif // MAP_H