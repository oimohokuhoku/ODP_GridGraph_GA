#pragma once

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    namespace GA {
        using Individual = GridGraph;

        namespace Crossovers {
            class Crossover {
            public:
                virtual ~Crossover() = default;
                virtual Individual execute(const Individual& parentA, const Individual& parentB, std::mt19937& random)= 0;
            };
        }
    }
}
