#pragma once
#include <vector>
#include <memory>
#include "generateEmbeddMap.hpp"
#include "crossover.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers
{
    class EmbeddMap;

    class BlockCrossover: public Crossover {
    public:
        BlockCrossover(GenerateEmbeddMapUnits *const generateEmbeddMapUnits);
        ~BlockCrossover() = default;
        GridGraph execute(const GridGraph& parentA, const GridGraph& parentB, std::mt19937& random) override;
    private:
        GenerateEmbeddMapUnits *const _generateEmbeddMapUnits;
    };
}