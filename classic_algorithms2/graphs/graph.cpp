#include <boost/shared_ptr.hpp>
#include <queue>
#include "graphs/graph.h"

using namespace std;

namespace graph {

    Graph::Graph(std::ifstream& inputStream) {
        inputStream >> std::dec >> vertexCount;
        adj = boost::shared_ptr < std::set<int>[]>(new std::set<int>[vertexCount]);
        while (!inputStream.eof()) {
            int v, w;
            inputStream >> std::dec >> v >> w;
            addEdge(v, w);
        }
    }

    Graph::Graph(unsigned int vertices)
    : adj(new std::set<int>[vertices]),
    vertexCount(vertices) {

    }

    void Graph::addEdge(unsigned int v, unsigned int w) {
        adj[v].insert(w);
        adj[w].insert(v);
    }

    unsigned int Graph::vertices() const {
        return vertexCount;
    }

    unsigned int Graph::edges() {
        unsigned int edgeCount = 0;
        for (unsigned int vertex = 0; vertex < vertexCount; vertex++) {
            edgeCount += adj[vertex].size();
        }
        return edgeCount / 2;
    }

    std::vector<int> Graph::adjacent(int vertex) const {
        std::vector<int> adjacentVertexes;
        for (std::set<int>::iterator iter = adj[vertex].begin(); iter != adj[vertex].end(); ++iter)
            adjacentVertexes.push_back(*iter);
        return adjacentVertexes;
    }

    PathsInterface::~PathsInterface() {

    }

    DepthFirstSearchPaths::DepthFirstSearchPaths(const Graph& graph, unsigned int sourceVertex)
    : source(sourceVertex) {
        marked = boost::shared_ptr<bool[]>(new bool[graph.vertices()]());
        edgeTo = boost::shared_ptr<int[]>(new int[graph.vertices()]);
        dfs(graph, source);
    }

    void DepthFirstSearchPaths::dfs(const Graph& graph, unsigned int vertex) {
        marked[vertex] = true;
        std::vector<int> adjVertices = graph.adjacent(vertex);
        for (std::vector<int>::iterator iter = adjVertices.begin(); iter != adjVertices.end(); ++iter) {
            if (!marked[*iter]) {
                dfs(graph, *iter);
                edgeTo[*iter] = vertex;
            }

        }
    }

    DepthFirstSearchPaths::~DepthFirstSearchPaths() {

    }

    bool DepthFirstSearchPaths::hasPathTo(unsigned int vertex) {
        return true == marked[vertex];
    }

    bool DepthFirstSearchPaths::pathTo(unsigned int vertex, std::deque<int>& path) {
        if (hasPathTo(vertex)) {
            for (unsigned int x = vertex; x != source; x = edgeTo[x]) {
                (path).push_front(x);
            }
            (path).push_front(source);
            return true;

        }
        return false;

    }

    BreadthFirstSearchPaths::BreadthFirstSearchPaths(const Graph& graph, unsigned int sourceVertex)
    : source(sourceVertex) {
        marked = boost::shared_ptr<bool[]>(new bool[graph.vertices()]());
        edgeTo = boost::shared_ptr<int[]>(new int[graph.vertices()]);
        bfs(graph, source);
    }

    void BreadthFirstSearchPaths::bfs(const Graph& graph, unsigned int vertex) {
        marked[vertex] = true;
        std::queue<int> vertexQ;
        vertexQ.push(vertex);
        marked[vertex] = true;

        while (!vertexQ.empty()) {
            int newVertex = vertexQ.front();
            vertexQ.pop();
            std::vector<int> adjVertices = graph.adjacent(newVertex);
            for (std::vector<int>::iterator iter = adjVertices.begin(); iter != adjVertices.end(); ++iter) {
                if (!marked[*iter]) {
                    marked[*iter] = true;
                    vertexQ.push(*iter);
                    edgeTo[*iter] = newVertex;
                }
            }
        }
    }

    bool BreadthFirstSearchPaths::hasPathTo(unsigned int vertex) {
        return marked[vertex];
    }

    bool BreadthFirstSearchPaths::pathTo(unsigned int vertex, std::deque<int>& path) {
        if (hasPathTo(vertex)) {
            for (unsigned int x = vertex; x != source; x = edgeTo[x]) {
                (path).push_front(x);
            }
            (path).push_front(source);
            return true;

        }
        return false;
    }

    BreadthFirstSearchPaths::~BreadthFirstSearchPaths() {

    }
    
    CC::CC(const Graph& graph)
    :count(0){
        marked = boost::shared_ptr<bool[]>(new bool[graph.vertices()]());
        id = boost::shared_ptr<unsigned int[]>(new unsigned int[graph.vertices()]);

        for(unsigned int v = 0; v < graph.vertices(); v++){
            if(!marked[v]){
                dfs(graph, v);
                count++;
            }
        }
    }
    
    void CC::dfs(const Graph& graph, unsigned int vertex){
        id[vertex] = count;
        marked[vertex] = true;
        std::vector<int> adjVertex = graph.adjacent(vertex);
        for(std::vector<int>::iterator iter = adjVertex.begin(); iter != adjVertex.end(); ++iter){
            if(!marked[*iter]){                
                marked[*iter] = true;
                dfs(graph, *iter);
            }
        }
        
    }
    
    unsigned int CC::getCount(){
        return count;
    }
    
    unsigned int CC::getId(unsigned int vertex){
        return id[vertex];
    }

}

