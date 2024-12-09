#include "odpGridGraphGAs.hpp"
#include "odpGridGraphs.hpp"
#include "../unitTest.hpp"
using namespace Cselab23Kimura;
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::string;

const std::string EdgesFile1 = "h5w5d4r2_d4l226667.edges";
const std::string EdgesFile2 = "h5w5d4r2_d4l227333.edges";
const std::string EdgesFile3 = "h5w5d4r2_d4l227667.edges";
const std::string EdgesFile4 = "h5w5d4r2_d4l230333.edges";
const std::string EdgesFile5 = "h5w5d4r2_d4l231000.edges";

bool substitute_for_same_population_group() {
    int population = 2;

    Group groupA(population);
    groupA[0] = EdgesFileReader::read(EdgesFile1);
    groupA[1] = EdgesFileReader::read(EdgesFile2);

    Group groupB(population);
    groupB[0] = EdgesFileReader::read(EdgesFile3);
    groupB[1] = EdgesFileReader::read(EdgesFile4);

    UnitTest unitTest("substitute_for_same_population_group");
    groupB = groupA;
    unitTest.assertEqualInt("population equal", groupA.population(), groupB.population());
    for(int i = 0; i < population; ++i) {
        unitTest.assertTrue(
            "individual match",
            groupA[i].matchGraph(groupB[i])
        );
    }
    unitTest.showResult();

    return unitTest.successAll();
}

bool substitute_for_different_population_group() {
    Group groupA(3);
    groupA[0] = EdgesFileReader::read(EdgesFile1);
    groupA[1] = EdgesFileReader::read(EdgesFile2);
    groupA[2] = EdgesFileReader::read(EdgesFile5);

    Group groupB(2);
    groupB[0] = EdgesFileReader::read(EdgesFile3);
    groupB[1] = EdgesFileReader::read(EdgesFile4);
    
    UnitTest unitTest("substitute_for_different_population_group");
    groupB = groupA;
    unitTest.assertEqualInt("population equal", groupA.population(), groupB.population());
    for(int i = 0; i < groupA.population(); ++i) {
        unitTest.assertTrue(
            "individual match",
            groupA[i].matchGraph(groupB[i])
        );
    }
    unitTest.showResult();

    return unitTest.successAll();
}

bool select_without_replacement() {
    Group group(5);
    group[0] = EdgesFileReader::read(EdgesFile1);
    group[1] = EdgesFileReader::read(EdgesFile2);
    group[2] = EdgesFileReader::read(EdgesFile3);
    group[3] = EdgesFileReader::read(EdgesFile4);
    group[4] = EdgesFileReader::read(EdgesFile5);

    UnitTest unitTest("tally_fitness");
    group.tally();
    unitTest.assertEqualInt("best diameter", group.bestDiameter(), 4);
    unitTest.assertEqualDouble("best ASPL", group.bestASPL(),  2.26667, 4);
    unitTest.assertEqualDouble("worst ASPL", group.worstASPL(), 2.31000, 3);

    unitTest.showResult();
    return unitTest.successAll();
}

int main(void) {
    bool success = true;
    GridGraph::setDefaultGraphCondition(5, 5, 4, 2);

    success &= substitute_for_same_population_group();
    success &= substitute_for_different_population_group();
    success &= select_without_replacement();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}


