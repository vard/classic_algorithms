/* 
 * File:   array_impl_queue.h
 * Author: vard
 *
 * Created on 25 Май 2013 г., 17:45
 */

#ifndef ARRAY_IMPL_QUEUE_H
#define	ARRAY_IMPL_QUEUE_H

#include <cstdlib>

namespace array_impl_q {
#define DEFAULT_Q_ARRAY_CAPACITY 10

    template <typename T> class Queue {
    private:
        T* qArray;
        unsigned int head;
        unsigned int tail;
        unsigned int capacity;
    public:
        Queue();
        ~Queue();
        bool isEmpty();
        void enqueue(T& item);
        T dequeue() throw (const char *);
    };

    template <typename T>Queue<T>::Queue()
    : qArray(NULL),
    head(0),
    tail(0),
    capacity(DEFAULT_Q_ARRAY_CAPACITY) {
        qArray = new T[capacity];
    }

    template <typename T>Queue<T>::~Queue() {
        delete[] qArray;
    }

    template <typename T>bool Queue<T>::isEmpty() {
        return (head == tail);
    }

    template<typename T>void Queue<T>::enqueue(T& item) {
        qArray[tail++] = item;
        if (tail >= capacity) {
            T* newArray = new T[capacity * 2];
            for (unsigned int i = 0; i < tail - head; i++) {
                newArray[i] = qArray[i + head];
            }
            capacity *= 2;
            delete[] qArray;
            qArray = newArray;
            tail = tail - head;
            head = 0;
        }
    }

    template <typename T>T Queue<T>::dequeue() throw (const char*) {
        if (tail == head) {
            throw "Stack underflow";
            return NULL;
        }
        T item = qArray[head];
        head++;
        if (tail - head <= capacity / 4) {
            capacity /= 2;
            T* newArray = new T[capacity];
            for (int i = 0; i < tail - head; i++) {
                newArray[i] = qArray[i + head];
            }
            delete[] qArray;
            qArray = newArray;
            tail = tail - head;
            head = 0;
        }


        return item;
    }

}


#endif	/* ARRAY_IMPL_QUEUE_H */

