#include "odpGridGraphGAs.hpp"
#include "../../unitTest.hpp"
#include <random>
#include <vector>
#include <string>
using namespace Cselab23Kimura;
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::vector;


bool select_elitist_individual() {
    constexpr int population = 5;
    RandomInitialize randomGraphGenerate;
    std::mt19937 mt(42);

    Group parents = randomGraphGenerate.genearteInitialGroup(population, mt);
    Group childs  = randomGraphGenerate.genearteInitialGroup(population, mt);

    UnitTest unitTest("select elitist individual");

    SurvivorSelects::ElitistSelect select;
    Group survivor = select.moveSurvivors(parents, childs, mt);

    unitTest.assertEqualInt("group size is 1" ,survivor.population(), 1);

    int movedCount = 0;
    for(int i = 0; i < parents.population(); ++i) {
        if(parents.indivs[i].adjacent == nullptr) movedCount++;
    }
    for(int i = 0; i < childs.population(); ++i) {
        if(childs.indivs[i].adjacent == nullptr) movedCount++;
    }
    unitTest.assertEqualInt("count of moved individual is 1", movedCount, 1);

    int selectedRank = 0;
    for(int i = 0; i < parents.population(); ++i) {
        if(survivor.indivs[0].worseThan(parents.indivs[i])) selectedRank++;
    }
    for(int i = 0; i < childs.population(); ++i) {
        if(survivor.indivs[0].worseThan(childs.indivs[i])) selectedRank++;
    }
    unitTest.assertEqualInt("Select Elitist", selectedRank, 0);

    unitTest.showResult();
    return unitTest.successAll();
}


int main(void) {
    bool success = true;
    GridGraph::setDefaultGraphCondition(5, 5, 4, 2);

    success &= select_elitist_individual();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}


