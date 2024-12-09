#pragma once
#include <vector>

namespace Cselab23Kimura::OdpGridGraphs
{
    class GridGraph;

    /// @brief 頂点の二次元表記での計算を行う.
    class Grid
    {
    public:
        Grid(const GridGraph &indiv);
        inline int toNodeIndex(int row, int column) const;
        inline int getColumn(int nodeIndex) const;
        inline int getRow(int nodeIndex) const;
        inline int calcDistance(int node1, int node2) const;
        inline bool closeEnough(int node1, int node2) const;
        std::vector<int> selectNearNode(int node) const;

    private:
        const int _numRow;
        const int _numColumn;
        const int _degree;
        const int _maxLength;
    };

    /// @brief 2次元表記(行番号・列番号)から1次元表記へ変換
    inline int Grid::toNodeIndex(int row, int column) const
    {
        return (row * _numColumn) + column;
    }

    /// @brief 1次元表記から2次元表記の列番号を取得
    inline int Grid::getColumn(int nodeIndex) const
    {
        return nodeIndex % _numColumn;
    }

    /// @brief 1次元表記から2次元表記の行番号を取得
    inline int Grid::getRow(int nodeIndex) const
    {
        return nodeIndex / _numColumn;
    }

    /// @brief 頂点間のマンハッタン距離を計算
    /// @param node1 1次元表記の頂点
    /// @param node2 1次元表記の頂点
    inline int Grid::calcDistance(int node1, int node2) const
    {
        int row1 = getRow(node1);
        int column1 = getColumn(node1);
        int row2 = getRow(node2);
        int column2 = getColumn(node2);

        int dRow = row1 - row2;
        int dColumn = column1 - column2;
        if (dRow < 0)
            dRow *= -1;
        if (dColumn < 0)
            dColumn *= -1;

        return dRow + dColumn;
    }

    /// @brief 2頂点間の距離が制約内かを判定
    /// @param node1 1次元表記の頂点番号
    /// @param node2 1次元表記の頂点番号
    inline bool Grid::closeEnough(int node1, int node2) const
    {
        return (calcDistance(node1, node2) <= _maxLength);
    }
}