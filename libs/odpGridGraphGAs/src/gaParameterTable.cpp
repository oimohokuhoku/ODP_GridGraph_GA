#include "gaParameterTable.hpp"
#include <iostream>
#include <iomanip>
#include "group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::cout;
using std::endl;
using std::setw;

GaParameterTable::GaParameterTable() {
    _stepWidth = 5;
    _diamWidth = 10;
    _asplDigit = 16;
    _asplWidth = 18;
    _variationWidth = 10;
    _numEvaluateWidth = 9;
    _blendRateWidth = 11;
    _defaultDoubleDigit = 5;
}

void GaParameterTable::showHedder() const {
    cout << std::left;

    cout << setw(_stepWidth) << "Step" << "| ";
    cout << setw(_diamWidth) << "Best_diam" << "| ";
    cout << setw(_asplWidth) << "Best_ASPL"    << "| ";
    cout << setw(_asplWidth) << "Average_ASPL" << "| ";
    cout << setw(_asplWidth) << "Worst_ASPL"   << "| ";
    cout << setw(_variationWidth) << "variation"  << "| ";
    cout << endl;

    cout << std::right;
}

void GaParameterTable::showRow(int generation, const Group &group) const {
    cout << std::left;

    cout << setw(_stepWidth) << generation           << "| ";
    cout << setw(_diamWidth) << group.bestDiameter() << "| ";

    cout << std::setprecision(_asplDigit);
    cout << setw(_asplWidth) << group.bestAspl()    << "| ";
    cout << setw(_asplWidth) << group.averageAspl() << "| ";
    cout << setw(_asplWidth) << group.worstAspl()   << "| ";

    cout << std::setprecision(_defaultDoubleDigit);
    cout << setw(_variationWidth) << group.indivVariation() << "| ";
    cout << endl;

    cout << std::defaultfloat;
    cout << std::right;
}