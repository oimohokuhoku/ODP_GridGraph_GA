#pragma once

namespace Cselab23Kimura::OdpGridGraphs::GA
{
    class Group;

    class GaParameterTable {
    public:
        GaParameterTable();
        void showHedder() const;
        void showRow(int generation, const Group &group) const;

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