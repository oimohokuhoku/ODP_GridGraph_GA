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
    int numIndiv = childs.population() + parents.population();
    vector<GridGraph*> indivs(numIndiv);
    vector<int> order(numIndiv);

    for(int i = 0; i < numIndiv; ++i) order[i] = i;
    for(int i = 0; i < childs.population();  ++i) indivs[i] = &(childs[i]);
    for(int i = 0; i < parents.population(); ++i) indivs[i + childs.population()] = &(parents[i]);

    //良い個体が前にくるようにソート
    for(int tail = numIndiv - 1; tail > 0; --tail) {
        for(int i = 0; i + 1 <= tail; ++i) {
            GridGraph *indivA = indivs[order[i]];
            GridGraph *indivB = indivs[order[i + 1]];

            if(indivA->worseThan(*indivB)) {
                int temp = order[i];
                order[i] = order[i + 1];
                order[i + 1] = temp;
            }
        }
    }

    //nullオブジェクトを除外
    for(int i = 0; i < numIndiv; ++i) {
        if(indivs[order[i]]->adjacent == nullptr) { numIndiv--; }
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

    std::cerr << "Cselab23Kimura::OdpGridGraphs::GA::SurvivorSelects::RankingSelect::moveSurvivor(Group, Group, std::mt19938) : " << std::endl;
    std::cerr << "Unexpected Error" << std::endl;
    exit(EXIT_FAILURE);
}
