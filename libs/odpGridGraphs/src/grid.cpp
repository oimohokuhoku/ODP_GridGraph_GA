#include "grid.hpp"
#include <cmath>
#include <vector>
#include "gridGraph.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using std::vector;

/// @brief 制約の情報をIndividualインスタンスから受け取って初期化
Grid::Grid(const GridGraph& indiv) :
    _numRow(indiv.numRow()),
    _numColumn(indiv.numColumn()),
    _degree(indiv.degree()),
    _maxLength(indiv.maxLength())
{}

/// @brief 制約の辺長以内の距離にある頂点をまとめて取得
vector<int> Grid::selectNearNode(int node) const {
    int numNearNode = 0;
    vector<int> nearNodes(_maxLength * _maxLength * 4); //やや大きめにとってる

    int row    = getRow(node);
    int column = getColumn(node);
    for(int dRow = -1 * _maxLength; dRow <= _maxLength; ++dRow) {
        int nearRow = row + dRow;
        if(nearRow < 0) continue;
        if(_numRow <= nearRow) break;

        int remainLength = _maxLength - abs(dRow);
        for(int dColumn = -1 * remainLength; dColumn <= remainLength; dColumn++) {
            //if(dRow == 0 && dColumn == 0) continue;

            int nearColumn = column + dColumn;
            if(nearColumn < 0) continue; 
            if(_numColumn <= nearColumn) break;

            nearNodes[numNearNode++] = toNodeIndex(nearRow, nearColumn);
        }
    }

    nearNodes.resize(numNearNode);
    return nearNodes;
}
