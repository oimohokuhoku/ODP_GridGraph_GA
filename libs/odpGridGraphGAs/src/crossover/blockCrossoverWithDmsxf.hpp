#pragma once

#include <random>
#include <vector>
#include <memory>
#include "crossover.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers
{
    class GenerateEmbeddMapUnits;
    class EmbeddMap;

    class BlockCrossoverWithDMSXf: public Crossover {
    public:
        BlockCrossoverWithDMSXf(GenerateEmbeddMapUnits *const generateEmbeddMapUnits, double saveParentProbability);
        ~BlockCrossoverWithDMSXf() = default;
        GridGraph execute(const GridGraph& parentA, const GridGraph& parentB, std::mt19937& random) override;
    private:
        const double _saveParentProbability;
        GenerateEmbeddMapUnits *const _generateEmbeddMapUnits;
        double calcBlendRatio(const EmbeddMap &bestMap);
    };
}