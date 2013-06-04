#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>
#include "st.h"

using namespace std;

template <typename K, typename V> bool comparePairs(const std::pair<K,V>& lhs, const std::pair<K,V>& rhs){
    if(strcmp(lhs.first, rhs.first)<0)
        return true;
    else 
        return false;
    /*  if(left.first <= right.first)
    return 1;
    else 
    return -1;*/
}

template <typename K, typename V> class BinSearchST : public SymbolTableInterface<K,V>{
private:
    vector<pair<K,V>> items;    
    void sort();
    int binSearch(K key, int lo, int hi);
public:
    //binSearchST(const std::vector<T>& items);
    void put(const K key, const V val);
    V get(K key);
    void remove(K key);
    int size();
    bool isEmpty();    
};

template <typename K, typename V>int BinSearchST<K,V>::binSearch(K key, int lo, int hi){
    if(isEmpty())
        return NULL;
    int mid = (hi-lo)/2 + lo;
    if(key==items[mid].first)
        return mid;
    if(lo>=hi)
        return NULL;
    if(key<items[mid].first){
        return binSearch(key, lo, mid-1);
    } else {
        return binSearch(key, mid+1, hi);
    }
}

template <typename K, typename V>void BinSearchST<K,V>::remove(K key){
    int index = this->binSearch(key, 0, items.size()-1);
    if(index!=NULL){
        items.erase(items.begin()+index);
        this->sort();
    }
    // ! implement
}

template <typename K, typename V>void BinSearchST<K,V>::sort(){
    std::sort(items.begin(), items.end());
}

template <typename K, typename V>int BinSearchST<K,V>::size(){
    return items.size();
}

template <typename K, typename V>bool BinSearchST<K,V>::isEmpty(){
    return (items.size()==0);
}

template <typename K, typename V>V BinSearchST<K,V>::get(K key){
    int index = 0;
    if((index = binSearch(key, 0, items.size()-1))!=NULL)
        return items[index].second;
    else
        return NULL;

}

template <typename K, typename V> void BinSearchST<K,V>::put(const K key, const V val){

    if(!this->contains(key)){
        this->items.push_back(pair<K,V>(key, val));
    } else {
        throw "Key already exists in collection";
        return;
    }
    this->sort();
}