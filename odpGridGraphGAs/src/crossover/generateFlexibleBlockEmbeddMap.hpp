#pragma once

#include "generateEmbeddMap.hpp"
#include <vector>
#include <random>

namespace Cselab23Kimura::OdpGridGraphs::GA
{
    class GenerateFlexibleBlockEmbeddMapUnits: GenerateEmbeddMapUnits {
    public:
        GenerateFlexibleBlockEmbeddMapUnits();
        ~GenerateFlexibleBlockEmbeddMapUnits() = default;
        std::vector<EmbeddMap> execute(int numGraphRow, int numGraphColumn, std::mt19937& random) override;

    private:
        const int _minUnitWidth;
        const int _minUnitHeight;

        EmbeddMap generateEmbeddMapUnits(int startNode, std::mt19937& random);
    };
}