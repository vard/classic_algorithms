#if defined  _WIN32
#include "stdafx.h"
#endif

#ifdef _WIN64
#include "stdafx.h"
#endif

#include "graphs/graph.h"
#include "graphs/digraph.h"
#include <iostream>
#include <fstream>

using namespace graph;
using namespace digraph;
using namespace std;

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

    

    return 0;
}

