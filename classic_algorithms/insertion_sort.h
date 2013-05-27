#include <vector>
using namespace std;

template <typename T> class Insertion : public VectorSort<T>{
public:
    void sort(vector<T>& items);        
};

template <typename T>void Insertion<T>::sort(vector<T>& items){
    unsigned int n = items.size();
    for(int i = 0; i < n; i++){
        for(int j=i; j > 0; j--){
            if(items[j]<items[j-1]){
                exch(items, j, j-1);
            } else {
                break;
            }
        }
    }
}
