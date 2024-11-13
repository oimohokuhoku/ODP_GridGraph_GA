#pragma once

#include <vector>
#include <random>
#include "copySelect.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class Group;

    namespace CopySelects 
    {
        class DmsxfSelect : public CopySelect{
        public:
            DmsxfSelect(std::mt19937& randomEngine);
            ~DmsxfSelect() = default;
            void decideSequence(const Group& group) override;
            int selectIndex() override;
        private:
            std::mt19937 _random;
            std::vector<int> _sequence;
            int _population;
            int _index;
        };
    }
}