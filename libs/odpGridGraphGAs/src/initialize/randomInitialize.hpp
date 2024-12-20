#pragma once

#include <random>
#include "initialize.hpp"

namespace Cselab23Kimura::OdpGridGraphs{
    class Grid;

    namespace GA {
        class RandomInitialize: public Initialize {
        public:
            RandomInitialize(const Grid& grid);
            ~RandomInitialize() = default;
            Group genearteInitialGroup(int population, std::mt19937& random) override;
        private:
            const Grid& _grid;
        };
    }
}