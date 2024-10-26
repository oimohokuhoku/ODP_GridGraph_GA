#pragma once
#include <random>

namespace Cselab23Kimura::OdpGridGraphs
{
    class GridGraph;

    /// @brief 2-changeの関数オブジェクト
    class TwoChange {
    public:
        void operator()(GridGraph &graph, std::mt19937& random);
        void operator()(GridGraph &graph, int node, std::mt19937& random);
        void operator()(GridGraph &graph, int node1, int node2, std::mt19937& random);
        void operator()(GridGraph &graph, int nodeA1, int nodeA2, int nodeB1, int nodeB2);
        void tryTwoChange(GridGraph &graph, int nodeA1, int nodeA2, int nodeB1, int nodeB2);

    private:
        long _numChangedEdges = 0;
        long _numDuplicateEdges = 0;
    };
}