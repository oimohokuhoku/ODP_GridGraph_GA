#include "twoChange.hpp"

#include <iostream>
#include <cmath>
#include <algorithm>
#include "gridGraph.hpp"
#include "grid.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;

/// @brief ランダムに2-changeを適用 
void TwoChange::operator() (GridGraph& graph, std::mt19937& random) {
    int node = random() % graph.numNode();
    (*this)(graph, node, random);
}

/// @brief 指定した頂点を含む2-changeの適用
void TwoChange::operator() (GridGraph& graph, int node, std::mt19937& random) {
    int d = random() % graph.nodeDegrees[node];
    int node2 = graph.adjacent[node][d];
    
    (*this)(graph, node, node2, random);
}

/// @brief 辺[node1-node2]を含む2-changeの適用
void TwoChange::operator() (GridGraph& graph, int nodeA1, int nodeA2, std::mt19937& random) {
    Grid grid = graph.grid();
    std::vector<int> nearNodesA1 = grid.selectConnectableNodes(nodeA1);
    std::shuffle(nearNodesA1.begin(), nearNodesA1.end(), random);

    for(int i = 0; i < nearNodesA1.size(); ++i) {
        int nodeB1 = nearNodesA1[i];

        int startDegree = random() % graph.nodeDegrees[nodeB1];
        for(int d = 0; d < graph.nodeDegrees[nodeB1]; ++d) {
            int degreeB2 = (startDegree + d) % graph.nodeDegrees[nodeB1];
            int nodeB2 = graph.adjacent[nodeB1][degreeB2];

            //同じ辺が選ばれたらスキップ
            if(nodeA1 == nodeB1 && nodeA2 == nodeB2) continue;
            if(nodeA1 == nodeB2 && nodeA2 == nodeB1) continue;

            if(grid.closeEnough(nodeA2, nodeB2)) {
                (*this)(graph, nodeA1, nodeA2, nodeB1, nodeB2);
                return;
            }
        }
    }
}

/// @brief 2辺を指定して2-changeを適用. (nodeA1-nodeA2, nodeB1-nodeB2) → (nodeA1-nodeB1, nodeA2-nodeB2).
void TwoChange::operator() (GridGraph& graph, int nodeA1, int nodeA2, int nodeB1, int nodeB2) {
    this->_numChangedEdges += 2;
    if(graph.haveEdge(nodeA1, nodeB1)) this->_numDuplicateEdges++;
    if(graph.haveEdge(nodeA2, nodeB2)) this->_numDuplicateEdges++;
    graph.removeEdge(nodeA1, nodeA2);
    graph.removeEdge(nodeB1, nodeB2);
    graph.addEdge(nodeA1, nodeB1);
    graph.addEdge(nodeA2, nodeB2);
}

/// @brief [For Debug] 2-changeが適用できない辺が選択されたときに警告して終了.
void TwoChange::tryTwoChange(GridGraph& graph, int nodeA1, int nodeA2, int nodeB1, int nodeB2) {
    Grid grid = graph.grid();
    if(nodeA1 == nodeB1 && nodeA2 == nodeB2) {
        std::cerr << "TwoChange: Edge is duplicated(" << nodeA1 << "-" << nodeA2 << ", " << nodeB1 << "-" << nodeB2 << ")" << std::endl;
        graph.showGraph();
        exit(-1);
    }
    if(nodeA1 == nodeB2 && nodeA2 == nodeB1) {
        std::cerr << "TwoChange: Edge is duplicated(" << nodeA1 << "-" << nodeA2 << ", " << nodeB1 << "-" << nodeB2  << std::endl;
        graph.showGraph();
        exit(-1);
    }
    if(!graph.haveEdge(nodeA1, nodeA2)) { 
        std::cerr << "TwoChange: Edge(" << nodeA1 << "-" << nodeA2 << ") doesn't exist" << std::endl;
        graph.showGraph();
        exit(-1);
    }
    if(!graph.haveEdge(nodeB1, nodeB2)) { 
        std::cerr << "TwoChange: Edge(" << nodeB1 << "-" << nodeB2 << ") doesn't exist" << std::endl;
        graph.showGraph();
        exit(-1);
    }
    if(!grid.closeEnough(nodeA1, nodeB1)) {
        std::cerr << "TwoChange: Length of edge(" << nodeA1 << "-" << nodeB1 << ") beyonds the limit" << std::endl;
        exit(-1);
    }
    if(!grid.closeEnough(nodeA2, nodeB2)) {
        std::cerr << "TwoChange: Length of edge(" << nodeA2 << "-" << nodeA2 << ") beyonds the limit" << std::endl;
        exit(-1);
    }

    graph.removeEdge(nodeA1, nodeA2);
    graph.removeEdge(nodeB1, nodeB2);
    graph.addEdge(nodeA1, nodeB1);
    graph.addEdge(nodeA2, nodeB2);
}
