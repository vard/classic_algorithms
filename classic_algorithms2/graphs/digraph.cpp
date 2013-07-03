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

    Digraph Digraph::reverse(){
        Digraph reversedDigraph(vertexCount);
        for(uint32_t v = 0; v < vertexCount; v++){
            std::set<uint32_t> adj = reversedDigraph.adjacent(v);
            for(std::set<uint32_t>::iterator iter = adj.begin(); iter != adj.end(); ++iter){
                reversedDigraph.addEdge(*iter, v);
            }
            //std::for_each(adj.begin(), adj.end(), reversedDigraph.addEdge(                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
        }
    return reversedDigraph;
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

    DigraphBFSPaths::DigraphBFSPaths(const digraph::Digraph &graph, boost::uint32_t source){
        vertexCount = graph.vertices();
        bfsSource = source;
        marked = boost::shared_ptr<bool[]>(new bool[vertexCount]());
        edgeTo = boost::shared_ptr<uint32_t[]>(new uint32_t[vertexCount]);
        bfs(graph, source);
    }

    void DigraphBFSPaths::bfs(const digraph::Digraph &graph, boost::uint32_t source){
        std::deque<uint32_t> vertexQ;
        vertexQ.push_back(source);
        marked[source] = true;

        while(!vertexQ.empty()){
            uint32_t vertex = vertexQ.front();
            vertexQ.pop_front();


            std::set<uint32_t> adjacent = graph.adjacent(vertex);
            for(std::set<uint32_t>::iterator iter = adjacent.begin(); iter != adjacent.end(); ++iter){
                if(!marked[*iter]){
                    marked[*iter] = true;
                    edgeTo[*iter] = vertex;
                    vertexQ.push_back(*iter);
                }
            }
        }
    }

    bool DigraphBFSPaths::hasPathTo(unsigned int vertex){
        if(vertex > vertexCount)
            return false;
        return marked[vertex];
    }

    bool DigraphBFSPaths::pathTo(unsigned int vertex, std::deque<int>& path){
        if(!marked[vertex])
            return false;

        for(uint32_t v = vertex; v != bfsSource; v = edgeTo[v]){
            path.push_front(v);
        }
        path.push_front(bfsSource);
        return true;
    }

    DepthFirstOrder::DepthFirstOrder(const Digraph &graph)
        :marked(new bool[graph.vertices()]()),
        reversePostOrder(new std::deque<uint32_t>){
            uint32_t vertexes = graph.vertices();
            for(uint32_t v = 0; v < vertexes; ++v){
                if(!marked[v]){
                    dfs(graph, v);
                }
            }
    }

    void DepthFirstOrder::dfs(const digraph::Digraph &graph, boost::uint32_t vertex){
        marked[vertex] = true;
        std::set<uint32_t> adjacent = graph.adjacent(vertex);
        for(std::set<uint32_t>::iterator iter = adjacent.begin(); iter != adjacent.end(); ++iter){
            if(!marked[*iter]){
                dfs(graph, *iter);    
            }
        }        
        (*reversePostOrder).push_front(vertex); 
    }

    std::deque<uint32_t> DepthFirstOrder::reversePost() const{
        return *reversePostOrder;

    }


}