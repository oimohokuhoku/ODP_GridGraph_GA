#pragma once

namespace Cselab23Kimura::OdpGridGraphs::GA
{
    class GeneticAlgorithm;

    class GAParameterTable {
    public:
        GAParameterTable();
        void showHedder() const;
        void showParameter(const GeneticAlgorithm &ga) const;

    private:
        int _stepWidth;
        int _diamWidth;
        int _asplWidth;
        int _variationWidth;
        int _numEvaluateWidth;
        int _blendRateWidth;
        int _numRefineInLSWidth;

        int _asplDigit;
        int _defaultDoubleDigit;
    };
}