#include "blockCrossover.hpp"
#include <vector>
#include "odpGridGraphs/include/gridGraphs.hpp"
#include "embeddPartialGraph.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs;

using std::unique_ptr;
using std::vector;

BlockCrossover::BlockCrossover(unique_ptr<GenerateEmbeddMapUnits> &generateEmbeddMapUnits) :
    _generateEmbeddMapUnits(generateEmbeddMapUnits)
{}

Individual BlockCrossover::execute(const Individual& parentA, const Individual& parentB, std::mt19937& random) {
    EmbeddPartialGraph embeddPartialGraph;
    FillEmptyPortRandomly fillEmptyPort;
    vector<EmbeddMap> embeddMapUnits = _generateEmbeddMapUnits->execute(parentA.numRow(), parentA.numColumn(), random);
    EmbeddMap embeddMap(parentA.numNode(), false);

    for(EmbeddMap map: embeddMapUnits) {
        if(random() % 2 == 0) overlayEmbeddMaps(embeddMap, map);
    }

    Individual child = parentA;
    child = embeddPartialGraph(parentA, parentB, embeddMap);
    fillEmptyPort(child, random);
    return child;
}

void BlockCrossover::overlayEmbeddMaps(EmbeddMap &baseMap, const EmbeddMap &overlayMap) {
    for(int i = 0; i < baseMap.size(); ++i) {
        baseMap[i] = baseMap[i] | overlayMap[i];
    }
}
