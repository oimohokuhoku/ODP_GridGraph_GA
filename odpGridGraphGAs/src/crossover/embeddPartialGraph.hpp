#pragma once

#include <vector>
namespace Cselab23Kimura::OdpGridGraphs { class GridGraph; }
using Individual = Cselab23Kimura::OdpGridGraphs::GridGraph;
using EmbeddMap = std::vector<bool>;

namespace Cselab23Kimura::OdpGridGraphs::GA
{
    class EmbeddPartialGraph {
    public:
        Individual operator()(const Individual &indiv0, const Individual &indiv1, const EmbeddMap &embeddMap);

    private:
        void inheritEdgesWithEmbeddMap(Individual &newIndiv, const Individual &indiv0, const Individual &indiv1, const EmbeddMap &embeddMap);
        void inheritShareEdges(Individual &newIndiv, const Individual &indiv0, const Individual &indiv1);
        void inheritRandomEdges(Individual &newIndiv, const Individual &indiv0, const Individual &indiv1);
    };
}
