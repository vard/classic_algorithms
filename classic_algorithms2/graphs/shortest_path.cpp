#include "shortest_path.h"
#include <iomanip>
#include <iterator>

namespace spt{

    DirectedEdge::DirectedEdge(uint32_t from, uint32_t to, double edgeWeigth)
        : v(from),
        w(to),
        weight(edgeWeigth){

    }

    uint32_t DirectedEdge::from() const{
        return v;
    }

    uint32_t DirectedEdge::to() const{
        return w;
    }

    double DirectedEdge::weigth() const{
        return weight;
    }

    DirectedEdge& DirectedEdge::operator=(const DirectedEdge& other){
        this->v = other.v;
        this->w = other.w;
        this->weight = other.weight;
        return *this;
    }

    std::ostream& operator<<(std::ostream& out, const DirectedEdge& dirEdge){
        out << std::setw(2) << dirEdge.from() << " -> " << std::setw(2) <<  dirEdge.to() << " " << std::setw(8) <<  dirEdge.weigth();
        return out;
    }

    uint32_t EdgeWeightedDigraph::getEdgeCount(){
        return edgeCount;
    }

    uint32_t EdgeWeightedDigraph::getVertexCount(){
        return vertexCount;
    }
    
    EdgeWeightedDigraph::EdgeWeightedDigraph(uint32_t vertexCount)
    :vertexCount(vertexCount){
        adjacentList.resize(vertexCount);
    }

    EdgeWeightedDigraph::EdgeWeightedDigraph(std::ifstream& inputStream){
        
        inputStream >> std::dec >> vertexCount;       
        uint32_t v = 0, w = 0;
        double weight;

        adjacentList.resize(vertexCount);

        while(!inputStream.eof()){
            inputStream >> std::dec >> v >> w >> weight;
            DirectedEdge dirEdge(v, w, weight);
            addEdge(dirEdge);
        }        
    }

    void EdgeWeightedDigraph::addEdge(const DirectedEdge& edge){
        adjacentList[edge.from()].push_back(edge);
        ++edgeCount;
    }

    std::deque<DirectedEdge> EdgeWeightedDigraph::adjacent(uint32_t vertex){
        return adjacentList[vertex];
    }

    std::deque<DirectedEdge> EdgeWeightedDigraph::edges(){
        std::deque<DirectedEdge> allEdges;
        std::deque<DirectedEdge>::iterator deqIter = allEdges.begin();
        for(auto it = std::begin(adjacentList); it != std::end(adjacentList); ++it){
            std::copy(std::begin(*it), std::end(*it), std::back_inserter(allEdges));
        }

        return allEdges;
    }


}