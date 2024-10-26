#include "embeddPartialGraph.hpp"

#include <vector>
#include <algorithm>
#include "odpGridGraphs.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers;

/// @brief indiv0にindiv1の部分グラフを埋め込む.
/// @param embeddMap インデックスが頂点の一次元表記に対応する配列.
Individual EmbeddPartialGraph::operator() (const Individual& indiv0, const Individual& indiv1, const EmbeddMap& embeddMap, std::mt19937& random) {
    Individual newIndiv;
    newIndiv.clear();

    inheritEdgesWithEmbeddMap(newIndiv, indiv0, indiv1, embeddMap);
    inheritShareEdges(newIndiv, indiv0, indiv1);
    inheritRandomEdges(newIndiv, indiv0, indiv1, random);

    return newIndiv;
}

void EmbeddPartialGraph::inheritEdgesWithEmbeddMap(Individual& newIndiv, const Individual& indiv0, const Individual& indiv1, const EmbeddMap& embeddMap) {
    for(int node = 0; node < newIndiv.numNode(); ++node) {
        const Individual* srcIndiv;
        if(embeddMap[node]) srcIndiv = &indiv0;
        else                srcIndiv = &indiv1;

        for(int d = 0; d < srcIndiv->nodeDegrees[node]; ++d) {
            int adjNode = srcIndiv->adjacent[node][d];

            if(node == adjNode) continue;
            if(newIndiv.haveEdge(node, adjNode))      continue;
            if(embeddMap[node] != embeddMap[adjNode]) continue;

            newIndiv.addEdge(node, adjNode);
        }
    }
}

void EmbeddPartialGraph::inheritShareEdges(Individual& newIndiv, const Individual& indivA, const Individual& indivB) {
    for(int nodeA0 = 0; nodeA0 < indivA.numNode(); ++nodeA0) {
        for(int d = 0; d < indivA.nodeDegrees[nodeA0]; ++d) {
            int nodeA1 = indivA.adjacent[nodeA0][d];
            if(nodeA0 == nodeA1 /*Loop egde*/)    continue;
            if(!indivB.haveEdge(nodeA0, nodeA1))  continue; //共有辺でない
            if(newIndiv.haveEdge(nodeA0, nodeA1)) continue;
            newIndiv.addEdge(nodeA0, nodeA1);
        }
    }
}

void EmbeddPartialGraph::inheritRandomEdges(Individual& newIndiv, const Individual& indiv0, const Individual& indiv1, std::mt19937& random) {
    std::vector<int> nodeSequence(newIndiv.numNode());
    for(int i = 0; i < nodeSequence.size(); ++i) nodeSequence[i] = i;
    std::shuffle(nodeSequence.begin(), nodeSequence.end(), random);

    for(int i = 0; i < nodeSequence.size(); ++i) {
        int node = nodeSequence[i];
        if(newIndiv.fullDegree(node)) continue;

        const Individual* srcIndiv;
        if(random() % 100 < 50) srcIndiv = &indiv0;
        else                    srcIndiv = &indiv1;

        for(int d = 0; d < srcIndiv->nodeDegrees[node]; ++d) {
            int adjNode = srcIndiv->adjacent[node][d];
            if(node == adjNode /*Loop egde*/)    continue;
            if(newIndiv.fullDegree(adjNode))     continue;
            if(newIndiv.haveEdge(node, adjNode)) continue;

            newIndiv.addEdge(node, adjNode);
            
            if(newIndiv.fullDegree(node)) break;
        }
    }
}
