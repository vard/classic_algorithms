#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <set>
#include <vector>
#include <deque>
#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>


#include "graphs/graph.h"
using namespace std;

namespace graph{
    class Graph{
    private:
        unsigned int vertexCount;
        boost::shared_ptr<std::set<int>[]> adj;
           
    public:
        Graph(unsigned int vertices);
        Graph(std::ifstream& inputStream);
        unsigned int vertices() const;
        unsigned int edges();
        void addEdge(unsigned int v, unsigned int w);
        std::vector<int> adjacent(int vertex) const;
    };

   class PathsInterface{
   public:       
       virtual bool hasPathTo(unsigned int vertex) = 0;
       virtual bool pathTo(unsigned int vertex, std::deque<int>& path) = 0;
       virtual ~PathsInterface();
   };

   class DepthFirstSearchPaths : public PathsInterface{
   private:
       boost::shared_ptr<bool[]> marked;
       boost::shared_ptr<int[]> edgeTo;
       unsigned int source;
       void dfs(const Graph& graph, unsigned int vertex);
   public:
       virtual bool hasPathTo(unsigned int vertex);
       virtual bool pathTo(unsigned int vertex, std::deque<int>& path);
       DepthFirstSearchPaths(const Graph& graph, unsigned int sourceVertex);
       virtual ~DepthFirstSearchPaths();
   };

   class BreadthFirstSearchPaths : public PathsInterface{
   private:
       boost::shared_ptr<bool[]> marked;
       boost::shared_ptr<int[]> edgeTo;
       unsigned int source;
       void bfs(const Graph& graph, unsigned int vertex);
   public:
       virtual bool hasPathTo(unsigned int vertex);
       virtual bool pathTo(unsigned int vertex, std::deque<int>& path);
       BreadthFirstSearchPaths(const Graph& graph, unsigned int sourceVertex);
       virtual ~BreadthFirstSearchPaths();
   };
}

#endif