#ifndef __LINKLIST_STACK__
#define __LINKLIST_STACK__

#include "stdafx.h"
namespace linked_list_stack
{

    template <typename T>struct Node{
        T value;
        Node<T>* next;
    };

    // implemented as linked list stack
    template <typename T> class Stack{

    public:
        Stack();
        ~Stack();
        void push(T& item);
        T pop();
        bool isEmpty();
    private:
        Node<T>* first;
    };

    template <typename T> Stack<T>::Stack(){
        first = NULL;
    }

    template <typename T> Stack<T>::~Stack(){
        Node<T>* nodeToDelete = NULL;
        while(first != NULL){
            nodeToDelete = first->next;
            delete first;
            first = nodeToDelete;
        }
    }

    template <typename T> void Stack<T>::push(T &item){
        Node<T>* newNode = new Node<T>();
        newNode->next = first;
        newNode->value = item;
        first = newNode;
    }

    template <typename T> T Stack<T>::pop(){
        Node<T> tempNode;
        tempNode.next = first->next;
        tempNode.value = first->value;
        delete first;
        first = tempNode.next;
        return tempNode.value;
    }

    template <typename T> bool Stack<T>::isEmpty(){
        return (first==NULL);
    }

}
#endif