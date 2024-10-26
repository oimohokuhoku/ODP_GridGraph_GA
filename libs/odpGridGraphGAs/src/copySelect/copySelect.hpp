#pragma once

//FIXME: void decideSequence(Group)をファクトリメソッドに切り出し

namespace Cselab23Kimura::OdpGridGraphs::GA 
{
    class Group;

    namespace CopySelects 
    {
        class CopySelect {
        public:
            virtual ~CopySelect() = default;
            virtual void decideSequence(const Group &group) = 0;
            virtual int selectIndex() = 0;
        };
    }
}