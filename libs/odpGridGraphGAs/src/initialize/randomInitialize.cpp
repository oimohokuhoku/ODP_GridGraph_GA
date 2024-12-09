#include "randomInitialize.hpp"

#include "odpGridGraphs.hpp"
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;

Group RandomInitialize::genearteInitialGroup(int population, std::mt19937& random) {
    Randomize randomize;
    Group initialGroup(population);

    for(int i = 0; i < population; ++i) {
        randomize(initialGroup[i], random);
        initialGroup[i].evaluate();
    }

    return initialGroup;
}