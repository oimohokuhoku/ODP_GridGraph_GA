#pragma once
#include <random>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    /// @brief グラフのランダム化を行う関数オブジェクト(アルゴリズム"https://ipsj.ixsq.nii.ac.jp/ej/?action=repository_uri&item_id=203866&file_id=1&file_no=1")
    class Randomize {
    public:
        Randomize() = default;
        void operator()(GridGraph &graph, std::mt19937& random, bool allowDislinkedGraph = false);

    private:
        void connectNeighborNodes(GridGraph &graph);
        void shaffleEdge(GridGraph &graph, std::mt19937& random);
        void modifyToLinkedGraph(GridGraph &graph, std::mt19937& random);
    };
}