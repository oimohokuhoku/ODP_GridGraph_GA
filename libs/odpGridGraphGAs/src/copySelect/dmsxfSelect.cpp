#include "dmsxfSelect.hpp"

#include <algorithm>
#include "odpGridGraphs.hpp"
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::CopySelects;
using std::vector;

DmsxfSelect::DmsxfSelect(std::mt19937& randomEngine) : 
    _index(0) ,
    _random(std::mt19937(randomEngine()))
{}

void DmsxfSelect::decideSequence(const Group& group) {
    if(_sequence.size() != group.population()) {
        _sequence.resize(group.population());
        for(size_t i = 0; i < _sequence.size(); ++i) _sequence[i] = i;
    }
    std::shuffle(_sequence.begin(), _sequence.end(), _random);
}

int DmsxfSelect::selectIndex() {
	int temp = _sequence[_index];
    _index = (_index + 1) % _sequence.size();
    return temp;
}
