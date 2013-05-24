// classic_algorithms.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "linklist_stack.h"
#include "array_impl_stack.h"
#include <iostream>

using namespace std;
using namespace linked_list_stack;
using namespace array_impl_stack;

int _tmain(int argc, _TCHAR* argv[])
{
    /* linked list implementation stack */
    linked_list_stack::Stack<int> integerStack;
    for(int i = 0; i < 100; i++){
        integerStack.push(i);
    }
    for(int i = 0; i < 50; i++){
        cout << integerStack.pop() << " ";
    }
    for(int i = 0; i < 100; i++){
        integerStack.push(i);
    }
    while(!integerStack.isEmpty()){
        cout << integerStack.pop() << " ";
    }

    cout << endl;

        /* array implementation stack */
    array_impl_stack::Stack<int> integerArrayBasedStack;
    for(int i = 0; i < 100; i++){
        integerArrayBasedStack.push(i);
    }
    for(int i = 0; i < 50; i++){
        cout << integerArrayBasedStack.pop() << " ";
    }
    /*
    for(int i = 0; i < 100; i++){
        integerArrayBasedStack.push(i);
    }
    while(!integerArrayBasedStack.isEmpty()){
        cout << integerArrayBasedStack.pop() << " ";
    }*/

	return 0;
}

