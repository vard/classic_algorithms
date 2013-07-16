#pragma once
#include "boost/cstdint.hpp"
#include <iostream>
#include <fstream>
#include <deque>
#include <set>
#include <vector>

using namespace boost;
using namespace std;

namespace spt{

    class DirectedEdge{
    private:
        uint32_t v;
        uint32_t w;
        double weight;
    public:
        DirectedEdge(uint32_t from, uint32_t to, double weigth);
        DirectedEdge& operator=(const DirectedEdge& other);
        uint32_t from() const;
        uint32_t to() const;
        double weigth() const;

        friend std::ostream& operator<<(std::ostream& out, const DirectedEdge& dirEdge); 
    };

    class EdgeWeightedDigraph{
    private:
        uint32_t vertexCount;
        uint32_t edgeCount;
        std::vector<std::deque<DirectedEdge> > adjacentList;
    public:
        EdgeWeightedDigraph(uint32_t vertexCount);
        EdgeWeightedDigraph(std::ifstream& inputStream);
        void addEdge(const DirectedEdge& edge);
        std::deque<DirectedEdge> adjacent(uint32_t vertex);
        uint32_t getVertexCount();
        uint32_t getEdgeCount();
        std::deque<DirectedEdge> edges();
    };

    class ShortestPathInterface{
    private:
        void relax(const DirectedEdge& edge);        
    public:
        double distTo(uint32_t v);
        std::vector<DirectedEdge> pathTo(uint32_t v);
        bool hasPathTo(uint32_t v);

    };



}