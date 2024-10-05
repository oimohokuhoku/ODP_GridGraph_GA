#pragma once

#include "survivorSelect.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA 
{
    class Group;

    class PassAllChild : public SurvivorSelect{
    public:
        ~PassAllChild() = default;
        Group select(const Group& childs, const Group& parents) override;
    };
}