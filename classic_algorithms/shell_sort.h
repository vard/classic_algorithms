#include <vector>

using namespace std;

template <typename T> class Shell : public VectorSort<T>{
public:
    virtual void sort(vector<T>& items);
};

template <typename T>void Shell<T>::sort(vector<T>& items){
    unsigned int n = items.size();
    unsigned int h = 1;

    while(h<n/3){
        h = h*3 +1;
    }

    while(h>=1){
        for(int i = 0; i < n; i+=h){
            for(int j = i; j >= h ; j-=h){
                if( items[j-h]>items[j]){
                    exch(items, j, j-h);
                } else{
                    break;
                }

            }
        }
        h = h/3;
    }
}