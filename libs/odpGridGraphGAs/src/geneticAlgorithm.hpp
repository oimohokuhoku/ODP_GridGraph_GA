#pragma once

#include <fstream>
#include <string>
#include <memory>
#include <random>
namespace Cselab23Kimura::OdpGridGraphs { class GridGraph; }

namespace Cselab23Kimura::OdpGridGraphs::GA
{
    class GAConfiguration;
    class Group;
    class Initialize;
    namespace CopySelects { class CopySelect; }
    namespace Crossovers  { class Crossover; }
    namespace Mutates     { class Mutate; }
    namespace SurvivorSelects { class SurvivorSelect; }

    // GAの操作を行う. なるべくこのインスタンスのみの呼び出しのみで処理が完結するように設計
    class GeneticAlgorithm
    {
    public:
        GeneticAlgorithm(
            const GAConfiguration &config, 
            std::unique_ptr<Initialize>& initialize,
            std::mt19937& random
        );
        ~GeneticAlgorithm();

        void progressGeneration(
            std::unique_ptr<CopySelects::CopySelect> &copySelect,
            std::unique_ptr<Crossovers::Crossover>& crossover,
            std::unique_ptr<Mutates::Mutate>& mutate,
            std::unique_ptr<SurvivorSelects::SurvivorSelect> &survivorSelect,
            std::mt19937& random
        );
        bool end() const;

        void showParameterTableHedder() const;
        void saveBestEverEdgeFile(const std::string &dirpath) const;

        inline int generation() const { return _generation; }
        int bestDiameter() const;
        double bestASPL() const;
        double averageASPL() const;
        double worstASPL() const;
        int indivVariation() const;
        inline int averageDistanceFromStartGraph() const { return _averageDistanceFromStartGraph; }

    private:
        const int _MAX_GENERATION;
        int _generation;
        int _numRow;
        int _numColumn;
        int _averageDistanceFromStartGraph;
        const double _indivMutateProbability;
        const double _geneMutateProbability;
        Group *_group;
        Cselab23Kimura::OdpGridGraphs::GridGraph *_bestEverGraph;

    private:
        GeneticAlgorithm() = delete;
    };
}