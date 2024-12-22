#include "rankingSelect.hpp"
#include <vector>
#include <iostream>
#include "odpGridGraphs.hpp"
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::SurvivorSelects;
using std::vector;

Group RankingSelect::moveSurvivors(Group& childs, Group& parents, std::mt19937& random) {
    //FIXME: リファクタリング
    int numIndiv = childs.population() + parents.population();
    
    vector<int> order(numIndiv);
    for(int i = 0; i < numIndiv; ++i) order[i] = i;

    vector<GridGraph*> indivs(numIndiv);
    for(int i = 0; i < childs.population();  ++i) {
        if(childs[i].has_value())
            indivs[i] = &(childs[i].value());
        else   
            indivs[i] = nullptr;
    }
    for(int i = 0; i < parents.population(); ++i) {
        if(parents[i].has_value())
            indivs[i + childs.population()] = &(parents[i].value());
        else
            indivs[i + childs.population()] = nullptr;
    }

    //良い個体が前にくるようにソート
    for(int tail = numIndiv - 1; tail > 0; --tail) {
        for(int i = 0; i + 1 <= tail; ++i) {
            const GridGraph* indivA = indivs[order[i]];
            const GridGraph* indivB = indivs[order[i + 1]];

            if(indivB == nullptr) continue;
            if(indivA == nullptr || indivA->worseThan(*indivB)) {
                int temp = order[i];
                order[i] = order[i + 1];
                order[i + 1] = temp;
            }
        }
    }

    //nullオブジェクトを除外
    for(int i = 0; i < numIndiv; ++i) {
        if(indivs[order[i]] == nullptr) { numIndiv--; }
    }

    Group result(1);
    int sumRank = ((numIndiv - 1) * numIndiv) / 2; //sum of 0 to (numIndiv-1)
    int r = random() % sumRank;
    for(int i = 0; i < numIndiv; ++i) {
        r -= (numIndiv - i) + 1;
        if(r <= 0) {
            result[0] = std::move(*indivs[order[i]]);
            return result;
        }
    }

    throw std::logic_error("Unexpected exception");
}
