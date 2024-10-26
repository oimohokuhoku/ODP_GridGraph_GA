#include "randomSelectWithoutReplacement.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::CopySelects;
using std::vector;

RandomSelectWithoutReplacement::RandomSelectWithoutReplacement(int seed) : 
    _random(std::mt19937(seed)),
    _sequence(vector<int>(0)),
    _index(-1)
{
}

void RandomSelectWithoutReplacement::decideSequence(const Group& group) {
    if(_sequence.size() != group.population()) {
        _sequence.resize(group.population());
    }

    int length = _sequence.size();
    for(int i = 0; i < length; ++i) {
        _sequence[i] = i;
    }

    std::shuffle(_sequence.begin(), _sequence.end(), _random);
    _index = 0;
}

int  RandomSelectWithoutReplacement::selectIndex() {
    if(_index >= _sequence.size()) {
        std::cerr << "RandomSelectWithoutReplacement::selectIndex()" << std::endl;
        exit(EXIT_FAILURE);
    }

    int result = _sequence[_index];
    _index++;
    return result;
}
