#pragma once
#include <random>

namespace Cselab23Kimura::OdpGridGraphs
{
    class GridGraph;

    class FillEmptyPortRandomly {
    public:
        FillEmptyPortRandomly() = default;
        void operator()(GridGraph &graph, std::mt19937& random);

    private:
        FillEmptyPortRandomly(FillEmptyPortRandomly &obj) = delete;
        FillEmptyPortRandomly(FillEmptyPortRandomly &&obj) = delete;
        FillEmptyPortRandomly operator=(FillEmptyPortRandomly &obj) = delete;
        FillEmptyPortRandomly operator=(FillEmptyPortRandomly &&obj) = delete;
    };
}