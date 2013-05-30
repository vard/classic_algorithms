#if defined  _WIN32
#include "stdafx.h"
#endif

#ifdef _WIN64
#include "stdafx.h"
#endif

#include <iostream>
#include <vector>
#include <ctime>
#include "linklist_stack.h"
#include "array_impl_stack.h"
#include "linklist_impl_queue.h"
#include "array_impl_queue.h"
#include "selection_sort.h"
#include "insertion_sort.h"
#include "shell_sort.h"
#include "mergesort.h"


using namespace std;
using namespace linked_list_stack;
using namespace array_impl_stack;
using namespace linklist_q;
using namespace array_impl_q;
using namespace selection_sort;

#ifdef _WIN64
int _tmain(int argc, _TCHAR* argv[])
#endif

#ifdef _WIN32
int _tmain(int argc, _TCHAR* argv[])
#endif

#ifdef __linux__
int main(int argc, char** argv)
#endif
{
    
    vector<int> intVec;
    srand(time(NULL));
    for(int i = 0; i < 10000; i++){  
        intVec.push_back(rand()%(1000+1)) ;
    }

    // Mergesort
    cout << "Mergesort" << endl;
    Mergesort<int> intMergeSort;
    intMergeSort.sort(intVec);

    for(std::vector<int>::iterator it = intVec.begin(); it != intVec.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    /*
    // Shellsort
    cout << "Shellsort" << endl;
    Shell<int> intShellSort;
    intShellSort.sort(intVec);

    for(std::vector<int>::iterator it = intVec.begin(); it != intVec.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
    */
    
    // Insertion sort
    cout << "Insertion sort: " << endl;
    Insertion<int> intInsertion;
   
    intInsertion.sort(intVec, 0, 20);
    for(std::vector<int>::iterator it = intVec.begin(); it != intVec.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
    
    /*
    // Selection sort
    cout << "Selection sort: " << endl;    
    Selection<int> intSelection;
    intSelection.sort(intVec);
    
    for(std::vector<int>::iterator it = intVec.begin(); it != intVec.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
    */

    // array Q implementation
    array_impl_q::Queue<int> arrayQ;
    unsigned int itemsCount = 100;
    cout << "Enqueue " << itemsCount << " items" << endl;
    for (int i = 0; i < itemsCount; i++) {
        arrayQ.enqueue(i);
    }
    
    itemsCount = 90;
    cout << "Dequeue " << itemsCount << " items" << endl;
    try{
    for (unsigned int i = 0; i < itemsCount; i++) {
        cout << arrayQ.dequeue() << " ";
    }
    cout << endl;
    }
    catch(const char *str){
        cout << endl << str << endl;
    }
    catch(...){
        cout << endl << "Unknown exception" << endl;
    }


/*
    // linked list Q implementation
    linklist_q::Queue<int> linkedListQ;
    unsigned int itemsCount = 1500000;
    cout << "Enqueue " << itemsCount << " items" << endl;
    for (int i = 0; i < itemsCount; i++) {
        linkedListQ.enqueue(i);
    }
    itemsCount = 1500000;
    cout << "Dequeue " << itemsCount << " items" << endl;
    try{
    for (int i = 0; i < itemsCount; i++) {
        cout << linkedListQ.dequeue() << " ";
    }
    cout << endl;
    }
    catch(const char *str){
        cout << endl << str << endl;
    }
    catch(...){
        cout << endl << "Unknown exception" << endl;
    }
 */




    /*
    // linked list implementation stack 
    cout << "****Stack linked list implementation****" << endl;
    cout << "stack push(1-100)" << endl;
    linked_list_stack::Stack<int> integerStack;
    for (int i = 0; i < 100000; i++) {
        integerStack.push(i);
    }
    try {
        cout << "stack pop(105)" << endl;
        for (int i = 0; i < 105000; i++) {
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

    // array implementation stack
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
    cout << endl;*/

    return 0;
}

