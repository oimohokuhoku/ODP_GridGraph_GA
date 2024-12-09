#include "countDifferentEdge.hpp"
#include "gridGraph.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;

int CountDifferentEdge::count(const GridGraph& graphA, const GridGraph& graphB) const {
    int count = 0;
    count += countMissingEdge(graphA, graphB);
    count += countMissingEdge(graphB, graphA);
    return count;
}

int CountDifferentEdge::countMissingEdge(const GridGraph& source, const GridGraph& compared) const {
    int count = 0;
    for(int node0 = 0; node0 < source.numNode(); ++node0) {
        for(int d = 0; d < source.nodeDegrees[node0]; ++d) {
            int node1 = source.adjacent[node0][d];
            if(!compared.haveEdge(node0, node1)) count++;
        }
    }
    return count;
}