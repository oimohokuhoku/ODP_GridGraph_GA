#pragma once

#include<vector>

namespace Cselab23Kimura::OdpGridGraphs
{
    class GridGraph;

    struct PartialFitness {
        int diameter;
        double aspl;

        bool betterThan(const PartialFitness &fitnesss)
        {
            if (this->diameter < fitnesss.diameter)
                return true;
            if (this->diameter > fitnesss.diameter)
                return false;
            if (this->aspl < fitnesss.aspl)
                return true;
            if (this->aspl > fitnesss.aspl)
                return false;
            return false;
        }
    };

    class IPartialEvaluate {
    public:
        virtual ~IPartialEvaluate() = default;
        virtual PartialFitness operator()(const GridGraph &graph, const std::vector<bool> &targetNodeMap) = 0;
    };

    class PartialEvaluateBFS : public IPartialEvaluate {
    public:
        ~PartialEvaluateBFS() = default;
        PartialFitness operator()(const GridGraph &graph, const std::vector<bool> &targetNodeMap) override;

    private:
        void computePathLength(const GridGraph &graph, const std::vector<bool> &targetNodeMap, int numTargetNode, int startNode, int *diameterStorage, int *pathLengthStorage);
        int countTargetNode(const std::vector<bool> &targetNodeMap);
    };
}