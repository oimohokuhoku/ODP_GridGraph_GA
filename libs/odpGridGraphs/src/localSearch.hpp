#pragma once

#include<vector>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    class LocalSearch
    {
    public:
        LocalSearch();
        void localOptimize(GridGraph &indiv);
        void partialGraphOptimize(GridGraph &indiv, const std::vector<bool> &targetNodes);
        inline int numEvaluate() { return _numEvaluate; }

    private:
        int _numEvaluate;
        bool exhaustiveTwoChange(GridGraph &indiv);
        bool partialExhaustiveTwoChange(GridGraph &indiv, const std::vector<bool> &targetNodes);
    };
}