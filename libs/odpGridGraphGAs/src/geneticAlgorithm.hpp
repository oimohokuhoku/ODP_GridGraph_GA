#pragma once

#include <fstream>
#include <string>
#include <memory>
#include <random>
namespace Cselab23Kimura::OdpGridGraphs { class GridGraph; }

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    namespace GA {
        class Group;
        namespace CopySelects { class CopySelect; }
        namespace Crossovers  { class Crossover; }
        namespace Mutates     { class Mutate; }
        namespace SurvivorSelects { class SurvivorSelect; }

        class GeneticAlgorithm {
        public:
            GeneticAlgorithm(const Group& initialGroup);

            Group progressGeneration(
                const Group& group,
                CopySelects::CopySelect *const copySelect,
                Crossovers::Crossover *const crossover,
                Mutates::Mutate *const mutate,
                SurvivorSelects::SurvivorSelect *const survivorSelect,
                std::mt19937& random
            );
            inline int generation() const { return _generation; }

        private:
            int _generation;
            GridGraph* _bestEverGraph;

        private:
            GeneticAlgorithm() = delete;
        };
    }
}