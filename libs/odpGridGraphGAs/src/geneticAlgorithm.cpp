#include "geneticAlgorithm.hpp"
#include <iostream>
#include <memory>
#include <random>
#include "odpGridGraphs.hpp"
#include "initialize/initialize.hpp"
#include "copySelect/copySelect.hpp"
#include "crossover/crossover.hpp"
#include "mutate/mutate.hpp"
#include "survivorSelect/survivorSelect.hpp"
#include "gaConfiguration.hpp"
#include "group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::string;
using std::unique_ptr;
using std::mt19937;

GeneticAlgorithm::GeneticAlgorithm(
    const GAConfiguration& config, 
    unique_ptr<Initialize>& initialize,
    mt19937& random
) : 
    _MAX_GENERATION(config.maxGeneration()),
    _numRow(config.graphNumRow()),
    _numColumn(config.graphNumColumn()),
    _indivMutateProbability(config.indivMutateProbability()),
    _geneMutateProbability(config.geneMutateProbability())
{
    Individual::setDefaultGraphCondition(config.graphNumRow(), config.graphNumColumn(), config.graphDegree(), config.graphMaxLength());
    this->_generation = 0;
    this->_group = new Group(config.population());
    this->_bestEverGraph = new GridGraph();

    *_group = initialize->genearteInitialGroup(config.population(), random);
    _group->tally();
}

GeneticAlgorithm::~GeneticAlgorithm() {
    if(this->_group != nullptr) delete this->_group;
}

/// @brief 世代を進める.
void GeneticAlgorithm::progressGeneration(
    unique_ptr<CopySelects::CopySelect> &copySelect,
    unique_ptr<Crossovers::Crossover> &crossover,
    unique_ptr<Mutates::Mutate> &mutate,
    unique_ptr<SurvivorSelects::SurvivorSelect>& survivorSelect,
    mt19937& random
) {
    FillEmptyPortRandomly fillEmptyPort;
    LocalSearch localSearch;
    Group nextGroup(_group->population());

    int numParent = 2;
    int numCrossover = 1;

    int numNextIndivs = 0;
    copySelect->decideSequence(*_group);
    while(numNextIndivs < nextGroup.population()) {
        Group parents(numParent);
        for(int i = 0; i < numParent; ++i) {
            parents.indivs[i] = _group->indivs[copySelect->selectIndex()];
        }

		Group childs(numCrossover);
        for(int i = 0; i < childs.population(); ++i) {
            childs.indivs[i] = crossover->execute(parents.indivs[0], parents.indivs[1], random);
            mutate->execute(childs.indivs[i], random);
		    localSearch.localOptimize(childs.indivs[i]);
            fillEmptyPort(childs.indivs[i], random);
        }
		
		Group survivor = survivorSelect->moveSurvivors(childs, parents, random);
        for(int i = 0; i < survivor.population(); ++i) {
            nextGroup.indivs[numNextIndivs++] = std::move(survivor.indivs[i]);
            if(numNextIndivs == nextGroup.population()) break;
        }
	}

    *(this->_group) = std::move(nextGroup);
    this->_group->tally();
    this->_generation++;

    if(_group->bestIndiv().betterThan(*(this->_bestEverGraph))) {
        *(this->_bestEverGraph) = _group->bestIndiv();
    }
}

/// @brief 終了条件を満たしているか.
bool GeneticAlgorithm::end() const {
    if(_MAX_GENERATION <= _generation) return true;
    if(_group->indivVariation() <= 1) return true;
    return false;
}

/// @brief 最良個体の.edgesファイルを保存.
void GeneticAlgorithm::saveBestEverEdgeFile(const std::string& dirPath) const {
    string fileName = dirPath + "/" + std::to_string(this->_bestEverGraph->aspl()) + ".edges";
    EdgesFileWriter::write(*(this->_bestEverGraph), fileName);
}

int GeneticAlgorithm::bestDiameter() const   { return _group->bestDiameter(); }
double GeneticAlgorithm::bestASPL() const    { return _group->bestASPL(); }
double GeneticAlgorithm::averageASPL() const { return _group->averageASPL(); }
double GeneticAlgorithm::worstASPL() const   { return _group->worstASPL(); }
int GeneticAlgorithm::indivVariation() const { return _group->indivVariation(); }
