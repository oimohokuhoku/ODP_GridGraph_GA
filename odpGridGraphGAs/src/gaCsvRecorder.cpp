#include "gaCsvRecorder.hpp"
#include "geneticAlgorithm.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::endl;

GaCsvRecorder::GaCsvRecorder(const std::string& filepath): _ofs(std::ofstream(filepath)) {
    _ofs << "step,";
    _ofs << "bestDiam,";
    _ofs << "bestAspl,";
    _ofs << "averageAspl,";
    _ofs << "worstAspl,";
    _ofs << "variation" << endl;
}

void GaCsvRecorder::record(const GeneticAlgorithm& ga) {
    _ofs << ga.generation() << ",";
    _ofs << ga.bestDiameter() << ",";
    _ofs << ga.bestASPL() << ",";
    _ofs << ga.averageASPL() << ",";
    _ofs << ga.worstASPL() << ",";
    _ofs << ga.indivVariation() << ",";
    _ofs << ga.averageDistanceFromStartGraph() << endl;
}