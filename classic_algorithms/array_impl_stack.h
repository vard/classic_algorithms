#ifndef __ARRAY_IMPL_STACK__
#define __ARRAY_IMPL_STACK__

namespace array_impl_stack
{
#define DEFAULT_STACK_DEPTH 10

    template <typename T> class Stack{
    private:
        T* stackArray;
        unsigned int stackPtr;    
        unsigned int arraySize;
    public:
        Stack();
        ~Stack();
        bool isEmpty();
        void push(T& item);
        T pop();
    };

    template <typename T> Stack<T>::Stack() : stackPtr(0), arraySize(DEFAULT_STACK_DEPTH){
        stackArray = new T[arraySize];
    }

    template <typename T> Stack<T>::~Stack(){
        delete[] stackArray;
    }

    template <typename T> bool Stack<T>::isEmpty(){
        return (stackPtr==0);
    }

    template <typename T> void Stack<T>::push(T &item){
        *(stackArray+stackPtr) = item;
        stackPtr++;
        if(stackPtr==arraySize){
            T* newArray = new T[2*arraySize];
            memcpy(newArray, stackArray, arraySize*sizeof(T));
            delete[] stackArray;
            stackArray = newArray;
            arraySize*=2;
        }
    }

    template <typename T> T Stack<T>::pop(){
        T val = *(stackArray+stackPtr-1);
        stackPtr--;
        if(stackPtr<=arraySize/4){
            T* newArray = new T[arraySize/2];
            memcpy(newArray, stackArray, stackPtr*sizeof(T));
            delete[] stackArray;
            stackArray = newArray;
            arraySize/=2;
        }
        return val;
    }
}
#endif 