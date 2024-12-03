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

BlockCrossover::BlockCrossover(unique_ptr<GenerateEmbeddMapUnits> &generateEmbeddMapUnits) :
    _generateEmbeddMapUnits(generateEmbeddMapUnits)
{}

Individual BlockCrossover::execute(const Individual& parentA, const Individual& parentB, std::mt19937& random) {
    EmbeddPartialGraph embeddPartialGraph;
    FillEmptyPortRandomly fillEmptyPort;
    vector<EmbeddMap> embeddMapUnits = _generateEmbeddMapUnits->execute(parentA.numRow(), parentA.numColumn(), random);
    EmbeddMap embeddMap(parentA.numRow(), parentA.numColumn());

    for(EmbeddMap map: embeddMapUnits) {
        if(random() % 2 == 0) embeddMap = embeddMap.overlay(map);
    }

    Individual child = parentA;
    child = embeddPartialGraph(parentA, parentB, embeddMap, random);
    fillEmptyPort(child, random);
    return child;
}
