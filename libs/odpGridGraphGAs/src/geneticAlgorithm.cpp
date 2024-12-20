#include "geneticAlgorithm.hpp"
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
    Initialize *const initialize,
    mt19937& random
) : 
    _MAX_GENERATION(config.maxGeneration()),
    _numRow(config.graphNumRow()),
    _numColumn(config.graphNumColumn()),
    _indivMutateProbability(config.indivMutateProbability()),
    _geneMutateProbability(config.geneMutateProbability())
{
    this->_generation = 0;
    this->_group = new Group(config.population());
    this->_bestEverGraph = new GridGraph(config.graphNumRow(), config.graphNumColumn(), config.graphDegree(), config.graphMaxLength());

    *_group = initialize->genearteInitialGroup(config.population(), random);
}

GeneticAlgorithm::~GeneticAlgorithm() {
    if(this->_group != nullptr) delete this->_group;
}

/// @brief 世代を進める.
void GeneticAlgorithm::progressGeneration(
    CopySelects::CopySelect *const copySelect,
    Crossovers::Crossover *const crossover,
    Mutates::Mutate *const mutate,
    SurvivorSelects::SurvivorSelect *const survivorSelect,
    std::mt19937& random
) {
    Group nextGroup(_group->population());

    int numParent = 2;
    int numCrossover = 10;

    int numNextIndivs = 0;
    copySelect->decideSequence(*_group);
    while(numNextIndivs < nextGroup.population()) {
        Group parents(numParent);
        for(int i = 0; i < numParent; ++i) {
            parents[i] = (*_group)[copySelect->selectIndex()];
        }

		Group childs(numCrossover);
        for(int i = 0; i < childs.population(); ++i) {
            childs[i] = crossover->execute(*(parents[0]), *(parents[1]), random);
            mutate->execute(*(childs[i]), random);
        }
		
		Group survivor = survivorSelect->moveSurvivors(childs, parents, random);
        for(int i = 0; i < survivor.population(); ++i) {
            nextGroup[numNextIndivs++] = std::move(survivor[i]);
            if(numNextIndivs == nextGroup.population()) break;
        }
	}
    *(this->_group) = std::move(nextGroup);
    this->_generation++;

    LocalSearch localSearch;
    for(int i = 0; i < _group->population(); ++i) {
        localSearch.localOptimize(*(*_group)[i]);
    }

    if(!_bestEverGraph->betterThan(_group->bestIndiv())) {
        *_bestEverGraph = _group->bestIndiv();
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
double GeneticAlgorithm::bestAspl() const    { return _group->bestAspl(); }
double GeneticAlgorithm::averageASPL() const { return _group->averageAspl(); }
double GeneticAlgorithm::worstASPL() const   { return _group->worstAspl(); }
int GeneticAlgorithm::indivVariation() const { return _group->indivVariation(); }
