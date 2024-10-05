#pragma once 

#include <vector>
#include <random>
namespace Cselab23Kimura::OdpGridGraphs { class GridGraph; }
using Individual = Cselab23Kimura::OdpGridGraphs::GridGraph;
using EmbeddMap = std::vector<bool>;

namespace Cselab23Kimura::OdpGridGraphs::GA
{
    class GenerateEmbeddMapUnits {
    public:
        ~GenerateEmbeddMapUnits() = default;
        virtual std::vector<EmbeddMap> execute(int numGraphRow, int numGraphColumn, std::mt19937& random) = 0;
    };
}