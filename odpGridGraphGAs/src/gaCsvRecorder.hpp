#pragma once

#include <string>
#include <fstream>

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class GeneticAlgorithm;

    class GaCsvRecorder {
    public:
        GaCsvRecorder(const std::string& filepath);
        void record(const GeneticAlgorithm& ga);

    private: 
        std::ofstream _ofs;
    };
}