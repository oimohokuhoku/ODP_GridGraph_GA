#pragma once
#include "survivorSelect.hpp"
#include <vector>
#include <memory>
#include <random>

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class Group;

    namespace SurvivorSelects {
        class MixSelect: public SurvivorSelect {
        public:
            MixSelect(std::vector<std::unique_ptr<SurvivorSelect>>& selects);
            ~MixSelect();
            Group moveSurvivors(Group& childs, Group& parents, std::mt19937& random) override;
        private:
            std::vector<std::unique_ptr<SurvivorSelect>>& _selects;
            Group mergeGroup(std::vector<Group>& groups);
        };
    }
}