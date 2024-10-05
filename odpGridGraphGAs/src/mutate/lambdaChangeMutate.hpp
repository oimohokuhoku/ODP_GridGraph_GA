#pragma once

#include "mutate.hpp"

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class LambdaChangeMutate: public Mutate {
    public:
        LambdaChangeMutate(double indivMutateProbability, double geneMutateProbability);
        ~LambdaChangeMutate() = default;
        void execute(Individual& indiv);

    private:
        const double _indivMutateProbability;
        const double _geneMutateProbability;
    };
}