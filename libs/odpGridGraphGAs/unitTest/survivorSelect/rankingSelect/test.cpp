#include "odpGridGraphGAs.hpp"
#include "../../unitTest.hpp"
#include <random>
#include <vector>
#include <string>
using namespace Cselab23Kimura;
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::vector;

const std::string EdgesFile1 = "h5w5d4r2_d4l226667.edges";
const std::string EdgesFile2 = "h5w5d4r2_d4l227333.edges";
const std::string EdgesFile3 = "h5w5d4r2_d4l227667.edges";
const std::string EdgesFile4 = "h5w5d4r2_d4l230333.edges";
const std::string EdgesFile5 = "h5w5d4r2_d4l231000.edges";

bool select_elitist_individual() {
    constexpr int population = 5;
    RandomInitialize randomGraphGenerate;
    std::mt19937 mt(42);

    Group parents = randomGraphGenerate.genearteInitialGroup(population, mt);
    Group childs  = randomGraphGenerate.genearteInitialGroup(population, mt);

    UnitTest unitTest("only one individual has been moved");

    SurvivorSelects::RankingSelect select;
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

    unitTest.showResult();
    return unitTest.successAll();
}

bool maybe_selected_according_to_ranking() {
    std::mt19937 mt(42);

    constexpr int numIndiv = 5;
    Individual indivs[numIndiv];
    indivs[0] = EdgesFileReader::read(EdgesFile1);
    indivs[1] = EdgesFileReader::read(EdgesFile2);
    indivs[2] = EdgesFileReader::read(EdgesFile3);
    indivs[3] = EdgesFileReader::read(EdgesFile4);
    indivs[4] = EdgesFileReader::read(EdgesFile5);

    Group parents(3);
    Group childs(2);

    UnitTest unitTest("maybe_selected_according_to_ranking");
    SurvivorSelects::RankingSelect select;
    vector<int> selectedCount(5, 0);
    for(int n = 0; n < 1000; ++n) {
        parents.indivs[0] = indivs[0];
        parents.indivs[1] = indivs[1];
        parents.indivs[2] = indivs[2];
        childs.indivs[0]  = indivs[3];
        childs.indivs[1]  = indivs[4];

        Group survivor = select.moveSurvivors(childs, parents, mt);
        for(int i = 0; i < numIndiv; ++i) {
            if(survivor.indivs[0].matchGraph(indivs[i])) {
                selectedCount[i]++;
                break;
            }
        }
    }

    for(int i = 0; i + 1 < numIndiv; ++i) {
        unitTest.assertTrue("better selected", selectedCount[i] >= selectedCount[i + 1]);
    }

    unitTest.showResult();
    return unitTest.successAll();
}

bool select_from_group_including_null() {
    std::mt19937 mt(42);

    constexpr int numIndiv = 5;
    Individual indivs[numIndiv];
    indivs[0] = EdgesFileReader::read(EdgesFile1);
    indivs[1] = EdgesFileReader::read(EdgesFile2);
    indivs[2] = EdgesFileReader::read(EdgesFile3);
    indivs[3] = EdgesFileReader::read(EdgesFile4);
    indivs[4] = EdgesFileReader::read(EdgesFile5);

    Group parents(3);
    Group childs(2);

    UnitTest unitTest("select_from_group_including_null");

    SurvivorSelects::RankingSelect select;
    vector<int> selectedCount(5, 0);
    bool selectNull = false;
    for(int n = 0; n < 1000; ++n) {
        parents.indivs[0] = indivs[0];
        parents.indivs[1] = indivs[1];
        parents.indivs[2] = indivs[2];
        childs.indivs[0]  = indivs[3];
        childs.indivs[1]  = indivs[4];

        //generate empty object
        Individual dummy;
        dummy = std::move(parents.indivs[0]);
        dummy = std::move(childs.indivs[0]);

        Group survivor = select.moveSurvivors(childs, parents, mt);
        if(survivor.indivs[0].adjacent == nullptr) {
            selectNull = true;
            break;
        }
    }
    unitTest.assertFalse("not select null object", selectNull);

    unitTest.showResult();
    return unitTest.successAll();
}

int main(void) {
    bool success = true;
    GridGraph::setDefaultGraphCondition(5, 5, 4, 2);

    success &= select_elitist_individual();
    success &= maybe_selected_according_to_ranking();
    success &= select_from_group_including_null();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}


