#pragma once

#include <random>
#include "mutate.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA::Mutates
{
    class TwoChangeMutate : public Mutate{
    public:
        ~TwoChangeMutate() = default;
        TwoChangeMutate(double indivMutateProbability, double geneMutateProbability);
        void execute(Individual &indiv, std::mt19937& random) override;

    private:
        const double _indivMutateProbability;
        const double _geneMutateProbability;
    };
}
