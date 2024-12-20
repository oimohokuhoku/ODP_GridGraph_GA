#include "checkLinkedGraph.hpp"

#include <iostream>
#include <vector>
#include "gridGraph.hpp"
#include "queue.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using std::vector;

/// @brief ノード[0]とつながっていない頂点を探索
/// @return 連結グラフであれば-1を返す
bool CheckLinkedGraph::checkLinked(const GridGraph& graph) {
    // BFSで探索
    Collections::Queue<int> queue(graph.numNode());

    vector<bool> visited(graph.numNode(), false);
    int visitedCount = 0;

    queue.enqueue(0);
    visited[0] = true;
    visitedCount++;

    while(!queue.empty()) {
        int currentNode = queue.dequeue();
        for(int d = 0; d < graph.nodeDegrees[currentNode]; ++d) {
            int nextNode = graph.adjacent[currentNode][d];
            if(visited[nextNode]) continue;

            queue.enqueue(nextNode);
            visited[nextNode] = true;
            visitedCount++;

            if(visitedCount == graph.numNode()) {
                this->_disLinkedNode = -1;
                return true;
            }
        }
    }

    for(int i = 0; i < graph.numNode(); ++i) {
        if(!visited[i]) {
            this->_disLinkedNode = i;
            return false;
        }
    }

    std::cerr << "CkechLinkedGraph::findDislinkedNode(GridGraph): Failure in inplementation." << std::endl;
    exit(EXIT_FAILURE);
}