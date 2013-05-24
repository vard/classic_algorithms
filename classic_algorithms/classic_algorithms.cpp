// classic_algorithms.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "my_stack.h"
#include "array_impl_stack"
#include <iostream>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
    /* linked list implementation stack */
    Stack<int> integerStack;
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

	return 0;
}

