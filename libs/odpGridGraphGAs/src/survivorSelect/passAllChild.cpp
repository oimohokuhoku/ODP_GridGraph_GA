#include "passAllChild.hpp"

#include <utility>
#include <random>
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::SurvivorSelects;

Group PassAllChild::moveSurvivors(Group& childs, Group& parents, std::mt19937& random) {
    return std::move(childs);
}