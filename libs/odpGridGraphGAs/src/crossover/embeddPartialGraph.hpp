#pragma once
#include <vector>
#include <random>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;
    using Individual = GridGraph;

    namespace GA::Crossovers {
        using EmbeddMap = std::vector<bool>;

        class EmbeddPartialGraph {
        public:
            Individual operator()(const Individual &indiv0, const Individual &indiv1, const EmbeddMap &embeddMap, std::mt19937& random);

        private:
            void inheritEdgesWithEmbeddMap(Individual &newIndiv, const Individual &indiv0, const Individual &indiv1, const EmbeddMap &embeddMap);
            void inheritShareEdges(Individual &newIndiv, const Individual &indiv0, const Individual &indiv1);
            void inheritRandomEdges(Individual &newIndiv, const Individual &indiv0, const Individual &indiv1, std::mt19937& random);
        };
    }
}
