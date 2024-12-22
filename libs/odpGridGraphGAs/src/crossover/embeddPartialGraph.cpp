#include "embeddPartialGraph.hpp"

#include <vector>
#include <algorithm>
#include "odpGridGraphs.hpp"
#include "embeddMap.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers;

/// @brief indiv0にindiv1の部分グラフを埋め込む.
/// @param embeddMap インデックスが頂点の一次元表記に対応する配列.
GridGraph EmbeddPartialGraph::operator() (const GridGraph& indiv0, const GridGraph& indiv1, const EmbeddMap& embeddMap, std::mt19937& random) {
    FillEmptyPortRandomly fillEmptyPort;
    GridGraph newIndiv(indiv0.grid());
    newIndiv.clearEdges();

    inheritEdgesWithEmbeddMap(newIndiv, indiv0, indiv1, embeddMap);
    inheritShareEdges(newIndiv, indiv0, indiv1);
    inheritRandomEdges(newIndiv, indiv0, indiv1, random);
    fillEmptyPort(newIndiv, random);

    return newIndiv;
}

void EmbeddPartialGraph::inheritEdgesWithEmbeddMap(GridGraph& newIndiv, const GridGraph& indiv0, const GridGraph& indiv1, const EmbeddMap& embeddMap) {
    for(int node = 0; node < newIndiv.numNode(); ++node) {
        const GridGraph* srcIndiv;
        if(embeddMap.at(node)) srcIndiv = &indiv0;
        else                srcIndiv = &indiv1;

        for(int d = 0; d < srcIndiv->nodeDegree(node); ++d) {
            int adjNode = srcIndiv->adjacent(node, d);

            if(node == adjNode) continue;
            if(newIndiv.haveEdge(node, adjNode))      continue;
            if(embeddMap.at(node) != embeddMap.at(adjNode)) continue;

            newIndiv.addEdge(node, adjNode);
        }
    }
}

void EmbeddPartialGraph::inheritShareEdges(GridGraph& newIndiv, const GridGraph& indivA, const GridGraph& indivB) {
    for(int nodeA0 = 0; nodeA0 < indivA.numNode(); ++nodeA0) {
        for(int d = 0; d < indivA.nodeDegree(nodeA0); ++d) {
            int nodeA1 = indivA.adjacent(nodeA0, d);
            if(nodeA0 == nodeA1 /*Loop egde*/)    continue;
            if(!indivB.haveEdge(nodeA0, nodeA1))  continue; //共有辺でない
            if(newIndiv.haveEdge(nodeA0, nodeA1)) continue;
            newIndiv.addEdge(nodeA0, nodeA1);
        }
    }
}

void EmbeddPartialGraph::inheritRandomEdges(GridGraph& newIndiv, const GridGraph& indiv0, const GridGraph& indiv1, std::mt19937& random) {
    std::vector<int> nodeSequence(newIndiv.numNode());
    for(size_t i = 0; i < nodeSequence.size(); ++i) nodeSequence[i] = i;
    std::shuffle(nodeSequence.begin(), nodeSequence.end(), random);

    for(size_t i = 0; i < nodeSequence.size(); ++i) {
        int node = nodeSequence[i];
        if(newIndiv.fullDegree(node)) continue;

        const GridGraph* srcIndiv;
        if(random() % 100 < 50) srcIndiv = &indiv0;
        else                    srcIndiv = &indiv1;

        for(int d = 0; d < srcIndiv->nodeDegree(node); ++d) {
            int adjNode = srcIndiv->adjacent(node, d);
            if(node == adjNode /*Loop egde*/)    continue;
            if(newIndiv.fullDegree(adjNode))     continue;
            if(newIndiv.haveEdge(node, adjNode)) continue;

            newIndiv.addEdge(node, adjNode);
            
            if(newIndiv.fullDegree(node)) break;
        }
    }
}
