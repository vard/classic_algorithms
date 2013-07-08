#pragma once

#include "boost/shared_ptr.hpp"
#include "boost/cstdint.hpp"
#include <iostream>

using namespace std;
using namespace boost;

namespace union_find{

    class QuickFindUF{
    private:
        boost::shared_ptr<uint32_t[]> id;
        uint32_t count;
    public:
        QuickFindUF(uint32_t itemsCount);
        bool connected(uint32_t p, uint32_t q);
        void unionItems(uint32_t p, uint32_t q); 

        friend std::ostream& operator<<(std::ostream& outStream, const QuickFindUF& rhs);
    };

    class QuickUnionUF{
    private:
        uint32_t count;
        boost::shared_ptr<uint32_t[]> id;
        uint32_t root(uint32_t index);
    public:
        QuickUnionUF(uint32_t itemsCount);
        bool connected(uint32_t p, uint32_t q);
        void unionItems(uint32_t p, uint32_t q);

        friend std::ostream& operator<<(std::ostream& outStream, const QuickUnionUF& rhs);
    };

    class WeightedQuickUnionUF{
    private:
        uint32_t count;
        boost::shared_ptr<uint32_t[]> id;
        boost::shared_ptr<uint32_t []> sz;
        uint32_t root(uint32_t index);
    public:
        WeightedQuickUnionUF(uint32_t itemsCount);
        bool connected(uint32_t p, uint32_t q);
        void unionItems(uint32_t p, uint32_t q);

        friend std::ostream& operator<<(std::ostream& outStream, const WeightedQuickUnionUF& rhs);
    };



}