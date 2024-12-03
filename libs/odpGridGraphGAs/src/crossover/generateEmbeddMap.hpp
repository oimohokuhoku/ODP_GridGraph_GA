#pragma once 
#include <vector>
#include <random>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    namespace GA::Crossovers {
        class EmbeddMap;

        class GenerateEmbeddMapUnits {
        public:
            ~GenerateEmbeddMapUnits() = default;
            virtual std::vector<EmbeddMap> execute(int numGraphRow, int numGraphColumn, std::mt19937& random) = 0;
        };
    }
}