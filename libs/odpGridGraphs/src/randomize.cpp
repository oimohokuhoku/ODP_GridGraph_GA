#include "randomize.hpp"
#include "gridGraph.hpp"
#include "grid.hpp"
#include "twoChange.hpp"
#include "checkLinkedGraph.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;

/// @brief グラフのランダム化(アルゴリズム"https://ipsj.ixsq.nii.ac.jp/ej/?action=repository_uri&item_id=203866&file_id=1&file_no=1")
void Randomize::operator() (GridGraph& graph, std::mt19937& random, bool allowDislinkedGraph) {
    graph.clearEdges();
    connectNeighborNodes(graph);
    shaffleEdge(graph, random);

    if(!allowDislinkedGraph) modifyToLinkedGraph(graph, random);
}

void Randomize::connectNeighborNodes(GridGraph& graph) {
    Grid grid = graph.grid();

    //水平方向に隣接する頂点を接続
    for(int y = 0; y < graph.numRow(); ++y) {
        for(int x = 0; x + 1 < graph.numColumn(); x += 2) {
            int node1 = grid.toNodeIndex(y, x);
            int node2 = grid.toNodeIndex(y, x + 1);
            for(int d = 0; d < graph.degree(); ++d)
                graph.addEdge(node1, node2);
        }
    }
    if(graph.numColumn() % 2 == 0) return;

    //右端列において、鉛直方向に隣接する頂点を接続
    int rightEnd = graph.numColumn() - 1;
    for(int y = 0; y + 1 < graph.numRow(); y += 2) {
        int node1 = grid.toNodeIndex(y    , rightEnd);
        int node2 = grid.toNodeIndex(y + 1, rightEnd);
        for(int d = 0; d < graph.degree(); ++d)
            graph.addEdge(node1, node2);
    }
    if(graph.numRow() % 2 == 0) return;

    //右下頂点にループ辺を追加
    int bottomEnd = graph.numColumn() - 1;
    int cornerNode = grid.toNodeIndex(bottomEnd, rightEnd);
    for(int d = 0; d + 1 < graph.degree(); d += 2) {
        graph.addEdgeAllowingLoops(cornerNode, cornerNode);
    }
}

void Randomize::shaffleEdge(GridGraph& graph, std::mt19937& random) {
    TwoChange twoChange;
    int numChange = graph.numNode() * graph.numNode() * graph.degree() * graph.degree(); //大きすぎず、小さすぎずの値. 計算式に特に意味はない

    for(int i = 0; i < numChange; ++i) {
        twoChange(graph, random);
    }
}

void Randomize::modifyToLinkedGraph(GridGraph& graph, std::mt19937& random) {
    CheckLinkedGraph checkLinked;
    TwoChange twoChange;

    while(!checkLinked.checkLinked(graph)) {
        int dislinkedNode = checkLinked.dislinkedNode();
        twoChange(graph, dislinkedNode, random);
    }
}
