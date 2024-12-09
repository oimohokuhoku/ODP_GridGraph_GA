#pragma once
#include "survivorSelect.hpp"
#include <vector>
#include <random>

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class Group;

    namespace SurvivorSelects {
        class MixSelect: public SurvivorSelect {
        public:
            MixSelect(std::vector<SurvivorSelect*>& selects);
            ~MixSelect() = default;
            Group moveSurvivors(Group& childs, Group& parents, std::mt19937& random) override;
        private:
            std::vector<SurvivorSelect*>& _selects;
            Group mergeGroup(std::vector<Group>& groups);
        };
    }
}