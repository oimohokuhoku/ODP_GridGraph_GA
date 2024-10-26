#pragma once
#include<random>

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class Group;

    namespace SurvivorSelects {
        class SurvivorSelect {
        public:
            virtual ~SurvivorSelect() = default;
            virtual Group moveSurvivors(Group& childs, Group& parents, std::mt19937& random) = 0;
        };
    }
}