#include "graphs/digraph.h"

namespace digraph{

    Digraph::Digraph(std::ifstream &inputStream){
        inputStream >> std::dec >> vertexCount;
        adjacencyList = boost::shared_ptr<std::set<uint32_t>[]>(new std::set<uint32_t>[vertexCount]);

        while(!inputStream.eof()){
            uint32_t v, w;
            inputStream >> v >> w;
            addEdge(v , w);
        }
    }

    Digraph::Digraph(uint32_t vertexCount)
        :adjacencyList(new std::set<uint32_t>[vertexCount]),
         vertexCount(vertexCount) {
    }

    void Digraph::addEdge(boost::uint32_t v, boost::uint32_t w){
        adjacencyList[v].insert(w);
    }

    uint32_t Digraph::vertices() const{
        return vertexCount;
    }

    std::set<uint32_t> Digraph::adjacent(boost::uint32_t vertex) const{
        //std::vector<uint32_t> adjacentVec(adjacencyList[vertex].size());
        //std::copy(adjacencyList[vertex].begin(), adjacencyList[vertex].end(), adjacentVec.begin());
        return adjacencyList[vertex];
    }


}