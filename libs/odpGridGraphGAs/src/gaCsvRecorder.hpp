#pragma once
#include <string>
#include <fstream>

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class Group;

    class GaCsvRecorder {
    public:
        GaCsvRecorder(const std::string& filepath);
        void record(int generation, const Group& group);
    private: 
        std::ofstream _ofs;
    };
}