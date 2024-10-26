#pragma once

#include <vector>
#include "copySelect.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class Group;

    namespace CopySelects 
    {
        class StairsSelect : public CopySelect{
        public:
            StairsSelect();
            ~StairsSelect() = default;
            void decideSequence(const Group& group) override;
            int selectIndex() override;
        private:
            std::vector<int> _sequence;
            int _population;
            int _index;
            int _reserve;
        };
    }
}