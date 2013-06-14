#ifndef __BIN_HEAP_IMPL_PRIORITY_Q_H__
#define __BIN_HEAP_IMPL_PRIORITY_Q_H__
#include <vector>

template <typename K> class MaxPQ{
private:
    std::vector<K> pq;
    void swim(int index);
    void sink(int index);
    void exch(int i, int j);
public:
    MaxPQ();
    MaxPQ(int volume);
    bool isEmpty();
    void insert(const K& key);
    bool delMax(K* item);
};

template <typename K>void MaxPQ<K>:: sink(int index){
    while(2*index < pq.size()){
        int j = index*2;
        if((j < pq.size()-1) && (pq.at(j)<pq.at(j+1)))
            j++;
        if(pq.at(index)<pq.at(j)){
            exch(index, j);
            index=j;
        } else {
            break;
        }
    }
}

template <typename K>void MaxPQ<K>:: swim(int index){
    while(pq.at(index)>pq.at(index/2) && index > 1){
        exch(index, index/2);
        index/=2;
    }
}

template <typename K>void MaxPQ<K>::exch(int i, int j){
    K swap = pq.at(i);
    pq.at(i) = pq.at(j);
    pq.at(j) = swap;
}

template <typename K>MaxPQ<K>::MaxPQ(){
    pq.push_back(0);  // take 0 index
}

template <typename K>MaxPQ<K>::MaxPQ(int capacity){
    pq.push_back(0);  // take 0 index
}

template <typename K>bool MaxPQ<K>::delMax(K* item){
    K temp;
    if(isEmpty())
        return false;

    exch(1, pq.size()-1);
    *item = *(pq.end()-1);
    pq.pop_back();
    sink(1);
    
    return true;
}

template <typename K>void MaxPQ<K>::insert(const K& key){
    pq.push_back(key);
    if(isEmpty())
        return;
    swim(pq.size()-1);
}

template <typename K>bool MaxPQ<K>::isEmpty(){
    return (pq.size() == 1);
}

#endif