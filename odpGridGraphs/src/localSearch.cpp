#include "localSearch.hpp"

#include <vector>
#include "gridGraph.hpp"
#include "grid.hpp"
#include "twoChange.hpp"
#include "partialEvaluate.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using std::vector;

LocalSearch::LocalSearch() {
    this->_numEvaluate = 0;
}

/// @brief 局所最適化(網羅的2-changeを改善しなくなるまで繰り返す)
void LocalSearch::localOptimize(GridGraph& indiv) {
    indiv.evaluate();
    while(true) {
        bool refine = exhaustiveTwoChange(indiv);
        if(!refine) break;
    }
}

/// @brief 網羅的2-changeを1度だけ行う.
/// @param targetNodes インデックスが頂点の一次元表記に対応する配列. trueに対応する頂点について最適化
/// @return 改善があった場合はtrueを返す
bool LocalSearch::exhaustiveTwoChange(GridGraph& indiv) {
    TwoChange twoChange;
    Grid grid(indiv);
    bool refine = false;

    for(int nodeA0 = 0; nodeA0 < indiv.numNode(); ++nodeA0) {
        for(int dA = 0; dA < indiv.nodeDegrees[nodeA0]; ++dA) {
            int nodeA1 = indiv.adjacent[nodeA0][dA];

            vector<int> nearNodesA0 = grid.selectNearNode(nodeA0);
            for(int i = 0; i < nearNodesA0.size(); ++i) {
                int nodeB0 = nearNodesA0[i];
                bool exchanged = false;

                for(int dB = 0; dB < indiv.nodeDegrees[nodeB0]; ++dB) {
                    int nodeB1 = indiv.adjacent[nodeB0][dB];
                    
                    if(nodeA0 == nodeB0 && nodeA1 == nodeB1) continue;
                    if(nodeA0 == nodeB1 && nodeA1 == nodeB0) continue;
                    if(!grid.closeEnough(nodeA1, nodeB1))    continue;

                    GridGraph newIndiv = indiv;
                    twoChange(newIndiv, nodeA0, nodeA1, nodeB0, nodeB1);

                    newIndiv.evaluate();
                    _numEvaluate++;

                    if(newIndiv.betterThan(indiv)) {
                        //TODO: LS改善回数の記録
                        //MetaObserver::incrementNumRefineInLS();
                        indiv = std::move(newIndiv);
                        refine = true;
                        exchanged = true;
                        break;
                    }
                }
                if(exchanged) break;
            }
        }
    }

    return refine;
}

/// @brief 部分局所最適化(指定した頂点のみについて網羅的2-changeによる改善)
/// @param targetNodes 配列のインデックスが頂点の一次元表記に対応する. trueに対応する頂点について最適化
void LocalSearch::partialGraphOptimize(GridGraph& indiv, const vector<bool>& targetNodes) {
    while(true) {
        bool refine = partialExhaustiveTwoChange(indiv, targetNodes);
        if(!refine) break;
    }
}

/// @brief 網羅的2-changeを1度だけ行う.
/// @param targetNodes インデックスが頂点の一次元表記に対応する配列. trueに対応する頂点について最適化
/// @return 改善があった場合はtrueを返す
bool LocalSearch::partialExhaustiveTwoChange(GridGraph& indiv, const vector<bool>& targetNodes) {
    TwoChange twoChange;
    PartialEvaluateBFS adjAspl;
    Grid grid(indiv);
    bool refine = false;

    PartialFitness partialFitness = adjAspl(indiv, targetNodes);

    for(int nodeA0 = 0; nodeA0 < indiv.numNode(); ++nodeA0) {
        if(!targetNodes[nodeA0]) continue;

        for(int dA = 0; dA < indiv.nodeDegrees[nodeA0]; ++dA) {
            int nodeA1 = indiv.adjacent[nodeA0][dA];

            vector<int> nearNodesA0 = grid.selectNearNode(nodeA0);
            for(int i = 0; i < nearNodesA0.size(); ++i) {
                int nodeB0 = nearNodesA0[i];
                bool exchanged = false;

                for(int dB = 0; dB < indiv.nodeDegrees[nodeB0]; ++dB) {
                    int nodeB1 = indiv.adjacent[nodeB0][dB];
                    
                    if(nodeA0 == nodeB0 && nodeA1 == nodeB1) continue;
                    if(nodeA0 == nodeB1 && nodeA1 == nodeB0) continue;
                    if(!grid.closeEnough(nodeA1, nodeB1))    continue;

                    GridGraph newIndiv = indiv;
                    twoChange(newIndiv, nodeA0, nodeA1, nodeB0, nodeB1);

                    PartialFitness newPartialFitness = adjAspl(newIndiv, targetNodes);
                    _numEvaluate++;

                    if(newPartialFitness.betterThan(partialFitness)) {
                        indiv = std::move(newIndiv);
                        refine = true;
                        exchanged = true;
                        break;
                    }
                }
                if(exchanged) break;
            }
        }
    }

    return refine;
}
