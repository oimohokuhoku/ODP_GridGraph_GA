#pragma once
#include "survivorSelect.hpp"
#include <random>

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class Group;

    namespace SurvivorSelects {
        class PassAllChild : public SurvivorSelect{
        public:
            ~PassAllChild() = default;
            Group moveSurvivors(Group& childs, Group& parents, std::mt19937& random) override;
        };
    }
}