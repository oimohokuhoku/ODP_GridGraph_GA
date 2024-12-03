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
        BlockCrossoverWithDMSXf(std::unique_ptr<GenerateEmbeddMapUnits> &generateEmbeddMapUnits, double saveParentProbability);
        ~BlockCrossoverWithDMSXf() = default;
        Individual execute(const Individual& parentA, const Individual& parentB, std::mt19937& random) override;
    private:
        const double _saveParentProbability;
        std::unique_ptr<GenerateEmbeddMapUnits>& _generateEmbeddMapUnits;
        double calcBlendRatio(const EmbeddMap &bestMap);
    };
}