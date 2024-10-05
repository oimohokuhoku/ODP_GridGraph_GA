#pragma once

#include<vector>
namespace Collections { template <class T> class Array; }

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    class LocalSearch
    {
    public:
        LocalSearch();
        void localOptimize(GridGraph &indiv);
        bool exhaustiveTwoChange(GridGraph &indiv);
        void partialGraphOptimize(GridGraph &indiv, const std::vector<bool> &targetNodes);
        bool partialExhaustiveTwoChange(GridGraph &indiv, const std::vector<bool> &targetNodes);
        inline int numEvaluate() { return _numEvaluate; }

    private:
        int _numEvaluate;
    };
}