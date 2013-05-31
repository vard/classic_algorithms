#include <vector>
#include <ctime>

using namespace std;

template <typename T> class VectorSort{
protected:
    virtual void exch(std::vector<T>& items, int i, int j);
    void medianOf3(std::vector<T>& items, int lo, int mid, int hi);
public:
    virtual void sort(vector<T>& items) = 0;  
    bool isSorted(vector<T>& items);
};

template <typename T>void VectorSort<T>::medianOf3(std::vector<T>& items, int lo, int mid, int hi){
    if(items[lo] < items[mid])
        exch(items, lo, mid);
    if(items[hi]<items[mid])
        exch(items, hi, mid);
    if(items[hi]<items[lo])
        exch(items, hi, lo);
}

template <typename T>void VectorSort<T>::exch(std::vector<T>& items, int i, int j){
    T swap;
    swap = (items)[i];
    (items)[i] = (items)[j];
    (items)[j] = swap;
}

template <typename T>bool VectorSort<T>::isSorted(std::vector<T> &items){
    unsigned int N = items.size();
    for(unsigned int i = 0; i < N-1; i++){
        if(items[i] > items[i+1])
            return false;
    }
    return true;
}
