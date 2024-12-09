#pragma once

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    class CountDifferentEdge {
    public:
        int count(const GridGraph& graphA, const GridGraph& graphB) const;

    private:
        int countMissingEdge(const GridGraph& graphA, const GridGraph& graphB) const;
    };
}