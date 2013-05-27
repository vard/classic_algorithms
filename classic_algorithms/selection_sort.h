#include <vector>
#include "vector_sort.h"

namespace selection_sort{
    using namespace std;
    template<typename T> class Selection : public VectorSort<T>{
    private:
        //void exch(std::vector<T>& items, int i, int j);
    public:
        virtual void sort(vector<T>& items);        
    };

    template <typename T>void Selection<T>::sort(std::vector<T>& items){
        int n = items.size();
        for(int i = 0; i < (n-1); i++){
            int min = i;
            for(int j = i; j < n; j++){
                if((items)[j] < (items)[min]){
                    min = j;
                }
            }
            exch(items, i, min);
        }
    }

    /*template <typename T>void Selection<T>::exch(std::vector<T>& items, int i, int j){
        T swap;
        swap = (items)[i];
        (items)[i] = (items)[j];
        (items)[j] = swap;
    }*/

}