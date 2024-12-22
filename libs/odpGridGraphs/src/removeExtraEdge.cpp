#include "removeExtraEdge.hpp"

#include "gridGraph.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;

void RemoveExtraEdge::operator() (GridGraph& graph) {
    removeLoopEdge(graph);
    removeMultipleEdge(graph);
}

void RemoveExtraEdge::removeLoopEdge(GridGraph& graph) {
    for(int nodeA = 0; nodeA < graph.numNode(); ++nodeA) {
        for(int d = 0; d < graph.nodeDegree(nodeA); ++d) {
            int nodeB = graph.adjacent(nodeA, d);
            if(nodeA == nodeB) graph.removeEdge(nodeA, nodeB);
        }
    }
}

void RemoveExtraEdge::removeMultipleEdge(GridGraph& graph) {
    for(int nodeA = 0; nodeA < graph.numNode(); ++nodeA) {
        int degree = graph.nodeDegree(nodeA);

        for(int d1 = 0; d1 < degree; ++d1) {
            int nodeB1 = graph.adjacent(nodeA, d1);
            for(int d2 = d1 + 1; d2 < degree; ++d2) {
                int nodeB2 = graph.adjacent(nodeA, d2);
                if(nodeB1 == nodeB2) graph.removeEdge(nodeA, nodeB2);
            }
        }
    }
}
