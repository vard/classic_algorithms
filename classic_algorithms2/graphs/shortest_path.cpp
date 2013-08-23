#include "shortest_path.h"
#include <iomanip>
#include <iterator>
#include <limits>

namespace spt{

    DirectedEdge::DirectedEdge(uint32_t from, uint32_t to, double edgeWeigth)
        : v(from),
        w(to),
        weight(edgeWeigth){

    }

    
    DirectedEdge::DirectedEdge()
        : v(0),
        w(0),
        weight(0)
    {

    }

    uint32_t DirectedEdge::from() const{
        return v;
    }

    uint32_t DirectedEdge::to() const{
        return w;
    }

    double DirectedEdge::getWeight() const{
        return weight;
    }

    DirectedEdge& DirectedEdge::operator=(const DirectedEdge& other){
        this->v = other.v;
        this->w = other.w;
        this->weight = other.weight;
        return *this;
    }

    bool DirectedEdge::operator<( const DirectedEdge& rhs )
    {
        if(this->getWeight() < rhs.getWeight())
            return true;
        return false;
    }

    std::ostream& operator<<(std::ostream& out, const DirectedEdge& dirEdge){
        out << std::setw(2) << dirEdge.from() << " -> " << std::setw(2) <<  dirEdge.to() << " " << std::setw(8) <<  dirEdge.getWeight();
        return out;
    }

    uint32_t EdgeWeightedDigraph::getEdgeCount() const{
        return edgeCount;
    }

    uint32_t EdgeWeightedDigraph::getVertexCount() const{
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

    std::deque<DirectedEdge> EdgeWeightedDigraph::adjacent(uint32_t vertex) const{
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

    std::deque<DirectedEdge> DijkstraSPT::pathTo( uint32_t v )
    {
        std::deque<DirectedEdge> path;
        DirectedEdge edge = edgeTo[v];
        for(; edge.from()!=source; edge = edgeTo[edge.from()])
        {
            path.push_front(edge);
        }
        path.push_front(edge);
        return path;
    }

    double DijkstraSPT::distTo( uint32_t v )
    {
        return distanceTo[v];
    }

    void DijkstraSPT::relax(const DirectedEdge& edge )
    {
        uint32_t v = edge.from();
        uint32_t w = edge.to();
        if(distanceTo[w] > distanceTo[v] + edge.getWeight()){
            distanceTo[w] = distanceTo[v] + edge.getWeight();
            edgeTo[w] = edge;
            if(pq->contains(w))
                pq->decreaseKey(w, distanceTo[w]);
            else
                pq->insertElem(w, distanceTo[w]);
        }

    }

    DijkstraSPT::DijkstraSPT( const EdgeWeightedDigraph& digraph, uint32_t src )
    {
        source = src;
        uint32_t vertexCount = digraph.getVertexCount();
        edgeTo.resize(vertexCount);
        distanceTo.resize(vertexCount);
        pq = boost::shared_ptr<indexed_pq::IndexedPQ<double> >(new indexed_pq::IndexedPQ<double>(vertexCount));
        
        std::numeric_limits<double> doubleLimits;
        for (uint32_t v = 0; v < vertexCount; ++v)
        {           
            distanceTo[v]=doubleLimits.infinity();
        }
        distanceTo[source] = 0;
        
        pq->insertElem(src, 0.0);
        while(!pq->isEmpty()){
            uint32_t vertex = pq->deleteMin();
            std::deque<DirectedEdge> adj = digraph.adjacent(vertex);
            for(auto it = std::begin(adj); it != std::end(adj); ++it){
                relax(*it);
            }   

        }
    }

}