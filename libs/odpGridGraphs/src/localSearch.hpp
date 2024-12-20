#pragma once

#include<vector>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    class LocalSearch
    {
    public:
        LocalSearch();
        void localOptimize(GridGraph &graph);
        void partialGraphOptimize(GridGraph &graph, const std::vector<bool> &targetNodes);
        inline int numEvaluate() { return _numEvaluate; }

    private:
        int _numEvaluate;
        bool exhaustiveTwoChange(GridGraph &graph);
        bool partialExhaustiveTwoChange(GridGraph &graph, const std::vector<bool> &targetNodes);
    };
}