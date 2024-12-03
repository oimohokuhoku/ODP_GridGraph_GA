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


int main(void) {
    bool success = true;
    success &= set_embedd_map_value();
    success &= overlay_embedd_maps();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}


