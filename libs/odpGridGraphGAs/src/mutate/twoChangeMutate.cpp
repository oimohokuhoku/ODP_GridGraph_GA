#include "twoChangeMutate.hpp"

#include "odpGridGraphs.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA::Mutates;
using namespace Cselab23Kimura::OdpGridGraphs;

TwoChangeMutate::TwoChangeMutate(double indivMutateProbability, double geneMutateProbability) :
    _indivMutateProbability(indivMutateProbability),
    _geneMutateProbability(geneMutateProbability)
{
}

void TwoChangeMutate::execute(GridGraph& indiv, std::mt19937& random) {
    long maxRand = static_cast<long>(random.max()) + 1;
    if(!(random() < _indivMutateProbability * maxRand)) return;

    TwoChange twoChange;
    for(int node = 0; node < indiv.numNode(); ++node) {
        if(random() < _geneMutateProbability * maxRand) twoChange(indiv, node, random);
    }
}