#include "generateFlexibleBlockEmbeddMap.hpp"
#include <algorithm>
#include "embeddMap.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers;
using std::vector;

GenerateFlexibleBlockEmbeddMapUnits::GenerateFlexibleBlockEmbeddMapUnits(int maxUnitWidth, int minUnitWidth, int maxUnitHeight, int minUnitHeight) :
    _maxUnitWidth(maxUnitWidth),
    _minUnitWidth(minUnitWidth),
    _maxUnitHeight(maxUnitHeight),
    _minUnitHeight(minUnitHeight)
{}

vector<EmbeddMap> GenerateFlexibleBlockEmbeddMapUnits::execute(int numGraphRow, int numGraphColumn, std::mt19937& random) {
    int numGraphNode = numGraphRow * numGraphColumn;
    int numSearchingNode = (numGraphRow - _minUnitHeight) * (numGraphColumn - _minUnitWidth);
    vector<EmbeddMap> embeddMapUnits; 
    vector<int> searchingNode(numSearchingNode);
    EmbeddMap covered(numGraphRow, numGraphColumn);
    embeddMapUnits.reserve(numGraphNode);

    for(int i = 0; i < numGraphNode; ++i) searchingNode[i] = i;
    std::shuffle(searchingNode.begin(), searchingNode.end(), random);
    
    for(int startNode: searchingNode) {
        if(covered.at(startNode)) continue;

        
    }

    return embeddMapUnits;
}

EmbeddMap GenerateFlexibleBlockEmbeddMapUnits::generateEmbeddMapUnits(int startNode, std::mt19937& random) {
    
}