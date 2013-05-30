#ifndef __INSERTION_SORT_H__
#define __INSERTION_SORT_H__

#include <vector>
using namespace std;

template <typename T> class Insertion : public VectorSort<T>{
private:
    void sort(vector<T>& items);
public:    
       
    void sort(vector<T>& items, unsigned int lo, unsigned int hi) throw (const char *);        
};

template <typename T>void Insertion<T>::sort(vector<T>& items){
    return;
}

template <typename T>void Insertion<T>::sort(vector<T>& items, unsigned int lo, unsigned int hi) throw (const char *){
    //unsigned int n =  0;
    if( (hi-lo)>=items.size() || (lo > hi)){
        throw "Wrong vector capacity";
        return;
    }
        

    for(unsigned int i = lo; i <= hi; i++){
        for(int j=i; j > 0; j--){
            if(items[j]<items[j-1]){
                exch(items, j, j-1);
            } else {
                break;
            }
        }
    }
}

#endif