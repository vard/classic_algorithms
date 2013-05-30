#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include <vector>
#include <algorithm>
#include "insertion_sort.h"


using namespace std;

#define CUTOFF 6

template <typename T> class Mergesort : public VectorSort<T>{
private:
    unsigned int cutoff;
    void merge(std::vector<T>& items, unsigned int lo, unsigned mid, unsigned int hi);
    void sort(std::vector<T>& items, unsigned int lo, unsigned int hi);
public:
    void sort(std::vector<T>& items);
    void bottomUpSort(std::vector<T>& items);
    Mergesort();
};

template <typename T>void Mergesort<T>::bottomUpSort(std::vector<T>& items){
    unsigned int vecSize = items.size();
    for(unsigned int sz=1; sz < vecSize; sz = sz + sz){
        for(unsigned int lo = 0; lo < vecSize - sz; lo+=sz+sz){
            merge(items, lo, lo+sz-1, min(vecSize-1, lo+sz+sz-1));
        }
    }
}

template <typename T>Mergesort<T>::Mergesort()
:cutoff(CUTOFF){
}

template <typename T>void Mergesort<T>::sort(std::vector<T>& items){
    sort(items, 0, items.size()-1);

}

template <typename T>void Mergesort<T>::sort(std::vector<T>& items, unsigned int lo, unsigned int hi){
    unsigned int mid = lo + (hi-lo)/2;
    if(lo>=hi){        
        return;
    } else if(hi-lo < cutoff) {
        Insertion<T> insertionSort;
        insertionSort.sort(items, lo, hi);
    } else {
        sort(items, lo, mid);   // left includingg mid
        sort(items, mid+1, hi); // right 
        if(items[mid]<items[mid+1]){
            return;
        }
        merge(items, lo, mid, hi);
    }
}

template <typename T>void Mergesort<T>::merge(std::vector<T>& items, unsigned int lo, unsigned mid, unsigned int hi){
    vector<T> aux;
    for(unsigned int i = lo; i <= hi; i++){
        aux.push_back(items[i]);
    }

    unsigned int ix = 0;
    mid = mid - lo;
    unsigned int j = mid+1;
    for(unsigned int k = lo; k<=hi; k++){
        if(ix>mid){
            items[k]=aux[j++];
        } else if(j>(hi-lo)){
            items[k]=aux[ix++];
        } else if(aux[ix]<aux[j]){
            items[k] = aux[ix++];
        } else {
            items[k] = aux[j++];
        }
    }
}

#endif