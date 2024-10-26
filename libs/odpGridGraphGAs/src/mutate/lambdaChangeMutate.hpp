#pragma once

#include "mutate.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA::Mutates {
    class LambdaChangeMutate: public Mutate {
    public:
        LambdaChangeMutate(double indivMutateProbability, double geneMutateProbability);
        ~LambdaChangeMutate() = default;
        void execute(Individual& indiv, std::mt19937& random);

    private:
        const double _indivMutateProbability;
        const double _geneMutateProbability;
    };
}