#include "odpGridGraphGAs.hpp"
#include "odpGridGraphs.hpp"
#include "../unitTest.hpp"
using namespace Cselab23Kimura;
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::string;

bool copy_group() {
    int population = 3;

    Group groupA(population);
    Group groupB(population);
    groupA[0] = Tests::SimpleGraphGenerate::h2w2d3r2_A();
    groupA[1] = std::nullopt;
    groupA[2] = Tests::SimpleGraphGenerate::h2w2d3r2_B();

    UnitTest unitTest("substitute_for_same_population_group");
    groupB = groupA;
    unitTest.assertTrue("object copy", groupB[0]->matchGraph(*groupA[0]));
    unitTest.assertFalse("empty copy", groupB[1].has_value());
    unitTest.assertTrue("object copy", groupB[2]->matchGraph(*groupA[2]));
    unitTest.showResult();

    return unitTest.successAll();
}

bool tally_fitness() {
    Group group(5);
    group[0] = std::nullopt;
    group[1] = Tests::SimpleGraphGenerate::h2w2d3r2_A();
    group[2] = std::nullopt;
    group[3] = Tests::SimpleGraphGenerate::h2w2d3r2_B();
    group[4] = Tests::SimpleGraphGenerate::h2w2d3r2_C();

    UnitTest unitTest("tally_fitness");
    unitTest.assertEqualInt("best diameter", 1, group.bestDiameter());
    unitTest.assertEqualDouble("best aspl" , 1.0, group.bestAspl(), 1);
    unitTest.assertEqualInt("worst diameter", 2, group.worstDiameter());
    unitTest.assertEqualDouble("worst aspl" , 1.33333, group.worstAspl(), 5);
    unitTest.assertEqualDouble("average diameter", 1.66666, group.averageDiameter(), 5);
    unitTest.assertEqualDouble("average aspl"    , 1.16666, group.averageAspl(), 5);
    
    unitTest.showResult();
    return unitTest.successAll();
}

bool count_individual_variation() {
    Group group(5);
    group[0] = Tests::SimpleGraphGenerate::h2w2d3r2_A();
    group[1] = Tests::SimpleGraphGenerate::h2w2d3r2_A();
    group[2] = std::nullopt;
    group[3] = Tests::SimpleGraphGenerate::h2w2d3r2_A();
    group[4] = Tests::SimpleGraphGenerate::h2w2d3r2_B();

    UnitTest unitTest("count_individual_variation");
    unitTest.assertEqualInt("indiv_variation", 2, group.indivVariation());

    unitTest.showResult();
    return unitTest.successAll();
}

int main(void) {
    bool success = true;

    success &= copy_group();
    success &= tally_fitness();
    success &= count_individual_variation();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}


