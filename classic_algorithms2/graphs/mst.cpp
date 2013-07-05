#include "graphs/mst.h"
#include <iomanip>

namespace mst{

    Edge::Edge(uint32_t firstVertex, uint32_t secondVertex, double edgeWeight)
        :weight(edgeWeight),
        v(firstVertex),
        w(secondVertex){
    }

    uint32_t Edge::either() const{
        return  v;
    }

    uint32_t Edge::other(boost::uint32_t vertex) const{
        if(v == vertex)
            return w;
        else
            return v;
    }

    double Edge::getWeight() const{
        return weight;
    }

    bool Edge::operator<(const Edge &rhs){
        if(weight < rhs.getWeight())
            return true;
        return false;
    }

    bool Edge::operator==(const Edge& rhs){
        if(weight == rhs.getWeight())
            return true;
        return false;
    }

    bool Edge::operator>(const Edge& rhs){
        if( (*this == rhs) || (*this < rhs))
            return false;
        return true;
    }

    EdgeWeightedGraph::EdgeWeightedGraph(boost::uint32_t vertices)
        :vertexCount(vertices),
         edgesCount(0),
         adjacencyLists(new deque<Edge>[vertices]){
    }

    EdgeWeightedGraph::EdgeWeightedGraph(std::ifstream &inputStream){
        inputStream >> std::dec >> vertexCount;
        edgesCount = 0;
        adjacencyLists = boost::shared_ptr<std::deque<Edge>[]>(new std::deque<Edge>[vertexCount]);
        while(!inputStream.eof()){
            uint32_t v, w;
            double edgeWeight;
            inputStream >> v >> w >> edgeWeight;
            Edge newEdge(v , w, edgeWeight);
            addEdge(newEdge);            
        }
    }

    void EdgeWeightedGraph::addEdge(const Edge& edge){
        uint32_t v = edge.either();
        adjacencyLists[v].push_back(edge);
        adjacencyLists[edge.other(v)].push_back(edge);
        ++edgesCount;
    }

    uint32_t EdgeWeightedGraph::getEdgesCount() const{
        return edgesCount;
    }

    uint32_t EdgeWeightedGraph::getVertexCount() const{
        return vertexCount;
    }

    std::deque<Edge> EdgeWeightedGraph::adjacent(uint32_t vertex) const{
        return adjacencyLists[vertex];
    }

    std::deque<Edge> EdgeWeightedGraph::edges() const{
        std::deque<Edge> allEdges;
        for(uint32_t v = 0; v < vertexCount; ++v){
            std::deque<Edge> adj = adjacent(v);
            for(std::deque<Edge>::iterator iter = adj.begin(); iter != adj.end(); ++iter){
                if((*iter).other(v) >= v){
                    allEdges.push_back(*iter);
                }
            }
        }  
        return allEdges;
    }

    void printWeightedGraph(const EdgeWeightedGraph& graph){
        uint32_t vertices = graph.getVertexCount();
        std::deque<Edge> allEdges = graph.edges();
        for(std::deque<Edge>::iterator iter = allEdges.begin(); iter != allEdges.end(); ++iter){
            uint32_t v = (*iter).either();
            std::cout << setw(2) << v << setw(2) <<" - " << setw(2) << (*iter).other(v) << " " << setw(8) << right << (*iter).getWeight() << std::endl;
        }


        /*for(uint32_t v = 0; v < vertices; ++v){
            std::deque<Edge> adj = graph.adjacent(v);
            for(std::deque<Edge>::iterator iter = adj.begin(); iter != adj.end(); ++iter){
                std::cout << setw(2) << v << setw(2) <<" - " << setw(2) << (*iter).other(v) << " " << setw(8) << right << (*iter).getWeight() << std::endl;

            }
        }*/
    }


}