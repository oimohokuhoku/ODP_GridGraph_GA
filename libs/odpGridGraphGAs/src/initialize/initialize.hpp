#pragma once
#include <random>

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class Group;

    class Initialize {
    public:
        virtual ~Initialize() = default;
        virtual Group genearteInitialGroup(int population, std::mt19937& random) = 0;
    };
}