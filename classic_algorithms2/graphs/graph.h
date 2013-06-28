#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <set>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "graphs/graph.h"
using namespace std;

namespace graph{
    class Graph{
    private:
        const unsigned int vertexCount;
        boost::shared_ptr<std::set<int>[]> adj;
           
    public:
        Graph(unsigned int vertices);
        unsigned int vertices();
        unsigned int edges();
        void addEdge(unsigned int v, unsigned int w);
        std::vector<int>& adjacent(int vertex);
    };

    Graph::Graph(unsigned int vertices)
        :adj(new std::set<int>[vertices]),
        vertexCount(vertices)
    {

    }

    void Graph::addEdge(unsigned int v, unsigned int w){
        adj[v].insert(w);
        adj[w].insert(v);
    }

    unsigned int Graph::vertices(){
        return vertexCount;
    }

    // TODO: fix
    unsigned int Graph::edges(){
        return 0;
    }
}

#endif