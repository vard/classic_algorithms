#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <deque>
#include <stack>
#include "boost/cstdint.hpp"
#include "boost/shared_ptr.hpp"
#include "graphs/graph.h"

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

    
    class DigraphDFSPaths : public graph::PathsInterface{
    private:
        boost::shared_ptr<uint32_t []> edgeTo;
        boost::shared_ptr<bool[]> marked;
        void dfs(const Digraph& digraph, uint32_t vertex);
        uint32_t vertexCount;
        uint32_t dfsSource;
    public:
        DigraphDFSPaths(const Digraph& digraph, uint32_t source);
        virtual bool hasPathTo(unsigned int vertex);
        virtual bool pathTo(unsigned int vertex, std::deque<int>& path);
     };

    class DigraphBFSPaths : public graph::PathsInterface{
    private:
        boost::shared_ptr<bool []> marked;
        boost::shared_ptr<uint32_t[]> edgeTo;
        uint32_t vertexCount;
        uint32_t bfsSource;
        void bfs(const Digraph& graph, uint32_t source);
    public:
        DigraphBFSPaths(const Digraph& graph, uint32_t source);
        virtual bool hasPathTo(unsigned int vertex);
        virtual bool pathTo(unsigned int vertex, std::deque<int>& path);
    };

    // topological order
    class DepthFirstOrder{
    private:
        boost::shared_ptr<bool[]> marked;
        std::stack<uint32_t> reversePost;
        void dfs(const Digraph& graph, uint32_t vertex);
    public:
        DepthFirstOrder(const Digraph& graph);
        bool reversePost(std::deque<uint32_t>& vertexes);
    };

}