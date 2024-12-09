#include "odpGridGraphGAs.hpp"
#include "odpGridGraphs.hpp"
#include "../../unitTest.hpp"
#include <random>
#include <vector>
using namespace Cselab23Kimura;
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::vector;

bool select_without_replacement() {
    constexpr int population = 5;
    RandomInitialize randomGraphGenerate;
    std::mt19937 mt(42);

    Group group = randomGraphGenerate.genearteInitialGroup(population, mt);

    UnitTest unitTest("select without replacement");

    CopySelects::RandomSelectWithoutReplacement select(mt());
    select.decideSequence(group);

    vector<bool> selected(population, false);
    for(int i = 0; i < population; ++i) {
        int index = select.selectIndex();
        unitTest.assertFalse("not duplicate select", selected[index]);
        selected[index] = true;
    }

    unitTest.showResult();
    return unitTest.successAll();
}

int main(void) {
    bool success = true;
    GridGraph::setDefaultGraphCondition(5, 5, 4, 2);

    success &= select_without_replacement();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}


