#pragma once
#include <vector>

namespace Cselab23Kimura::OdpGridGraphs
{
    class GridGraph;

    /// @brief 頂点の二次元表記での計算を行う.
    class Grid
    {
    public:
        const int numRow;
        const int numColumn;
        const int numNode;
        const int degree;
        const int maxLength;

        Grid(int numRow, int numColumn, int degree, int maxLength);
        bool operator==(const Grid& grid) const;
        bool operator!=(const Grid& grid) const;

        inline int toNodeIndex(int row, int column) const;
        inline int toColumnIndex(int nodeIndex) const;
        inline int toRowIndex(int nodeIndex) const;
        inline int calcDistance(int node1, int node2) const;
        inline bool closeEnough(int node1, int node2) const;
        std::vector<int> selectConnectableNodes(int node) const;
    };

    /// @brief 2次元表記(行番号・列番号)から1次元表記へ変換
    inline int Grid::toNodeIndex(int row, int column) const
    {
        return (row * numColumn) + column;
    }

    /// @brief 1次元表記から2次元表記の列番号を取得
    inline int Grid::toColumnIndex(int nodeIndex) const
    {
        return nodeIndex % numColumn;
    }

    /// @brief 1次元表記から2次元表記の行番号を取得
    inline int Grid::toRowIndex(int nodeIndex) const
    {
        return nodeIndex / numColumn;
    }

    /// @brief 頂点間のマンハッタン距離を計算
    /// @param node1 1次元表記の頂点
    /// @param node2 1次元表記の頂点
    inline int Grid::calcDistance(int node1, int node2) const
    {
        int row1 = toRowIndex(node1);
        int column1 = toColumnIndex(node1);
        int row2 = toRowIndex(node2);
        int column2 = toColumnIndex(node2);

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
        return (calcDistance(node1, node2) <= maxLength);
    }
}