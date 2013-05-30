#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include <vector>
#include "insertion_sort.h"

using namespace std;
template <typename T> class Mergesort : public VectorSort<T>{
private:
    void merge(std::vector<T>& items, unsigned int lo, unsigned mid, unsigned int hi);
    void sort(std::vector<T>& items, unsigned int lo, unsigned int hi);
public:
    void sort(std::vector<T>& items);
};

template <typename T>void Mergesort<T>::sort(std::vector<T>& items){
    sort(items, 0, items.size()-1);

}

template <typename T>void Mergesort<T>::sort(std::vector<T>& items, unsigned int lo, unsigned int hi){
        unsigned int mid = lo + (hi-lo)/2;
        if(lo>=hi){        
            return;
        } else if(hi-lo < 6) {
            Insertion<T> insertionSort;
            insertionSort.sort(items, lo, hi);
        } else {
            sort(items, lo, mid);   // left includingg mid
            sort(items, mid+1, hi); // right 
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