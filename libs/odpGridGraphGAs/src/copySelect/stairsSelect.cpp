#include "stairsSelect.hpp"
#include <algorithm>
#include "odpGridGraphs.hpp"
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::CopySelects;
using std::vector;

StairsSelect::StairsSelect() : _index(0), _reserve(-1) {}

void StairsSelect::decideSequence(const Group& group) {
    _population = group.population();
	if(_population > _sequence.size()) _sequence.resize(_population);

    vector<int> ranking(_population);
    for(int i = 0; i < _population; ++i) {
        ranking[i] = i;
    }

    //FIXME: バブルソート使ってるけど、もっといいアルゴリズムに変えたい.
    for(int end = _population; end > 0; --end) {
		for(int i = 0; i + 1 < end; ++i) {
			const GridGraph& before = *(group[ranking[i]]);
			const GridGraph& after  = *(group[ranking[i + 1]]);
			if(before.betterThan(after)) {
				int temp = ranking[i];
				ranking[i] = ranking[i + 1];
				ranking[i + 1] = temp;
			}
		}
	}

	int tail = _population - 1;
	for(int i = 0; i * 2 < _population; ++i) {
		_sequence[i] = ranking[i * 2];
	}
	for(int i = 0; (i * 2) + 1 < _population; ++i) {
		_sequence[tail - i] = ranking[(i * 2) + 1];
	}
}

int StairsSelect::selectIndex() {
	if(_reserve == -1) {
    	int output = _sequence[_index];
    	_index++;
    	_index %= _sequence.size();
		_reserve = _index;
    	return output;
	}
	else {
		int temp = _reserve;
		_reserve = -1;
		return _sequence[temp];
	}
}
