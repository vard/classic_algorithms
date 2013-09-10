
#include <cstdint>
#include <algorithm>
#include <array>
#include <vector>
#include <iostream>

#include "radix_sort.h"

using namespace std;

namespace radix_sort{


    void LSDStringRadixSort(std::deque<std::string>& strings, uint32_t stringsLength){
        uint32_t radix = 256;
        uint32_t stringCount = strings.size();
        std::deque<std::string> aux;
        aux.resize(strings.size());

        for(int32_t d = stringsLength -1; d >= 0; --d){
            std::deque<uint32_t> count;
            count.resize(radix+1);
            for(uint32_t i = 0; i < stringCount; ++i){
                ++count[strings[i].at(d)+1];
            }
            for(uint32_t i = 0; i < radix; ++i){
                count[i+1]+=count[i];
            }
            for(uint32_t i = 0; i < stringCount; ++i){
                aux[count[strings[i].at(d)]++] = strings[i];
            }

            std::copy(std::begin(aux), std::end(aux), strings.begin());
        }
    }




    static int charAt(const std::string& str, uint32_t d){
        if(d < str.length())
            return str.at(d); 
        else
            return -1;
    }

    static void msdSort(stringArray& strings, stringArray& aux, int32_t lo, int32_t hi, uint32_t d);

    void MSDStringRadixSort( stringArray& strings ){

        stringArray aux(strings.size());
        msdSort(strings, aux, 0, strings.size()-1, 0);
        /*uint32_t alphabetSize = 256;
        uint32_t stringsCount = strings.size();*/
    }

    static void msdSort(stringArray& strings, stringArray& aux, int32_t lo, int32_t hi, uint32_t d){
        if(hi <= lo)
            return;

        uint32_t alphabetSize = 256;
        std::vector<uint32_t> count(alphabetSize+2, 0);

        for(int32_t i = lo; i <=hi; ++i){
            count[charAt(strings[i], d) + 2]++;
        }

        for(uint32_t i = 0; i <alphabetSize+1; ++i){
            count[i+1]+= count[i];
        }

        for(int32_t i = lo; i <=hi; ++i){
            aux[count[charAt(strings[i], d) + 1]++] = strings[i];
        }

        for(int32_t i = lo; i <=hi; ++i){
            strings[i] = aux[i-lo];
        }

        for(uint32_t r =0; r < alphabetSize; ++r){
            msdSort(strings, aux, lo + count[r], lo + count[r+1] -1, d + 1);
        }
    }

    static void threeWayInnerSort(stringArray& strings, int32_t lo, int32_t hi, uint32_t d){
        if(lo >= hi)
            return;

        int32_t lt = lo;
        int32_t gt = hi;
        int32_t v = charAt(strings[lo], d);

        int32_t i = lo + 1;
        while(i <= gt){
            int32_t t = charAt(strings[i], d);
            if(t < v){
                std::cout << "swap " << strings[lt] << " and " << strings[i] << " cuz sign no " << d << std::endl;
                std::swap(strings[lt++], strings[i++]);
            }
            else if(t > v)
            {
                std::cout << "swap " << strings[gt] << " and " << strings[i] << " cuz sign no " << d << std::endl;
                std::swap(strings[gt--], strings[i]);
            }
            else
                i++;
        }

        threeWayInnerSort(strings, lo, lt-1, d);
        if(v>=0){
            threeWayInnerSort(strings, lt, gt, d+1);
        }
        threeWayInnerSort(strings, gt+1, hi, d);
    }



    void threeWayInnerSort(stringArray& strings){
        threeWayInnerSort(strings, 0, strings.size() -1, 0);
    }

}