#include "odpGridGraphGAs.hpp"
#include "odpGridGraphs.hpp"
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

bool only_one_individual_has_been_moved() {
    constexpr int population = 5;
    RandomInitialize randomGraphGenerate(Grid(5, 5, 4, 2));
    std::mt19937 mt(42);

    Group parents = randomGraphGenerate.genearteInitialGroup(population, mt);
    Group childs  = randomGraphGenerate.genearteInitialGroup(population, mt);

    UnitTest unitTest("only one individual has been moved");

    SurvivorSelects::RankingSelect select;
    Group survivor = select.moveSurvivors(parents, childs, mt);
    unitTest.assertEqualInt("group size is 1" ,survivor.population(), 1);

    int movedCount = 0;
    for(int i = 0; i < parents.population(); ++i) {
        if(!parents[i].has_value()) movedCount++;
    }
    for(int i = 0; i < childs.population(); ++i) {
        if(!childs[i].has_value()) movedCount++;
    }
    unitTest.assertEqualInt("count of moved individual", 1, movedCount);

    unitTest.showResult();
    return unitTest.successAll();
}

bool maybe_selected_according_to_ranking() {
    std::mt19937 mt(42);

    constexpr int numIndiv = 5;
    GridGraph* indivs[numIndiv];
    for(int i = 0; i < numIndiv; ++i) indivs[i] = new GridGraph(5, 5, 4, 2);
    *indivs[0] = EdgesFileReader::read(EdgesFile1);
    *indivs[1] = EdgesFileReader::read(EdgesFile2);
    *indivs[2] = EdgesFileReader::read(EdgesFile3);
    *indivs[3] = EdgesFileReader::read(EdgesFile4);
    *indivs[4] = EdgesFileReader::read(EdgesFile5);

    Group parents(3);
    Group childs(2);

    UnitTest unitTest("maybe_selected_according_to_ranking");
    SurvivorSelects::RankingSelect select;
    vector<int> selectedCount(5, 0);
    for(int n = 0; n < 1000; ++n) {
        parents[0] = *indivs[0];
        parents[1] = *indivs[1];
        parents[2] = *indivs[2];
        childs[0]  = *indivs[3];
        childs[1]  = *indivs[4];

        Group survivor = select.moveSurvivors(childs, parents, mt);
        for(int i = 0; i < numIndiv; ++i) {
            if(survivor[0]->matchGraph(*indivs[i])) {
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
    GridGraph* indivs[numIndiv];
    for(int i = 0; i < numIndiv; ++i) indivs[i] = new GridGraph(5, 5, 4, 2);
    *indivs[0] = EdgesFileReader::read(EdgesFile1);
    *indivs[1] = EdgesFileReader::read(EdgesFile2);
    *indivs[2] = EdgesFileReader::read(EdgesFile3);
    *indivs[3] = EdgesFileReader::read(EdgesFile4);
    *indivs[4] = EdgesFileReader::read(EdgesFile5);

    Group parents(3);
    Group childs(2);

    UnitTest unitTest("select_from_group_including_null");

    SurvivorSelects::RankingSelect select;
    vector<int> selectedCount(5, 0);
    bool selectNull = false;
    for(int n = 0; n < 1000; ++n) {
        parents[0] = *indivs[0];
        parents[1] = *indivs[1];
        parents[2] = *indivs[2];
        childs[0]  = *indivs[3];
        childs[1]  = *indivs[4];

        //generate empty object
        GridGraph dummy(5, 5, 4, 2);
        dummy = std::move(*parents[0]);
        dummy = std::move(*childs[0]);

        Group survivor = select.moveSurvivors(childs, parents, mt);
        if(survivor[0]->isValidObject()) {
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

    success &= only_one_individual_has_been_moved();
    success &= maybe_selected_according_to_ranking();
    success &= select_from_group_including_null();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}


