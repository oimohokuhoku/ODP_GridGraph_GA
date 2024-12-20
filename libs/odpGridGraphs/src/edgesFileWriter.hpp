#pragma once

#include <string>

namespace Cselab23Kimura::OdpGridGraphs
{
    class GridGraph;

    class EdgesFileWriter {
    public:
        static void write(const GridGraph &graph, const std::string &filepath);
    private:
        EdgesFileWriter() = delete;
    };
}