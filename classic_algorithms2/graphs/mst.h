#pragma once

#include <iostream>
#include <fstream>
#include <deque>
#include "boost/cstdint.hpp"
#include "boost/shared_ptr.hpp"

using namespace std;
using namespace boost;

namespace mst{

class Edge{
private:
    double weight;
    uint32_t v;
    uint32_t w;
public:
    Edge(uint32_t firstVertex, uint32_t secondVertex, double edgeWeight);
    uint32_t either() const;
    uint32_t other(uint32_t vertex) const;
    double getWeight() const;

    bool operator<(const Edge& rhs);
    bool operator==(const Edge& rhs);
    bool operator>(const Edge& rhs);
    friend ostream& operator<<(ostream& outStream, const Edge& edge);
};

class EdgeWeightedGraph{
private:
    uint32_t vertexCount;
    uint32_t edgesCount;
    boost::shared_ptr<std::deque<Edge>[]> adjacencyLists;
public:
    EdgeWeightedGraph(uint32_t vertices);
    EdgeWeightedGraph(std::ifstream& inputStream);
    uint32_t getVertexCount() const;
    uint32_t getEdgesCount() const;
    std::deque<Edge> adjacent(uint32_t vertex) const;
    std::deque<Edge> edges() const;
    void addEdge(const Edge& edge);
};

void printWeightedGraph(const EdgeWeightedGraph& graph);


class MST{
public:
    virtual std::deque<Edge> edges() = 0;
    double weight();
};


} // namespace mst
