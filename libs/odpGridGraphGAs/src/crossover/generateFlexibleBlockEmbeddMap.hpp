#pragma once

#include "generateEmbeddMap.hpp"
#include <vector>
#include <random>

namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers
{
    class GenerateFlexibleBlockEmbeddMapUnits: GenerateEmbeddMapUnits {
    public:
        GenerateFlexibleBlockEmbeddMapUnits(int maxUnitWidth, int minUnitWidth, int maxUnitHeight, int minUnitHeight);
        ~GenerateFlexibleBlockEmbeddMapUnits() = default;
        std::vector<EmbeddMap> execute(int numGraphRow, int numGraphColumn, std::mt19937& random) override;

    private:
        const int _maxUnitWidth;
        const int _minUnitWidth;
        const int _maxUnitHeight;
        const int _minUnitHeight;

        EmbeddMap generateEmbeddMapUnits(int startNode, std::mt19937& random);
    };
}