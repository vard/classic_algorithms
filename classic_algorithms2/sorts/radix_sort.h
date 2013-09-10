#pragma once
#include <deque>
#include <string>

namespace radix_sort{
    typedef std::deque<std::string> stringArray;

    void LSDStringRadixSort(std::deque<std::string>& strings, uint32_t stringsLength);
    void MSDStringRadixSort( stringArray& strings );
    void threeWayInnerSort(stringArray& strings);





}