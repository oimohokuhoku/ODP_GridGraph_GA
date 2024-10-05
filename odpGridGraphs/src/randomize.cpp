#include "randomize.hpp"


#include "gridGraph.hpp"
#include "grid.hpp"
#include "twoChange.hpp"
#include "checkLinkedGraph.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;

/// @brief グラフのランダム化(アルゴリズム"https://ipsj.ixsq.nii.ac.jp/ej/?action=repository_uri&item_id=203866&file_id=1&file_no=1")
void Randomize::operator() (GridGraph& indiv, std::mt19937& random, bool allowDislinkedGraph) {
    indiv.clear();
    connectNeighborNodes(indiv);
    shaffleEdge(indiv, random);

    if(!allowDislinkedGraph) modifyToLinkedGraph(indiv, random);
}

void Randomize::connectNeighborNodes(GridGraph& indiv) {
    Grid grid(indiv);

    //水平方向に隣接する頂点を接続
    for(int y = 0; y < indiv.numRow(); ++y) {
        for(int x = 0; x + 1 < indiv.numColumn(); x += 2) {
            int node1 = grid.toNodeIndex(y, x);
            int node2 = grid.toNodeIndex(y, x + 1);
            for(int d = 0; d < indiv.degree(); ++d)
                indiv.addEdge(node1, node2);
        }
    }
    if(indiv.numColumn() % 2 == 0) return;

    //右端列において、鉛直方向に隣接する頂点を接続
    int rightEnd = indiv.numColumn() - 1;
    for(int y = 0; y + 1 < indiv.numRow(); y += 2) {
        int node1 = grid.toNodeIndex(y    , rightEnd);
        int node2 = grid.toNodeIndex(y + 1, rightEnd);
        for(int d = 0; d < indiv.degree(); ++d)
            indiv.addEdge(node1, node2);
    }
    if(indiv.numRow() % 2 == 0) return;

    //右下頂点にループ辺を追加
    int bottomEnd = indiv.numColumn() - 1;
    int cornerNode = grid.toNodeIndex(bottomEnd, rightEnd);
    for(int d = 0; d + 1 < indiv.degree(); d += 2) {
        indiv.addEdge(cornerNode, cornerNode);
    }
}

void Randomize::shaffleEdge(GridGraph& indiv, std::mt19937& random) {
    TwoChange twoChange;
    int numChange = indiv.numNode() * indiv.numNode() * indiv.degree() * indiv.degree(); //大きすぎず、小さすぎずの値. 計算式に特に意味はない

    for(int i = 0; i < numChange; ++i) {
        twoChange(indiv, random);
    }
}

void Randomize::modifyToLinkedGraph(GridGraph& indiv, std::mt19937& random) {
    CheckLinkedGraph checkLinked;
    TwoChange twoChange;

    while(!checkLinked.checkLinked(indiv)) {
        int dislinkedNode = checkLinked.dislinkedNode();
        twoChange(indiv, dislinkedNode, random);
    }
}
