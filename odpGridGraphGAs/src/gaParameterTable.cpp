#include "gaParameterTable.hpp"

#include <iostream>
#include <iomanip>
#include "geneticAlgorithm.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::cout;
using std::endl;
using std::setw;

GAParameterTable::GAParameterTable() {
    _stepWidth = 5;
    _diamWidth = 10;
    _asplDigit = 16;
    _asplWidth = 18;
    _variationWidth = 10;
    _numEvaluateWidth = 9;
    _blendRateWidth = 11;
    _defaultDoubleDigit = 5;
}

void GAParameterTable::showHedder() const {
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

void GAParameterTable::showParameter(const GeneticAlgorithm& ga) const {
    cout << std::left;

    cout << setw(_stepWidth) << ga.generation()   << "| ";
    cout << setw(_diamWidth) << ga.bestDiameter() << "| ";
    cout << std::setprecision(_asplDigit);
    cout << setw(_asplWidth) << ga.bestASPL()    << "| ";
    cout << setw(_asplWidth) << ga.averageASPL() << "| ";
    cout << setw(_asplWidth) << ga.worstASPL()   << "| ";
    cout << std::setprecision(_defaultDoubleDigit);
    cout << setw(_variationWidth)    << ga.indivVariation() << "| ";
    cout << ga.averageDistanceFromStartGraph() << "| ";
    cout << endl;

    cout << std::defaultfloat;
    cout << std::right;
}