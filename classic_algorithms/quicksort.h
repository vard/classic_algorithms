#ifndef __QUICKSORT_H__
#define __QUICKSORT_H__

#include <vector>
#include <algorithm>  
#include "insertion_sort.h"

using namespace std;

#define DEFAULT_QUICKSORT_CUTOFF 5

template <typename T> class QuickSort : public VectorSort<T>{
private:
    unsigned int cutoff;
    int partition(std::vector<T>& items, int lo, int hi);
    void sort(std::vector<T>& items, int lo, int hi);
public:
    void sort(std::vector<T>& items);
    QuickSort();
};

template <typename T>QuickSort<T>::QuickSort()
                    :cutoff(DEFAULT_QUICKSORT_CUTOFF){}


template <typename T>void QuickSort<T>::sort(std::vector<T>& items){
    sort(items, 0, items.size()-1);
}

template <typename T>int QuickSort<T>::partition(std::vector<T>& items, int lo, int hi){
    try{
        for(int i = lo, j = hi+1;;){
            while(items[++i]<=items[lo] && i<hi);
            while(items[--j]>items[lo]&&j>lo);
            if(i<j){
                exch(items, i, j);
            } else {
                exch(items, lo, j);
                return j;
            }
        }
    }
    catch(...){
        cout << "GOWNO";
        return -1;
    }
}


template <typename T>void QuickSort<T>::sort(std::vector<T>& items, int lo, int hi){
    if(lo>=hi)
        return;
    if(lo+cutoff>hi){
        typedef Insertion<int> intInsertion;
        intInsertion insertionSort;
        insertionSort.sort(items, lo, hi);
        return;
    }

    typename std::vector<T>::iterator start = items.begin()+lo;
    typename std::vector<T>::iterator end = items.begin()+hi;
   // random_shuffle(start, end);
    medianOf3(items, lo, (hi-lo)/2+lo, hi);

    int gt = hi, lt=lo;
    // three way partition
    for(int i = lo; i <= gt; ){
        if(items[i]<items[lt]){
            exch(items, i, lt);
            ++i;
            ++lt;
        }
        if(items[i]>items[lt]){
            exch(items, i, gt);
            --gt;
        }
        if(items[i] == items[lt]){
            i++;
        }
    }
    sort(items, lo, lt-1);
    sort(items, gt+1, hi);
    /*
    int mid = partition(items, lo, hi);
    sort(items, lo, mid-1);
    sort(items, mid+1, hi);*/
}

#endif