#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "boost/cstdint.hpp"
#include "boost/shared_ptr.hpp"

using namespace std;
using namespace boost;

namespace digraph{

    class Digraph{
    private:
        uint32_t vertexCount;
        boost::shared_ptr<std::set<uint32_t>[]> adjacencyList;

    public:
        Digraph(uint32_t vertexCount);
        Digraph(std::ifstream& inputStream);
        void addEdge(uint32_t v, uint32_t w);
        std::set<uint32_t> adjacent(uint32_t vertex) const;
        uint32_t vertices() const;
        uint32_t edges() const;
        Digraph reverse();

    };

}