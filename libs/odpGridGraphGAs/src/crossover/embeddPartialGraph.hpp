#pragma once
#include <vector>
#include <random>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    namespace GA::Crossovers {
        class EmbeddMap;

        class EmbeddPartialGraph {
        public:
            GridGraph operator()(const GridGraph &indiv0, const GridGraph &indiv1, const EmbeddMap &embeddMap, std::mt19937& random);

        private:
            void inheritEdgesWithEmbeddMap(GridGraph &newIndiv, const GridGraph &indiv0, const GridGraph &indiv1, const EmbeddMap &embeddMap);
            void inheritShareEdges(GridGraph &newIndiv, const GridGraph &indiv0, const GridGraph &indiv1);
            void inheritRandomEdges(GridGraph &newIndiv, const GridGraph &indiv0, const GridGraph &indiv1, std::mt19937& random);
        };
    }
}
