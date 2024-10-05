#include"lambdaChangeMutate.hpp"

#include "odpGridGraphs/include/gridGraphs.hpp"
#include "commonLib/randoms/random.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;

LambdaChangeMutate::LambdaChangeMutate(double indivMutateProbability, double geneMutateProbability):
    _indivMutateProbability(indivMutateProbability),
    _geneMutateProbability(geneMutateProbability)
{}

void LambdaChangeMutate::execute(GridGraph& indiv) {
    if(!Random::roulette(_indivMutateProbability)) return;

    EdgeSwap swap(3);
    std::mt19937 mt(Random::randInt());
    for(int i = 0; i < indiv.numNode(); ++i) {
        if(Random::roulette(_geneMutateProbability))
            swap.swap(indiv, i, mt);
    }
}