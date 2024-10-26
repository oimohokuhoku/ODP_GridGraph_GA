#pragma once
#include "copySelect.hpp"
#include <vector>
#include <random>

namespace Cselab23Kimura {
    namespace OdpGridGraphs {
        namespace GA {
            class Group;
            
            namespace CopySelects {
                class RandomSelectWithoutReplacement : public CopySelect{
                public:
                    RandomSelectWithoutReplacement(int seed);
                    ~RandomSelectWithoutReplacement() = default;
                    void decideSequence(const Group& group) override;
                    int selectIndex() override;
                private:
                    std::mt19937 _random;
                    std::vector<int> _sequence;
                    int _index;
                    
                    void decideSequence(int population);
                };
            }
        }
    }
}