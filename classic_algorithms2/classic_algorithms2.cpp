#if defined  _WIN32
#include "stdafx.h"
#endif

#ifdef _WIN64
#include "stdafx.h"
#endif

#include "graphs/graph.h"
#include <iostream>
#include <fstream>

using namespace graph;
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


    return 0;
}

