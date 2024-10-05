#pragma once

namespace Cselab23Kimura::OdpGridGraphs { class GridGraph; }

namespace Cselab23Kimura::OdpGridGraphs::GA
{
    using Individual = Cselab23Kimura::OdpGridGraphs::GridGraph;

    class Crossover {
    public:
        virtual ~Crossover() = default;
        virtual Individual execute(const Individual& parentA, const Individual& parentB, std::mt19937& random)= 0;
    };
}
