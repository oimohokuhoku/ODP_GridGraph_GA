#include "partialEvaluate.hpp"

#include <vector>
#include "gridGraph.hpp"
using std::vector;
using namespace Cselab23Kimura::OdpGridGraphs;

//後で消す
#include <iostream>

PartialFitness PartialEvaluateBFS::operator() (const GridGraph& indiv, const vector<bool>& targetNodeMap) {
    std::cerr << "PertialEvaluateBFS::operator(GridGraph, std::vector<bool>) is not implemented" << std::endl;
    exit(EXIT_FAILURE);

    //TODO: 実装

    int numTargetNode = countTargetNode(targetNodeMap);
    int totalPathLength = 0;
    int diameter = 0;
    for(int startNode = 0; startNode < indiv.numNode(); ++startNode) {
        if(targetNodeMap[startNode]) {
            int sumPathLength, diam;
            computePathLength(indiv, targetNodeMap, numTargetNode, startNode, &diam, &sumPathLength);

            totalPathLength += sumPathLength;
            if(diameter < diam) diameter = diam;
        }
    }

    PartialFitness result;
    result.diameter = diameter;
    result.aspl = (double)totalPathLength / (((numTargetNode - 1) * numTargetNode) / 2);
    return result;
}

void PartialEvaluateBFS::computePathLength(const GridGraph& indiv, const vector<bool>& targetNodeMap, int numTargetNode, int startNode, int* diameterStorage, int* pathLengthStorage) {
    /*Queue<int> queue(indiv.numNode());
    vector<bool> found(indiv.numNode(), false);
    int sumPathLength = 0;
    int numFoundTargetNode = 0;

    //すでにstartNodeとして計算されている頂点を先にnumFoundTargetNodeに含める
    for(int i = startNode - 1; i > 0; --i) 
        if(targetNodeMap[i]) numFoundTargetNode++;

    queue.enqueue(startNode);
    found[startNode] = true;
    numFoundTargetNode++;

    //最後の対象頂点のときにバグるので脱出
    if(numFoundTargetNode == numTargetNode) {
        *diameterStorage = 0;
        *pathLengthStorage = 0;
        return;
    }

    int numHop = 1;
    while(!queue.empty()) {
        int numParentNode = queue.count();
        for(int i = 0; i < numParentNode; ++i) {
            int currentNode = queue.dequeue();
            for(int d = 0; d < indiv.nodeDegrees[i]; ++d) {
                int nextNode = indiv.adjacent[currentNode][d];
                if(found[nextNode])         continue;
                if(currentNode == nextNode) continue;

                queue.enqueue(nextNode);
                found[nextNode] = true;

                if(!targetNodeMap[nextNode]) continue;
                if(nextNode <= startNode )   continue;

                numFoundTargetNode++;
                sumPathLength += numHop;

                if (numFoundTargetNode == numTargetNode) {
                    *diameterStorage   = numHop;
                    *pathLengthStorage = sumPathLength;
                    return;
                }
            }
        }
        numHop++;
    }

    *diameterStorage   = INF_DIAMETER;
    *pathLengthStorage = INF_DIAMETER;
    */
}

int PartialEvaluateBFS::countTargetNode(const vector<bool>& targetNodeMap) {
    int count = 0;
    for(bool targetNode: targetNodeMap) {
        if(targetNode) count++;
    }
    return count;
}