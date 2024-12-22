#include "checkLinkedGraph.hpp"
#include <iostream>
#include <vector>
#include "gridGraph.hpp"
#include "queue.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using std::vector;

/// @brief Checks if all nodes in the graph are connected to node[0].
/// @param graph The GridGraph object to be checked.
/// @return Returns true if the graph is fully connected, otherwise returns false.
/// @details complexity is O(V + E) where V is the number of nodes and E is the number of edges.
bool CheckLinkedGraph::checkLinked(const GridGraph& graph) {
    // BFS
    Collections::Queue<int> queue(graph.numNode());

    vector<bool> visited(graph.numNode(), false);
    int visitedCount = 0;

    queue.enqueue(0);
    visited[0] = true;
    visitedCount++;

    while(!queue.empty()) {
        int currentNode = queue.dequeue();
        for(int d = 0; d < graph.nodeDegree(currentNode); ++d) {
            int nextNode = graph.adjacent(currentNode, d);
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

    throw std::logic_error("Unexpected Error");
}