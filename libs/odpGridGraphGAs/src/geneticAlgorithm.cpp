#include "geneticAlgorithm.hpp"
#include <memory>
#include <random>
#include "odpGridGraphs.hpp"
#include "initialize/initialize.hpp"
#include "copySelect/copySelect.hpp"
#include "crossover/crossover.hpp"
#include "mutate/mutate.hpp"
#include "survivorSelect/survivorSelect.hpp"
#include "group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::string;
using std::unique_ptr;
using std::mt19937;

GeneticAlgorithm::GeneticAlgorithm(const Group& initialGroup) {
    _generation = 0;
    _bestEverGraph = new GridGraph(initialGroup.bestIndiv());
}

/// @brief 世代を進める.
Group GeneticAlgorithm::progressGeneration(
    const Group& group,
    CopySelects::CopySelect *const copySelect,
    Crossovers::Crossover *const crossover,
    Mutates::Mutate *const mutate,
    SurvivorSelects::SurvivorSelect *const survivorSelect,
    std::mt19937& random
) {
    Group nextGroup(group.population());

    int numParent = 2;
    int numCrossover = 1;

    int numNextIndivs = 0;
    copySelect->decideSequence(group);
    while(numNextIndivs < nextGroup.population()) {
        Group parents(numParent);
        for(int i = 0; i < numParent; ++i) {
            parents[i] = group[copySelect->selectIndex()];
        }

		Group childs(numCrossover);
        for(int i = 0; i < childs.population(); ++i) {
            childs[i] = crossover->execute(*parents[0], *parents[1], random);
            mutate->execute(*childs[i], random);
        }
		
		Group survivor = survivorSelect->moveSurvivors(childs, parents, random);
        for(int i = 0; i < survivor.population(); ++i) {
            nextGroup[numNextIndivs++] = std::move(survivor[i]);
            if(numNextIndivs == nextGroup.population()) break;
        }
	}
    this->_generation++;

    LocalSearch localSearch;
    for(int i = 0; i < nextGroup.population(); ++i) {
        localSearch.localOptimize(*nextGroup[i]);
    }

    if(!_bestEverGraph->betterThan(nextGroup.bestIndiv())) {
        *_bestEverGraph = nextGroup.bestIndiv();
    }

    return nextGroup;
}
