#include "grid.hpp"
#include <cmath>
#include <vector>
using namespace Cselab23Kimura::OdpGridGraphs;
using std::vector;

Grid::Grid(int numRow, int numColumn, int degree, int maxLength) :
    numRow(numRow),
    numColumn(numColumn),
    numNode(numRow * numColumn),
    degree(degree),
    maxLength(maxLength)
{}

/// @brief 制約の辺長以内の距離にある頂点をまとめて取得
vector<int> Grid::selectConnectableNodes(int node) const {
    int numNearNode = 0;
    vector<int> nearNodes(maxLength * maxLength * 4); //やや大きめにとってる

    int row    = getRowIndex(node);
    int column = getColumnIndex(node);
    for(int dRow = -1 * maxLength; dRow <= maxLength; ++dRow) {
        int nearRow = row + dRow;
        if(nearRow < 0) continue;
        if(numRow <= nearRow) break;

        int remainLength = maxLength - abs(dRow);
        for(int dColumn = -1 * remainLength; dColumn <= remainLength; dColumn++) {
            //if(dRow == 0 && dColumn == 0) continue;

            int nearColumn = column + dColumn;
            if(nearColumn < 0) continue; 
            if(numColumn <= nearColumn) break;

            nearNodes[numNearNode++] = toNodeIndex(nearRow, nearColumn);
        }
    }

    nearNodes.resize(numNearNode);
    return nearNodes;
}
