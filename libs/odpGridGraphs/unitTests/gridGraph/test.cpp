#include "odpGridGraphs.hpp"
#include "../unitTest.hpp"
#include <vector>
using namespace Cselab23Kimura;
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::Tests;
using std::vector;

bool initialize() {
    UnitTest unitTest("initialize");
    GridGraph graph(5, 4, 3, 2);
    unitTest.assertEqualInt("number of row",    5, graph.numRow());
    unitTest.assertEqualInt("number of column", 4, graph.numColumn());
    unitTest.assertEqualInt("number of node"  , 20, graph.numNode());
    unitTest.assertEqualInt("degree", 3, graph.degree());
    unitTest.assertEqualInt("length", 2, graph.maxLength());
    unitTest.assertTrue("valid object", graph.isValidObject());

    for(int i = 0; i < graph.numNode(); ++i) {
        for(int d = 0; d < graph.degree(); ++d) {
            unitTest.assertEqualInt("no edges exist", GridGraph::EMPTY_PORT, graph.adjacent(i, d));
        }
    }

    for(int i = 0; i < graph.numNode(); ++i) {
        unitTest.assertEqualInt("all degree is 0", 0, graph.nodeDegree(i));
    }

    unitTest.showResult();
    return unitTest.successAll();
}

int main(void) {
    bool success = true;

    success &= initialize();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}


