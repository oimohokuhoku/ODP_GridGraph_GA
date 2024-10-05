#pragma once

#include<string>
#include<vector>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    class EdgesFileReader {
    public:
        static GridGraph read(const std::string &filepath);

    private:
        static std::vector<std::vector<int>> readEdges(const std::string &filepath);
        static int countLine(std::ifstream &ifs);
        static int calcNumColumn(const std::vector<std::vector<int>> &edges);
        static int calcNumRow(const std::vector<std::vector<int>> &edges);
        static int calcDegree(const std::vector<std::vector<int>> &edges, int numRow, int numColumn);
        static int calcMaxLength(const std::vector<std::vector<int>> &edges);

        EdgesFileReader() = delete;
    };
}