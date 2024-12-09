#pragma once

#include<random>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;
    class Grid;

    class EdgeSwap {
    public:
        EdgeSwap(int numSwappedEdge);
        void swap(GridGraph& graph, std::mt19937& rand);
        void swap(GridGraph& graph, int startNodeIndex, std::mt19937& rand);

    private:
        const int _numSwappedEdge;
        std::vector<int> selectSwappedEdgeTour(const GridGraph& graph, int startNode, std::mt19937& rand);
        bool selectSwappedEdgeTourBFS(const GridGraph& graph, const Grid& grid, std::vector<int>& stack, int stackSize, std::vector<bool>& passed, std::mt19937& rand);
        void swapEdges(GridGraph& graph, const std::vector<int>& swappedEdgeTour);
    };
}