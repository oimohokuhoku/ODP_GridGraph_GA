#pragma once

#include <random>
#include "initialize.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class RandomInitialize: public Initialize {
    public:
        ~RandomInitialize() = default;
        Group genearteInitialGroup(int population, std::mt19937& random) override;
    };
}