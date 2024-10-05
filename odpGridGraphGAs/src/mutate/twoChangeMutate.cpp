#include "twoChangeMutate.hpp"

#include "odpGridGraphs/include/gridGraphs.hpp"
#include "commonLib/randoms/random.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs;

TwoChangeMutate::TwoChangeMutate(double indivMutateProbability, double geneMutateProbability) :
    _indivMutateProbability(indivMutateProbability),
    _geneMutateProbability(geneMutateProbability)
{
}

void TwoChangeMutate::execute(Individual& indiv, std::mt19937& random) {
    //TODO Randomの廃止
    if(!Random::roulette(_indivMutateProbability)) return;

    TwoChange twoChange;
    for(int node = 0; node < indiv.numNode(); ++node) {
        if(Random::roulette(_geneMutateProbability)) twoChange(indiv, node, random);
    }
}