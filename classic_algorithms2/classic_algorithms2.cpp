#if defined  _WIN32
#include "stdafx.h"
#endif

#ifdef _WIN64
#include "stdafx.h"
#endif

#include "graphs/graph.h"
#include "graphs/digraph.h"
#include "graphs/mst.h"
#include "graphs/shortest_path.h"
#include <iostream>
#include <fstream>

using namespace graph;
using namespace digraph;
using namespace std;
using namespace mst;
using namespace spt;

#ifdef _WIN64
int _tmain(int argc, _TCHAR* argv[])
#endif

#ifdef _WIN32
    int _tmain(int argc, _TCHAR* argv[])
#endif

#ifdef __linux__
    int main(int argc, char** argv)
#endif

{
    std::ifstream vertexFile;
    try{
        vertexFile.open("vertexes.txt", std::ifstream::in);
    } catch(std::ifstream::failure e){
        std::cerr << "Exception opening file\n";
    }
    graph::Graph socialNetFriends(vertexFile);
    vertexFile.close();
    for(unsigned int vertex = 0; vertex < socialNetFriends.vertices(); vertex++){
        std::vector<int> adjacent = socialNetFriends.adjacent(vertex);
        for(std::vector<int>::iterator iter = adjacent.begin(); iter != adjacent.end(); iter++)
            cout << vertex <<  " - " << *iter << endl;
    }

    // use dfs to find all paths from 0
    std::cout << "DFS results:" << std::endl;
    unsigned int source = 0;
    graph::DepthFirstSearchPaths paths(socialNetFriends, source);
    for(unsigned int vertex = 0; vertex < socialNetFriends.vertices(); vertex++){
        std::deque<int> path;
        if(paths.hasPathTo(vertex)){
            paths.pathTo(vertex, path);
            std::cout << "Path to " << vertex << ":";
            for(std::deque<int>::iterator iter = path.begin(); iter != path.end(); ++iter){
                std::cout << " " << *iter;
            }
            std::cout << std::endl;
        }
    }

    // use dfs to find all paths from 0
    std::cout << "BFS results:" << std::endl;
    unsigned int bfsSource = 0;
    graph::BreadthFirstSearchPaths bfsPaths(socialNetFriends, bfsSource);
    for(unsigned int vertex = 0; vertex < socialNetFriends.vertices(); vertex++){
        std::deque<int> path;
        if(bfsPaths.hasPathTo(vertex)){
            bfsPaths.pathTo(vertex, path);
            std::cout << "Path to " << vertex << ":";
            for(std::deque<int>::iterator iter = path.begin(); iter != path.end(); ++iter){
                std::cout << " " << *iter;
            }
            std::cout << std::endl;
        }
    }

    std::cout << "Connected components results:" << std::endl;
    graph::CC connectedComponents(socialNetFriends);
    std::cout.width(12);
    std::cout << "Vertex: ";
    for(unsigned int v = 0; v < socialNetFriends.vertices(); v++){
        std::cout << v << " ";
    }
    std::cout << std::endl;
    std::cout.width(12);
    std::cout << "Component: ";
    for(unsigned int v = 0; v < socialNetFriends.vertices(); v++){
        std::cout << connectedComponents.getId(v) << " ";
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::ifstream digraphFile;
    try{
        digraphFile.open("digraph.txt", std::ifstream::in);
    } catch(std::ifstream::failure e){
        std::cerr << "Exception opening file\n";
    }

    // Directed graph
    std::cout << "Directed graph:" << std::endl;
    digraph::Digraph regionMap(digraphFile);
    digraphFile.close();
    for(uint32_t v = 0; v < regionMap.vertices(); v++){
        std::set<uint32_t> adj = regionMap.adjacent(v);
        for(std::set<uint32_t>::iterator iter = adj.begin(); iter != adj.end(); ++iter){
            std::cout << v << " -> " << *iter << std::endl;
        }
    }

    // DFS
    std::cout << "DFS:\n";
    digraph::DigraphDFSPaths routes(regionMap, 0);
    for(uint32_t v = 0; v < regionMap.vertices(); v++){
        if(routes.hasPathTo(v)){
            std::deque<int> routeFound;
            routes.pathTo(v , routeFound);
            std::cout << "Path to " << v << ":";
            for(std::deque<int>::iterator iter = routeFound.begin(); iter != routeFound.end(); ++iter){
                std::cout << " " << *iter;
            }
            std::cout << std::endl;

        }

    }

    // BFS
    std::cout << "BFS:\n";
    digraph::DigraphBFSPaths bfsRoutes(regionMap, 0);
    for(uint32_t v = 0; v < regionMap.vertices(); v++){
        if(bfsRoutes.hasPathTo(v)){
            std::deque<int> routeFound;
            bfsRoutes.pathTo(v , routeFound);
            std::cout << "Path to " << v << ":";
            for(std::deque<int>::iterator iter = routeFound.begin(); iter != routeFound.end(); ++iter){
                std::cout << " " << *iter;
            }
            std::cout << std::endl;
        }
    }

    // Topological order
    std::cout << "Topological order\n";
    digraph::DepthFirstOrder topologicalSort(regionMap);
    std::deque<uint32_t> routeTraversal = topologicalSort.reversePost();
    for(std::deque<uint32_t>::iterator iter = routeTraversal.begin(); iter != routeTraversal.end(); ++iter){
        std::cout << *iter << " -> ";
    }
    std::cout << std::endl;

    // Strong connected components
    std::cout << "Strong CC:\n";
    digraph::KosarajuSharirSCC strongComponents(regionMap);
    std::cout.width(12);
    std::cout << "Vertex: ";
    for(unsigned int v = 0; v < regionMap.vertices(); v++){
        std::cout << v << " ";
    }
    std::cout << std::endl;
    std::cout.width(12);
    std::cout << "Component: ";
    for(unsigned int v = 0; v < regionMap.vertices(); v++){
        std::cout << strongComponents.getId(v) << " ";
    }
    std::cout << std::endl;

    std::ifstream weightedDigraphFile;
    try{
        weightedDigraphFile.open("weighted_digraph.txt", std::ifstream::in);
    } catch(std::ifstream::failure e){
        std::cerr << "Exception opening file\n";
    }

    // Weighted undirected graph
    std::cout << "Undirected weighted graph:" << std::endl;
    mst::EdgeWeightedGraph roadMap(weightedDigraphFile);
    mst::printWeightedGraph(roadMap);

    // Minimum spanning tree
    std::cout << "Minimum spanning tree (Kruskal) \n";
    mst::MST* mst = new mst::KruskalMST(roadMap);
    std::deque<mst::Edge> mstEdges = mst->edges();
    for(std::deque<mst::Edge>::const_iterator citer = mstEdges.begin(); citer != mstEdges.end(); ++citer){
        std::cout << *citer << std::endl;
    }
    delete mst;

    std::cout << "Minimum spanning tree (Prim, lazy approach) \n";
    mst = new mst::LazyPrimMST(roadMap);
    std::deque<mst::Edge> lazyPrimMstEdges = mst->edges();
    for(std::deque<mst::Edge>::const_iterator citer = lazyPrimMstEdges.begin(); citer != lazyPrimMstEdges.end(); ++citer){
        std::cout << *citer << std::endl;
    }  
    delete mst;

    weightedDigraphFile.seekg(0, ios::beg);


    std::cout << "Directed weighted digraph:\n";
    spt::EdgeWeightedDigraph someMap(weightedDigraphFile);
    std::deque<spt::DirectedEdge> someMapEdges = someMap.edges();
    for(auto it = std::begin(someMapEdges); it != std::end(someMapEdges); ++it){
        std::cout << *it << std::endl;
    }

    weightedDigraphFile.close();

    {
        spt::DijkstraSPT djikstraShortestPath(someMap, 0);
        uint32_t destVertex = 5;
        std::deque<spt::DirectedEdge> shortestPath =  djikstraShortestPath.pathTo(destVertex);
        std::cout << "Shortest path to " << destVertex << std::endl;
        for(auto it = std::begin(shortestPath); it != std::end(shortestPath); ++it){
            std::cout << it->from() << " -> " << it->to() << " " << it->getWeight() << std::endl;
        }
    }


    {
        spt::BellmanFordSPT bellmanFordShortestPath(someMap, 0);
        uint32_t destVertex = 8;
        std::deque<spt::DirectedEdge>  shortestPath =  bellmanFordShortestPath.pathTo(destVertex);
        std::cout << "Shortest path(Bellman-Ford) to " << destVertex << std::endl;
        for(auto it = std::begin(shortestPath); it != std::end(shortestPath); ++it){
            std::cout << it->from() << " -> " << it->to() << " " << it->getWeight() << std::endl;
        }
    }


    return 0;
}


