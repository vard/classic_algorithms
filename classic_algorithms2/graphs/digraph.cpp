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
        return adjacencyList[vertex];
    }

    DigraphDFSPaths::DigraphDFSPaths(const Digraph &digraph, boost::uint32_t source){
        vertexCount = digraph.vertices();
        marked = shared_ptr<bool []>(new bool[vertexCount]());
        edgeTo = shared_ptr<uint32_t []>(new uint32_t[vertexCount]); 
        dfsSource = source;
        dfs(digraph, source);
    }

    void DigraphDFSPaths::dfs(const digraph::Digraph &digraph, boost::uint32_t vertex){
        std::set<uint32_t> adjVertexes = digraph.adjacent(vertex);
        marked[vertex] = true;  
        for(std::set<uint32_t>::iterator iter = adjVertexes.begin(); iter != adjVertexes.end(); ++iter){
            if(!marked[*iter]){                
                edgeTo[*iter] = vertex;
                dfs(digraph, *iter);

            }
        }
    }

    bool DigraphDFSPaths::hasPathTo(unsigned int vertex){
        if(vertex > vertexCount)
            return false;
        return marked[vertex];
    }

    bool DigraphDFSPaths::pathTo(unsigned int vertex, std::deque<int>& path){
        if((vertex > vertexCount) | (!marked[vertex]))
            return false;

        for(int v = vertex; v != dfsSource; v = edgeTo[v]){
            path.push_front(v);
        }
        path.push_front(dfsSource);
        return true;
    }


}