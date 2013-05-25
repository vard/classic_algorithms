/* 
 * File:   linklist_impl_queue.h
 * Author: vard
 *
 * Created on 25 Май 2013 г., 15:28
 */

#ifndef LINKLIST_IMPL_QUEUE_H
#define	LINKLIST_IMPL_QUEUE_H

#include <cstdlib>

namespace linklist_q {

    template <typename T> struct Node {
        T value;
        Node<T>* next;
    };

    template <typename T> class Queue {
    private:
        Node<T>* first;
        Node<T>* last;
    public:
        Queue();
        ~Queue();
        void enqueue(T& item);
        T dequeue() throw (const char*);
        bool isEmpty();
    };

    template <typename T>Queue<T>::Queue()
    : first(NULL),
    last(NULL) {

    }

    template <typename T>Queue<T>::~Queue() {
        Node<T>* tmpNode = NULL;
        while (first != NULL) {
            tmpNode = first;
            first = first->next;
            delete tmpNode;
        }

    }

    template <typename T>void Queue<T>::enqueue(T& item) {
        Node<T>* newItem = new Node<T>;
        newItem->value = item;
        newItem->next = NULL;
        if (isEmpty()) {
            first = last = newItem;
        } else {
            last->next = newItem;
            last = last->next;
        }

    }

    template <typename T>T Queue<T>::dequeue() throw (const char*) {
        if (isEmpty()) {
            throw "Queue underflow";
            return NULL;
        }
        Node<T>* oldFirst = first;
        T item = first->value;
        first = first->next;
        delete oldFirst;
        return item;
    }

    template <typename T>bool Queue<T>::isEmpty() {
        return (first == NULL);
    }

}
#endif	/* LINKLIST_IMPL_QUEUE_H */

