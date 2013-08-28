#pragma once
#include "boost/cstdint.hpp"
#include "indexed_priority_queue.h"
#include <iostream>
#include <fstream>
#include <deque>
#include <set>
#include <vector>
#include <queue>
#include <map>

using namespace boost;
using namespace std;
using namespace indexed_pq;

namespace spt{

    class DirectedEdge{
    private:
        uint32_t v;
        uint32_t w;
        double weight;
    public:
        DirectedEdge();
        DirectedEdge(uint32_t from, uint32_t to, double weigth);
        DirectedEdge& operator=(const DirectedEdge& other);
        uint32_t from() const;
        uint32_t to() const;
        double getWeight() const;
        bool operator<(const DirectedEdge& rhs);

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
        std::deque<DirectedEdge> adjacent(uint32_t vertex) const;
        uint32_t getVertexCount() const;
        uint32_t getEdgeCount() const;
        std::deque<DirectedEdge> edges() const;
    };

    struct CompareDistance : public std::binary_function<double, double, bool>
    {
        bool operator()(const double& _Left, const double& _Right) const
        {
            return (_Left > _Right);
        }
    };



    // будем имплементировать только алгоритм Дейкстры
    // породим от интерфейса единственный класс и вперед
    class ShortestPathInterface{
    private:
    public:
        virtual double distTo(uint32_t v) = 0;
        virtual std::deque<DirectedEdge> pathTo(uint32_t v) = 0;
        //virtual bool hasPathTo(uint32_t v) = 0;
    };

    class DijkstraSPT : public ShortestPathInterface{
    private:
        std::vector<DirectedEdge> edgeTo;
        std::vector<double> distanceTo;
        boost::shared_ptr<indexed_pq::IndexedPQ<double> > pq;
        uint32_t source;
        void relax(const DirectedEdge& edge);
    public:
        DijkstraSPT(const EdgeWeightedDigraph& digraph, uint32_t source);
        virtual double distTo(uint32_t v);
        virtual std::deque<DirectedEdge> pathTo(uint32_t v);
        //virtual bool hasPathTo(uint32_t v);
    };
    

    class BellmanFordSPT : public ShortestPathInterface{
    private:
        typedef std::deque<DirectedEdge> DirectedEdges;
        std::deque<uint32_t> verticesDistancetoChanged;
        std::deque<double> distanceTo;
        DirectedEdges edgeTo;
        void relax(const DirectedEdge& edge);
        uint32_t src;
    public:
        BellmanFordSPT(const EdgeWeightedDigraph& digraph, uint32_t source);
        virtual double distTo( uint32_t v );
        virtual std::deque<DirectedEdge> pathTo( uint32_t v );
    };

}