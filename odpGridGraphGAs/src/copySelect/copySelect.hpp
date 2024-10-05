#pragma once

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class Group;

    class CopySelect {
    public:
        virtual ~CopySelect() = default;
        virtual void decideOrder(const Group& group) = 0;
        virtual int selectIndex() = 0;
    };
}