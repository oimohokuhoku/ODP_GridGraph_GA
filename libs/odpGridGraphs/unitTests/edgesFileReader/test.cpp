#include "odpGridGraphs.hpp"
#include "../unitTest.hpp"
#include <vector>
using namespace Cselab23Kimura;
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::Tests;
using std::vector;

bool read_constraints_and_edges() {
    UnitTest unitTest("read_constraints_and_edges");

    GridGraph graph = EdgesFileReader::read("test.edges");
    unitTest.assertEqualInt("a number of row",    2, graph.numRow());
    unitTest.assertEqualInt("a number of column", 3, graph.numColumn());
    unitTest.assertEqualInt("degree", 3, graph.degree());
    unitTest.assertEqualInt("length", 3, graph.maxLength());

    unitTest.assertTrue("edge(0,0)-(0,1)", graph.haveEdge(0, 1));
    unitTest.assertTrue("edge(0,0)-(1,0)", graph.haveEdge(0, 3));
    unitTest.assertTrue("edge(0,0)-(1,2)", graph.haveEdge(0, 5));
    unitTest.assertTrue("edge(0,1)-(0,2)", graph.haveEdge(1, 2));
    unitTest.assertTrue("edge(0,1)-(1,0)", graph.haveEdge(1, 3));
    unitTest.assertTrue("edge(0,2)-(1,2)", graph.haveEdge(2, 5));
    unitTest.assertTrue("edge(1,0)-(1,1)", graph.haveEdge(3, 4));
    unitTest.assertTrue("edge(1,1)-(1,2)", graph.haveEdge(4, 5));

    unitTest.showResult();
    return unitTest.successAll();
}

int main(void) {
    bool success = true;

    success &= read_constraints_and_edges();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}


