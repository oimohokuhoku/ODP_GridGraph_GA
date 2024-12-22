#include "mixSelect.hpp"
#include <optional>
#include "odpGridGraphs.hpp"
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::SurvivorSelects;
using std::vector;
using std::optional;

MixSelect::MixSelect(vector<SurvivorSelect*> &selects) :
    _selects(selects)
{}

Group MixSelect::moveSurvivors(Group &childs, Group &parents, std::mt19937& random) {
    vector<optional<Group>> survivors(_selects.size());
    int numSelectMethod = _selects.size();
    for(int i = 0; i < numSelectMethod; ++i) {
        survivors[i] = _selects[i]->moveSurvivors(childs, parents, random);
    }

    return std::move(mergeGroup(survivors));
}

Group MixSelect::mergeGroup(vector<optional<Group>>& groups) {
    int totalSurvivors = 0;
    for(auto& group: groups) {
        totalSurvivors += group->population();
    }

    Group result(totalSurvivors); 
    int index = 0;
    for(auto& group: groups) {
        for(int i = 0; i < group->population(); ++i) 
            result[index++] = std::move(group->get(i));
    }

    return result;
}
