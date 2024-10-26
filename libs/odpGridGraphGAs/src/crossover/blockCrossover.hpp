#pragma once

#include <vector>
#include <memory>
#include "generateEmbeddMap.hpp"
#include "crossover.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers
{
    class BlockCrossover: public Crossover {
    public:
        BlockCrossover(std::unique_ptr<GenerateEmbeddMapUnits> &generateEmbeddMapUnits);
        ~BlockCrossover() = default;
        Individual execute(const Individual& parentA, const Individual& parentB, std::mt19937& random) override;
    private:
        std::unique_ptr<GenerateEmbeddMapUnits>& _generateEmbeddMapUnits;
        void overlayEmbeddMaps(EmbeddMap &baseMap, const EmbeddMap &overlayMap);
    };
}