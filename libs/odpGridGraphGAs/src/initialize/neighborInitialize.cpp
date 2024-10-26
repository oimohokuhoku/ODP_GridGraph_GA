#include "./neighborInitialize.hpp"
#include "odpGridGraphs.hpp"
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;

NeighborInitialize::NeighborInitialize(const std::string& startEdgesFilepath, int numMutate):
    _startEdgesFilepath(startEdgesFilepath),
    _numMutate(numMutate)
{}

Group NeighborInitialize::genearteInitialGroup(int population, std::mt19937& random) {
    Group initialGroup(population);
    Individual startIndiv = EdgesFileReader::read(_startEdgesFilepath);
    TwoChange mutate;
    CountDifferentEdge countDiffEdge;
    int totalNumDiffEdge = 0;

    for(int i = 0; i < population; ++i) {
        Individual indiv = startIndiv;

        for(int j = 0; j < _numMutate; ++j) {
            mutate(indiv, random);
        }

        totalNumDiffEdge += countDiffEdge.count(indiv, startIndiv);
        indiv.evaluate();
        
        initialGroup.indivs[i] = std::move(indiv);
    }

    this->_averageNumDiffEdge = totalNumDiffEdge / population;
    return initialGroup;
}