#include "elitistSelect.hpp"
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::SurvivorSelects;

Group ElitistSelect::moveSurvivors(Group& childs, Group& parents, std::mt19937& random) {
    constexpr int CHILDS_GROUP  = 0;
    constexpr int PARENTS_GROUP = 1;
    int selectedGroup = CHILDS_GROUP;
    int selectedIndex = 0;
    Individual& elitist = childs.indivs[0];

    for(int i = 1; i < childs.population(); ++i) {
        if(childs.indivs[i].betterThan(elitist)) {
            selectedGroup = CHILDS_GROUP;
            selectedIndex = i;
        }
    }
    for(int i = 0; i < parents.population(); ++i) {
        if(parents.indivs[i].betterThan(elitist)) {
            selectedGroup = PARENTS_GROUP;
            selectedIndex = i;
        }
    }

    Group result(1);
    if(selectedGroup == CHILDS_GROUP) {
        result.indivs[0] = std::move(childs.indivs[selectedIndex]);
    }
    else {
        result.indivs[0] = std::move(parents.indivs[selectedIndex]);
    }

    return result;
}
