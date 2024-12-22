#include "gaCsvRecorder.hpp"
#include "group.hpp"
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

void GaCsvRecorder::record(int generation, const Group& group) {
    _ofs << generation << ",";
    _ofs << group.bestDiameter()   << ",";
    _ofs << group.bestAspl()       << ",";
    _ofs << group.averageAspl()    << ",";
    _ofs << group.worstAspl()      << ",";
    _ofs << group.indivVariation() << ",";
    _ofs << endl;
}