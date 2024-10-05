#pragma once

#include <string>
#include "initialize.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class Group;

    class NeighborInitialize: public Initialize {
    public:
        NeighborInitialize(const std::string& startEdgesFilepath, int numMutate);
        ~NeighborInitialize() = default;
        Group genearteInitialGroup(int population, std::mt19937& random) override;
        inline int averageNumDiffEdge() const { return _averageNumDiffEdge; }

    private:
        const std::string _startEdgesFilepath;
        const int _numMutate;
        int _averageNumDiffEdge = 0;
    };
}