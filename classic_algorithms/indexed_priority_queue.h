#pragma  once
#include <deque>
#include "boost/cstdint.hpp"
#include "boost/exception/all.hpp"
#include <exception>

using namespace std;
using namespace boost;

namespace indexed_pq
{
    template<typename T> 
    class IndexedPQ{
    private:
        uint32_t maxElemCount_;
        uint32_t elemCount_;
        std::deque<int32_t> pq_;
        std::deque<int32_t> qp_;
        std::deque<T> keys_;

        void swim(uint32_t k);
        void sink(uint32_t k);
        void exch(uint32_t i, uint32_t j);
        bool greater(uint32_t i, uint32_t j);
    public:
        //IndexedPQ();
        IndexedPQ(uint32_t maxElem);
        bool isEmpty();
        bool contains(uint32_t i) throw (std::out_of_range);
        uint32_t size();
        void insertElem(uint32_t index, const T& key) throw (std::invalid_argument);
        void deleteElem(uint32_t index) throw (std::out_of_range, const char*);
        void increaseKey(uint32_t index, const T& key);
        void decreaseKey(uint32_t index, const T& key);
        void changeKey(uint32_t index, const T& key);
        T keyOf(uint32_t index);
        int deleteMin();
        T minKey();        
    };

    template<typename T>
    T indexed_pq::IndexedPQ<T>::minKey()
    {
        if(0 == elemCount_)
            throw std::out_of_range("Priority queue underflow");
        return keys[pq[1]];
    }

    template<typename T>
    int indexed_pq::IndexedPQ<T>::deleteMin()
    {
        if(0 == elemCount_)
            throw std::out_of_range("Priority queue underflow");
        uint32_t min = pq_[1];
        exch(1, elemCount_);
        --elemCount_;
        sink(1);
        qp_[min] = -1;
        return min;
    }

    template<typename T>
    T indexed_pq::IndexedPQ<T>::keyOf( uint32_t index )
    {
        if(index >= maxElemCount_)
            throw std::out_of_range("index is out of bound");
        if(!contains(index))
            throw "no such element";
        else
            return keys[i];    
    }

    template<typename T>
    void indexed_pq::IndexedPQ<T>::changeKey( uint32_t index, const T& key )
    {
        if(index >= maxElemCount_)
            throw std::out_of_range("index is out of bound");
        if(!contains(index))
            throw "no such element";
        if(keys[index] == key)
            throw std::invalid_argument("Calling increaseKey() with given argument would not strictly increase the key");
        keys[index] = key;
        swim(qp[index]);
        sink(qp[index]);
    }

    template<typename T>
    void indexed_pq::IndexedPQ<T>::decreaseKey( uint32_t index, const T& key )
    {
        if(index >= maxElemCount_)
            throw std::out_of_range("index is out of bound");
        if(!contains(index))
            throw "no such element";

        if(keys_[index] == key)
            throw std::invalid_argument("Calling increaseKey() with given argument would not strictly increase the key");
        keys_[index] = key;
        swim(qp_[index]);

    }

    template<typename T>
    void indexed_pq::IndexedPQ<T>::increaseKey( uint32_t index, const T& key )
    {
        if(index >= maxElemCount_)
            throw std::out_of_range("index is out of bound");
        if(!contains(index))
            throw "no such element";
        if(keys[index] == key)
            throw std::invalid_argument("Calling increaseKey() with given argument would not strictly increase the key");
        keys[index] = key;
        sink(qp[index]);
    }

    template<typename T>
    void indexed_pq::IndexedPQ<T>::deleteElem( uint32_t index )
    {
        if(index >= maxElemCount_)
            throw std::out_of_range("index is out of bound");
        if(!contains(index))
            throw "no such element";

        int i = qp[index];
        exch(i, elemCount_);
        --elemCount_;
        swim(i);
        sink(i);
        qp[index] = -1;
    }
    
    template<typename T>
    void indexed_pq::IndexedPQ<T>::sink( uint32_t k )
    {
        while(2*k <= elemCount_){
            uint32_t j = k*2;
            if(j < elemCount_ && greater(j, j+1)) // нам нужно сравивать с меньшим
                ++j;
            if(!greater(k, j))
                break;
            exch(k, j);
            k = j;
        }
    }

    template<typename T>
    void indexed_pq::IndexedPQ<T>::exch( uint32_t i, uint32_t j )
    {
        int32_t swap = pq_[i];
        pq_[i] = pq_[j];
        pq_[j] = swap;
        qp_[pq_[i]] = i;
        qp_[pq_[j]] = j;
    }

    template<typename T>
    void indexed_pq::IndexedPQ<T>::swim( uint32_t k )
    {
        while(k > 1 && greater(k/2, k)){
            exch(k, k/2);
            k = k/2;
        }
    }

    template<typename T>
    bool indexed_pq::IndexedPQ<T>::greater( uint32_t i, uint32_t j )
    {
        if( contains(pq_[i])){
            if(contains(pq_[j]))
                return (keys_[pq_[i]] > keys_[pq_[j]]);
            else
            {
                return true;
            }
        }
        else
        {
            if(contains(pq_[j]))
                return false;
            else
            {
                return true;
            }
        }
    }

    template<typename T>
    void indexed_pq::IndexedPQ<T>::insertElem( uint32_t index, const T& key )
    {
        if(contains(index)){
            throw std::invalid_argument("Index is already on priority queue");
        }
        ++elemCount_;
        qp_[index] = elemCount_;
        pq_[elemCount_]=index;
        keys_[index] = key;
        swim(elemCount_);
    }

    template<typename T>IndexedPQ<T>::IndexedPQ(uint32_t maxElem){
    qp_.resize(maxElem+1, -1);
    pq_.resize(maxElem+1);
    keys_.resize(maxElem+1);
    elemCount_ = 0;
    maxElemCount_ = maxElem;
}

    template<typename T>bool IndexedPQ<T>::isEmpty(){
    return (0 == elemCount_);
}

    template<typename T>bool IndexedPQ<T>::contains(uint32_t i){

    if((i < 0) || (i >= maxElemCount_)){
        throw std::out_of_range("out of range");
    }

    return -1 != qp_[i];
}

    template<typename T>uint32_t IndexedPQ<T>::size(){
    return elemCount_;
}

}



