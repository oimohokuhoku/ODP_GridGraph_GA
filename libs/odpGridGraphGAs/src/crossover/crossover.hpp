#pragma once
#include <random>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    namespace GA {
        using GridGraph = GridGraph;

        namespace Crossovers {
            class Crossover {
            public:
                virtual ~Crossover() = default;
                virtual GridGraph execute(const GridGraph& parentA, const GridGraph& parentB, std::mt19937& random)= 0;
            };
        }
    }
}
