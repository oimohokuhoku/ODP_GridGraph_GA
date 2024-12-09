#pragma once
#include <random>
namespace Cselab23Kimura::OdpGridGraphs { class GridGraph; }

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;
    
    namespace GA {
        using GridGraph = Cselab23Kimura::OdpGridGraphs::GridGraph;

        namespace Mutates {
            class Mutate {
            public:
                virtual ~Mutate() = default;
                virtual void execute(GridGraph& indiv, std::mt19937& random) = 0;
            };
        }
    }
}