#if defined  _WIN32
#include "stdafx.h"
#endif

#ifdef _WIN64
#include "stdafx.h"
#endif

#include "linklist_stack.h"
#include "array_impl_stack.h"
#include <iostream>

using namespace std;
using namespace linked_list_stack;
using namespace array_impl_stack;

#ifdef _WIN64

int _tmain(int argc, _TCHAR* argv[])
#endif

#ifdef __linux__
int main(int argc, char** argv)
#endif
{
    /* linked list implementation stack */
    cout << "****Stack linked list implementation****" << endl;
    cout << "stack push(1-100)" << endl;
    linked_list_stack::Stack<int> integerStack;
    for (int i = 0; i < 100; i++) {
        integerStack.push(i);
    }
    try {
        cout << "stack pop(105)" << endl;
        for (int i = 0; i < 105; i++) {
            cout << integerStack.pop() << " ";
        }
    } catch (const char *p) {
        cout << endl << p << endl;
    } catch (...) {
        cout << "Unknown exception" << endl;
    }

    cout << endl;
    cout << "stack push(1-100)" << endl;
    for (int i = 0; i < 100; i++) {
        integerStack.push(i);
    }
    cout << "stack pop all" << endl;
    while (!integerStack.isEmpty()) {
        cout << integerStack.pop() << " ";
    }

    cout << endl;

    /* array implementation stack */
    cout << "****Stack resizing array implementation****" << endl;
    cout << "stack push(1-100)" << endl;
    array_impl_stack::Stack<int> integerArrayBasedStack;
    for (int i = 0; i < 100; i++) {
        integerArrayBasedStack.push(i);
    }

    try {
        cout << "stack pop(105)" << endl;
        for (int i = 0; i < 105; i++) {
            cout << integerArrayBasedStack.pop() << " ";
        }
    } catch (const char *p) {
        cout << endl << p << endl;
    } catch (...) {
        cout << "Unknown exception" << endl;
    }

    cout << "stack push(1-100)" << endl;
    for (int i = 0; i < 100; i++) {
        integerArrayBasedStack.push(i);
    }
    cout << "stack pop all" << endl;
    try {
        while (!integerArrayBasedStack.isEmpty()) {
            cout << integerArrayBasedStack.pop() << " ";
        }
    } catch (const char* p) {
        cout << endl << p << endl;
    } catch (...) {
        cout << endl << "Unknown exception" << endl;
    }
    cout << endl;

    return 0;
}

