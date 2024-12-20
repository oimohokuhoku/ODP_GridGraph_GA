#include "blockCrossover.hpp"
#include <vector>
#include "odpGridGraphs.hpp"
#include "embeddPartialGraph.hpp"
#include "embeddMap.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers;

using std::unique_ptr;
using std::vector;

BlockCrossover::BlockCrossover(GenerateEmbeddMapUnits *const generateEmbeddMapUnits) :
    _generateEmbeddMapUnits(generateEmbeddMapUnits)
{}

GridGraph BlockCrossover::execute(const GridGraph& parentA, const GridGraph& parentB, std::mt19937& random) {
    EmbeddPartialGraph embeddPartialGraph;
    vector<EmbeddMap> embeddMapUnits = _generateEmbeddMapUnits->execute(parentA.numRow(), parentA.numColumn(), random);
    EmbeddMap embeddMap(parentA.numRow(), parentA.numColumn());

    for(EmbeddMap map: embeddMapUnits) {
        if(random() % 2 == 0) embeddMap = embeddMap.overlay(map);
    }

    GridGraph child = parentA;
    child = embeddPartialGraph(parentA, parentB, embeddMap, random);

    LocalSearch localSearch;
    localSearch.partialGraphOptimize(child, embeddMap.borderNeighborMap(2));
    return child;
}
