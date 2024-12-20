#include "fillEmptyPortRandomly.hpp"
#include <vector>
#include <algorithm>
#include "gridGraph.hpp"
#include "grid.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using std::vector;

/// @brief 空きポートをランダムに埋める
void FillEmptyPortRandomly::operator() (GridGraph& graph, std::mt19937& random) {
    Grid grid = graph.grid();
    int* nearNodes;

    vector<int> nodeSequence(graph.numNode());
    for(int i = 0; i < nodeSequence.size(); ++i) nodeSequence[i] = i;
    std::shuffle(nodeSequence.begin(), nodeSequence.end(), random);

    for(int i = 0; i < nodeSequence.size(); ++i) {
        int nodeA = nodeSequence[i];
        if(graph.fullDegree(nodeA)) continue;
        
        vector<int> nearNodes = grid.selectConnectableNodes(nodeA);
        std::shuffle(nearNodes.begin(), nearNodes.end(), random);
        for(int j = 0; j < nearNodes.size(); ++j) {
            int nodeB = nearNodes[j];
            if(nodeA == nodeB)                  continue;
            if(graph.fullDegree(nodeB))         continue;
            if(!grid.closeEnough(nodeA, nodeB)) continue;
            if(graph.haveEdge(nodeA, nodeB))    continue;

            graph.addEdge(nodeA, nodeB);
            if(graph.fullDegree(nodeA)) break;
        }
    }
}