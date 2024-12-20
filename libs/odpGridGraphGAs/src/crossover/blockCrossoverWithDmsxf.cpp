#include "blockCrossoverWithDmsxf.hpp"

#include <algorithm>
#include <iostream>
#include "embeddMap.hpp"
#include "embeddPartialGraph.hpp"
#include "./generateEmbeddMap.hpp"
#include "odpGridGraphs.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers;
using std::vector;
using std::unique_ptr;

BlockCrossoverWithDMSXf::BlockCrossoverWithDMSXf(GenerateEmbeddMapUnits* generateEmbeddMapUnits, double saveParentProbability) :
    _generateEmbeddMapUnits(generateEmbeddMapUnits),
    _saveParentProbability(saveParentProbability)
{}

/// @brief DMSXf形式でのブロック交叉
/// @return 生成された子個体
GridGraph BlockCrossoverWithDMSXf::execute(const GridGraph& parentA, const GridGraph& parentB, std::mt19937& random) {
    //For _blendRate calculation
    GridGraph const *startParent, *endParent;
    if(parentA.betterThan(parentB)) {
        startParent = &parentA;
        endParent   = &parentB;
    }
    else{
        startParent = &parentB;
        endParent   = &parentA;
    }

    EmbeddPartialGraph embeddPartialGraph;
    vector<EmbeddMap> embeddMapUnits = _generateEmbeddMapUnits->execute(parentA.numRow(), parentB.numColumn(), random);
    vector<bool> appliedUnit(embeddMapUnits.size(), false);
    EmbeddMap currentEmbeddMap(startParent->numRow(), startParent->numColumn());

    GridGraph bestIndiv(parentA.grid());
    GridGraph currentIndiv(parentA.grid());

    for(size_t step = 0; step < embeddMapUnits.size() - 1; ++step) {
        GridGraph bestNextIndiv(parentA.grid());
        int bestUnit = -1;

        for(int unitIndex = 0; unitIndex < embeddMapUnits.size(); ++unitIndex) {
            if(appliedUnit[unitIndex]) continue;

            EmbeddMap nextEmbeddMap = currentEmbeddMap.overlay(embeddMapUnits[unitIndex]);
            GridGraph nextIndiv    = embeddPartialGraph(*startParent, *endParent, nextEmbeddMap, random);
            
            if(unitIndex == 0 || nextIndiv.betterThan(bestNextIndiv)) {
                bestNextIndiv = std::move(nextIndiv);
                bestUnit = unitIndex;
            }
        }
        
        currentIndiv = std::move(bestNextIndiv);
        currentEmbeddMap = currentEmbeddMap.overlay(embeddMapUnits[bestUnit]);
        appliedUnit[bestUnit] = true;

        if(currentIndiv.betterThan(bestIndiv)) {
            bestIndiv = currentIndiv;
        }
    }

    if(startParent->betterThan(bestIndiv)) {
        long maxRand = static_cast<long>(random.max()) + 1;
        if(random() < _saveParentProbability * maxRand) {
            bestIndiv = *startParent;
        }
    }

    return bestIndiv;
}

double BlockCrossoverWithDMSXf::calcBlendRatio(const EmbeddMap& bestMap) {
    int numNodeA = 0;
    for(int i = 0; i < bestMap.numNode(); ++i) numNodeA += bestMap.at(i);
    return (double)numNodeA / bestMap.numNode();
}
