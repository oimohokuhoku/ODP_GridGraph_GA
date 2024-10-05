#include "generateFlexibleBlockEmbeddMap.hpp"
#include <algorithm>
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::vector;

GenerateFlexibleBlockEmbeddMapUnits::GenerateFlexibleBlockEmbeddMapUnits() :
    _minUnitWidth(3),
    _minUnitHeight(3)
{}

vector<EmbeddMap> GenerateFlexibleBlockEmbeddMapUnits::execute(int numGraphRow, int numGraphColumn, std::mt19937& random) {
    int numGraphNode = numGraphRow * numGraphColumn;
    vector<EmbeddMap> embeddMapUnits; 
    vector<int> searchingNode(numGraphNode);
    EmbeddMap covered(numGraphNode, false);
    embeddMapUnits.reserve(numGraphNode);

    for(int i = 0; i < numGraphNode; ++i) searchingNode[i] = i;
    std::shuffle(searchingNode.begin(), searchingNode.end(), random);
    
    for(int startNode: searchingNode) {
        if(covered[startNode]) continue;

        
    }

    return embeddMapUnits;
}

EmbeddMap GenerateFlexibleBlockEmbeddMapUnits::generateEmbeddMapUnits(int startNode, std::mt19937& random) {

}