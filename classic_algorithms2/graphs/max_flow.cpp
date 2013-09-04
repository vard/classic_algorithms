#include <iomanip>
#include <iterator>
#include <algorithm>
#include <queue>
#include <set>
#include <tuple>
#include "max_flow.h"

using namespace std;

namespace max_flow{

    FlowEdge::FlowEdge( uint32_t from, uint32_t to, double capacity )
        :from_(from),
        to_(to),
        capacity_(capacity),
        flow_(0)
    {

    }

    FlowEdge::FlowEdge()
        :from_(0),
        to_(0),
        capacity_(0),
        flow_(0)
    {

    }

    uint32_t FlowEdge::from() const
    {
        return this->from_;
    }

    uint32_t FlowEdge::to() const
    {
        return this->to_;
    }

    uint32_t FlowEdge::other(uint32_t vertex) const
    {
        if(vertex==to_)
            return from_;
        else if(vertex==from_)
            return to_;
        else
        {
            throw std::invalid_argument("invalid argument");
        }
    }

    double FlowEdge::getCapacity() const
    {
        return this->capacity_;
    }

    double FlowEdge::getFlow() const
    {
        return this->flow_;
    }

    double FlowEdge::residualCapacityTo(uint32_t vertex) const{
        if(vertex == from_)
            return flow_;
        else if(vertex==to_)
            return capacity_ - flow_;
        else
            throw std::invalid_argument("invalid arg");
    }

    void FlowEdge::addResidualFlowTo( uint32_t vertex, double delta )
    {
        if(vertex == from_)
            flow_ -= delta;
        else if(vertex == to_)
            flow_ += delta;
        else
            throw std::invalid_argument("invalid argument");
    }

    bool FlowEdge::operator<( const FlowEdge& edge ) const{
        return std::tie(from_, to_, capacity_, flow_) < std::tie(edge.from_, edge.to_, edge.capacity_, edge.flow_);

    }

    bool FlowEdge::operator==( const FlowEdge& edge ) const{
        if(this->capacity_ == edge.capacity_ && this->from_ == edge.from_ && this->to_ == edge.to_)
            return true;
        return false;
    }

    std::ostream& operator<<(std::ostream& outputStream, const FlowEdge& edge){
        outputStream << edge.from() << " -> " << edge.to() << " " << edge.getFlow() << "/" << edge.getCapacity() << std::endl;
        return outputStream;
    }

    FlowNetwork::FlowNetwork( uint32_t vertexCount ){
        try{
            adjacentList_.resize(vertexCount);
        } catch (const std::exception& e){
            throw e.what();
        }
    }

    FlowNetwork::FlowNetwork(std::ifstream& inputStream){
        try{
            uint32_t vertexCount;
            inputStream >> std::dec >> vertexCount; 
            vertexCount_ = vertexCount;
            adjacentList_.resize(vertexCount);
            while(!inputStream.eof()){                   
                uint32_t from = 0;
                uint32_t to = 0;
                double capacity = 0.0;
                inputStream >> from >> to >> capacity;
                FlowEdge newEdge(from, to, capacity);
                adjacentList_[from].push_back(newEdge);
                adjacentList_[to].push_back(newEdge);
                ++edgesCount_;
            }
        } catch (const std::exception& e){
            throw e.what();
        }
    }

    void FlowNetwork::addEdge( const FlowEdge& edge ){
        try{
            adjacentList_[edge.from()].push_back(edge);
            adjacentList_[edge.to()].push_back(edge);
            ++edgesCount_;
        } catch (const std::exception& e){
            throw e.what();
        }
    }

    std::deque<FlowEdge>& FlowNetwork::adjacent( uint32_t vertex ) {
        if(vertex >= vertexCount_)
            throw std::invalid_argument("invalid arguments");

       // std::deque<FlowEdge&> adjacent;
       
        return (adjacentList_[vertex]);
        /*
        try{

            std::copy(adjacentList_[vertex].begin(), adjacentList_[vertex].end(), std::back_inserter(adjacent));
        } catch (const std::exception e){
            throw e.what();
        }*/

        //return adjacent;
    }

    std::set<FlowEdge> FlowNetwork::edges() const{
        //FlowEdges allEdges;
        std::set<FlowEdge> allEdges;
        try{
            for(auto it = std::begin(adjacentList_); it != std::end(adjacentList_); ++it){
                std::copy((*it).begin(), (*it).end(), std::inserter(allEdges, allEdges.end()));
                //std::copy((*it).begin(), (*it).end(), std::back_inserter(allEdges));        
            }
        } catch (const std::exception& e){
            throw e.what();
        }
        return allEdges;
    }

    uint32_t FlowNetwork::getVertexCount() const{
        return vertexCount_;
    }

    uint32_t FlowNetwork::getEdgeCount() const{
        return edgesCount_;
    }

    std::ostream& operator<<(std::ostream& out, const FlowNetwork& flowNetwork){
        std::set<FlowEdge> allEdges = flowNetwork.edges();
        for(const auto& edge : allEdges){
            out << edge;
        }
        return out;
    }

    FordFulkersonMaxFlow::FordFulkersonMaxFlow( FlowNetwork& graph, uint32_t source, uint32_t sink ){
        flowValue_ = 0.0;
        while(hasAugmentingPath(graph, source, sink)){
            numeric_limits<double> doubleLimits;
            double bottleneck = doubleLimits.infinity();
            for(uint32_t v = sink; v!=source; v = (*edgeTo_[v]).other(v)){
                bottleneck = std::min(bottleneck, (*edgeTo_[v]).residualCapacityTo(v));
            }

            for(uint32_t v = sink; v!=source; v = (*edgeTo_[v]).other(v)){
                (*edgeTo_[v]).addResidualFlowTo(v, bottleneck);
            }

            flowValue_ += bottleneck;
        }

    }

    bool FordFulkersonMaxFlow::hasAugmentingPath( FlowNetwork& graph, uint32_t s, uint32_t t ){
        uint32_t vertexCount = graph.getVertexCount();
        edgeTo_.erase(edgeTo_.begin(), edgeTo_.end());
        marked_.erase(marked_.begin(), marked_.end());
        edgeTo_.resize(vertexCount);
        marked_.resize(vertexCount, false);

        std::queue<uint32_t> vertexQ;
        vertexQ.push(s);
        while(!vertexQ.empty()){
            uint32_t v = vertexQ.front();
            vertexQ.pop();           
            std::deque<FlowEdge>& adj = graph.adjacent(v);
          //  for(auto edge : adj)
            for(std::deque<FlowEdge>::iterator edge = adj.begin(); edge !=adj.end(); ++ edge)
            {
                uint32_t w = (*edge).other(v);
                if((*edge).residualCapacityTo(w) > 0 && !marked_[w]){
                    edgeTo_[w] = &(*edge);
                    marked_[w] = true;
                    vertexQ.push(w);
                }

            }
        }
        return marked_[t];
    }

}