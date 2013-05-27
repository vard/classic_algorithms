#include <vector>
using namespace std;

template <typename T> class VectorSort{
protected:
    virtual void exch(std::vector<T>& items, int i, int j);
public:
    virtual void sort(vector<T>& items) = 0;  
};

//template <typename T>void VectorSort<T>::exch(std::vector<T>::iterator it, std::vector<T>::iterator jt){
template <typename T>void VectorSort<T>::exch(std::vector<T>& items, int i, int j){
        T swap;
        swap = (items)[i];
        (items)[i] = (items)[j];
        (items)[j] = swap;
    }