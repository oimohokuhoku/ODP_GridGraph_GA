#pragma once

namespace Cselab23Kimura::OdpGridGraphs::GA
{
    class Group;

    class SurvivorSelect {
    public:
        virtual ~SurvivorSelect() = default;
        virtual Group select(const Group& childs, const Group& parents) = 0;
    };
}