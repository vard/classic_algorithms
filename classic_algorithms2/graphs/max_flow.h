#pragma once

#include "boost/cstdint.hpp"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <deque>

using namespace boost;
using namespace std;

namespace max_flow{

    class FlowEdge{
    private:
        uint32_t from_;
        uint32_t to_;
        double capacity_;
        double flow_;
    public:
        FlowEdge();
        FlowEdge(uint32_t from, uint32_t to, double capacity);
        uint32_t from() const;
        uint32_t to() const;
        uint32_t other(uint32_t vertex) const throw(std::invalid_argument);
        double getCapacity() const;
        double getFlow() const;
        double residualCapacityTo(uint32_t vertex) const throw(std::invalid_argument);
        void addResidualFlowTo(uint32_t vertex, double delta) throw(std::invalid_argument);

        bool operator<(const FlowEdge& edge) const;
        bool operator==(const FlowEdge& edge) const;

        friend std::ostream& operator<<(std::ostream& outputStream, const FlowEdge& edge);
    };

    typedef std::deque<FlowEdge> FlowEdges;

    class FlowNetwork{
    private:        
        uint32_t vertexCount_;
        uint32_t edgesCount_;
        std::deque<FlowEdges> adjacentList_;
    public:
        FlowNetwork(uint32_t vertexCount) throw(std::exception);
        FlowNetwork(std::ifstream& inputStream) throw(std::exception);
        void addEdge(const FlowEdge& edge);
        std::deque<FlowEdge>& adjacent(uint32_t vertex);
        std::set<FlowEdge> edges() const;
        uint32_t getVertexCount() const;
        uint32_t getEdgeCount() const;

        

        friend std::ostream& operator<<(std::ostream& out, const FlowNetwork& flowNetwork);
    };

    class FordFulkersonMaxFlow{
    private:
        uint32_t source_;
        uint32_t sink_; 
        std::deque<bool> marked_;
        std::deque<FlowEdge*> edgeTo_;
        double flowValue_;
        bool hasAugmentingPath(FlowNetwork& graph, uint32_t s, uint32_t t);

    public:
        FordFulkersonMaxFlow(FlowNetwork& graph, uint32_t source, uint32_t sink);
        double getFlowValue() const;
        bool inCut(uint32_t vertex) const;
    };
}