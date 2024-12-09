#include "mixSelect.hpp"
#include "odpGridGraphs.hpp"
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::SurvivorSelects;
using std::vector;

MixSelect::MixSelect(vector<SurvivorSelect*> &selects) :
    _selects(selects)
{}

Group MixSelect::moveSurvivors(Group &childs, Group &parents, std::mt19937& random) {
    vector<Group> survivors(_selects.size(), Group(0));
    int numSelectMethod = _selects.size();
    for(int i = 0; i < numSelectMethod; ++i) {
        survivors[i] = _selects[i]->moveSurvivors(childs, parents, random);
    }

    return std::move(mergeGroup(survivors));
}

Group MixSelect::mergeGroup(std::vector<Group>& groups) {
    int totalSurvivors = 0;
    for(auto& group: groups) {
        totalSurvivors += group.population();
    }

    Group result(totalSurvivors); 
    int index = 0;
    for(auto& group: groups) {
        for(int i = 0; i < group.population(); ++i) 
            result[index++] = std::move(group[i]);
    }

    return std::move(result);
}
