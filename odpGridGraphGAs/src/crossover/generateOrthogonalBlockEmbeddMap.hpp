#pragma once

#include "generateEmbeddMap.hpp"
#include <vector>
#include <random>

namespace Cselab23Kimura::OdpGridGraphs::GA
{
    class GenerateOrthogonalBlockEmbeddMapUnits: public GenerateEmbeddMapUnits {
    public:
        ~GenerateOrthogonalBlockEmbeddMapUnits() = default;
        std::vector<EmbeddMap> execute(int numGraphRow, int numGraphColumn, std::mt19937& random) override;

    private:
        std::vector<int> decideDevidePositions(int width, std::mt19937& random);
    };
}