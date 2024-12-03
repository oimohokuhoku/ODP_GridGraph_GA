#include "odpGridGraphGAs.hpp"
#include "../../unitTest.hpp"
#include <random>
#include <vector>
#include <string>
using namespace Cselab23Kimura;
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers;
using std::vector;

bool set_embedd_map_value() {
    UnitTest unitTest("set_embedd_map_value");
    EmbeddMap map(2, 3);
    map.set(0, 0, true);
    map.set(1, 2, true);

    unitTest.assertTrue("element(0, 0)", map.at(0, 0));
    unitTest.assertFalse("element(0, 1)", map.at(0, 1));
    unitTest.assertFalse("element(0, 2)", map.at(0, 2));
    unitTest.assertFalse("element(1, 0)", map.at(1, 0));
    unitTest.assertFalse("element(1, 1)", map.at(1, 1));
    unitTest.assertTrue("element(1, 2)", map.at(1, 2));

    unitTest.assertTrue ("element(0)", map.at(0));
    unitTest.assertFalse("element(1)", map.at(1));
    unitTest.assertFalse("element(2)", map.at(2));
    unitTest.assertFalse("element(3)", map.at(3));
    unitTest.assertFalse("element(4)", map.at(4));
    unitTest.assertTrue ("element(5)", map.at(5));

    unitTest.showResult();
    return unitTest.successAll();
}

bool overlay_embedd_maps() {
    UnitTest unitTest("overlay_embedd_maps");
    EmbeddMap mapA(2, 3);
    mapA.set(0, 0, true);
    mapA.set(1, 2, true);

    EmbeddMap mapB(2, 3);
    mapB.set(0, 2, true);
    mapB.set(1, 0, true);

    EmbeddMap map = mapA.overlay(mapB);
    
    unitTest.assertTrue ("element(0, 0)", map.at(0, 0));
    unitTest.assertFalse("element(0, 1)", map.at(0, 1));
    unitTest.assertTrue ("element(0, 2)", map.at(0, 2));
    unitTest.assertTrue ("element(1, 0)", map.at(1, 0));
    unitTest.assertFalse("element(1, 1)", map.at(1, 1));
    unitTest.assertTrue ("element(1, 2)", map.at(1, 2));

    unitTest.showResult();
    return unitTest.successAll();
}

bool obtain_border_neighbor_map() {
    UnitTest unitTest("obtain_border_neighbor_map");

    EmbeddMap map(5, 5);
    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 2; ++c) {
            map.set(r, c, true);
        }
    }

    std::vector<bool> border = map.borderNeighborMap(1);
    
    unitTest.assertFalse("element(0, 0)", border[0]);
    unitTest.assertTrue("element(0, 1)", border[1]);
    unitTest.assertTrue ("element(0, 2)", border[2]);
    unitTest.assertFalse("element(0, 3)", border[3]);
    unitTest.assertFalse("element(0, 4)", border[4]);

    unitTest.assertFalse("element(1, 0)", border[5]);
    unitTest.assertTrue ("element(1, 1)", border[6]);
    unitTest.assertTrue ("element(1, 2)", border[7]);
    unitTest.assertFalse("element(1, 3)", border[8]);
    unitTest.assertFalse("element(1, 4)", border[9]);

    unitTest.assertTrue ("element(2, 0)", border[10]);
    unitTest.assertTrue ("element(2, 1)", border[11]);
    unitTest.assertTrue ("element(2, 2)", border[12]);
    unitTest.assertFalse("element(2, 3)", border[13]);
    unitTest.assertFalse("element(2, 4)", border[14]);

    unitTest.assertTrue ("element(3, 0)", border[15]);
    unitTest.assertTrue ("element(3, 1)", border[16]);
    unitTest.assertFalse("element(3, 2)", border[17]);
    unitTest.assertFalse("element(3, 3)", border[18]);
    unitTest.assertFalse("element(3, 4)", border[19]);

    unitTest.assertFalse("element(4, 0)", border[20]);
    unitTest.assertFalse("element(4, 1)", border[21]);
    unitTest.assertFalse("element(4, 2)", border[22]);
    unitTest.assertFalse("element(4, 3)", border[23]);
    unitTest.assertFalse("element(4, 4)", border[24]);

    unitTest.showResult();
    return unitTest.successAll();
}


int main(void) {
    bool success = true;
    success &= set_embedd_map_value();
    success &= overlay_embedd_maps();
    success &= obtain_border_neighbor_map();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}


