#include"lambdaChangeMutate.hpp"

#include "odpGridGraphs.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA::Mutates;

LambdaChangeMutate::LambdaChangeMutate(double indivMutateProbability, double geneMutateProbability):
    _indivMutateProbability(indivMutateProbability),
    _geneMutateProbability(geneMutateProbability)
{}

void LambdaChangeMutate::execute(GridGraph& indiv, std::mt19937& random) {
    long maxRand = static_cast<long>(random.max()) + 1;
    if(!(random() < _indivMutateProbability * maxRand)) return;

    EdgeSwap swap(3);
    for(long i = 0; i < indiv.numNode(); ++i) {
        if(random() < _geneMutateProbability * maxRand)
            swap.swap(indiv, i, random);
    }
}