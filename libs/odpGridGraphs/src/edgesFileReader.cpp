#include "edgesFileReader.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "gridGraph.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using std::string;
using std::vector;

/// @brief .edgeファイルを読み込んでIndividualオブジェクトを作成
GridGraph EdgesFileReader::read(const string& filepath) {
    vector<vector<int>> edges = readEdges(filepath);
    int numRow    = calcNumRow(edges);
    int numColumn = calcNumColumn(edges);
    int degree    = calcDegree(edges, numColumn, numRow);
    int length    = calcMaxLength(edges);

    GridGraph indiv(numRow, numColumn, degree, length);
    indiv.clear();

    for(int i = 0; i < edges.size(); ++i) {
        int columnA = edges[i][0];
        int rowA    = edges[i][1];
        int columnB = edges[i][2];
        int rowB    = edges[i][3];

        int nodeA = (rowA * numColumn) + columnA;
        int nodeB = (rowB * numColumn) + columnB;

        if(nodeA == nodeB) continue;
        if(indiv.haveEdge(nodeA, nodeB)) continue;

        indiv.addEdge(nodeA, nodeB);
    }

    indiv.evaluate();
    return indiv;
}

int EdgesFileReader::countLine(std::ifstream& ifs) {
    int numLine = 0;
    string dummy;
    while(getline(ifs, dummy)) numLine++;

    ifs.clear();
    ifs.seekg(0);

    return numLine;
}

vector<vector<int>> EdgesFileReader::readEdges(const string& filepath) {
    std::ifstream ifs(filepath);
    if(ifs.fail()) {
        std::cerr << "file \"" << filepath << "\" can't be opened" << std::endl;
        exit(EXIT_FAILURE);
    }

    int numLine = countLine(ifs);
    vector<vector<int>> edges(numLine, vector<int>(4));

    for(int i = 0; i < numLine; ++i) {
        int columnA, rowA, columnB, rowB;
        string line;

        getline(ifs, line);
        sscanf(line.data(), "%d,%d %d,%d", &columnA, &rowA, &columnB, &rowB);

        edges[i][0] = columnA;
        edges[i][1] = rowA;
        edges[i][2] = columnB;
        edges[i][3] = rowB;
    }

    return edges;
}

int EdgesFileReader::calcNumColumn(const vector<vector<int>>& edges) {
    int maxColumn = 0;
    for(int i = 0; i < edges.size(); ++i) {
        if(maxColumn < edges[i][0]) maxColumn = edges[i][0];
        if(maxColumn < edges[i][2]) maxColumn = edges[i][2];
    }
    return maxColumn + 1;
}

int EdgesFileReader::calcNumRow(const vector<vector<int>>& edges) {
    int maxRow = 0;
    for(int i = 0; i < edges.size(); ++i) {
        if(maxRow < edges[i][1]) maxRow = edges[i][1];
        if(maxRow < edges[i][3]) maxRow = edges[i][3];
    }
    return maxRow + 1;
}

int EdgesFileReader::calcDegree(const vector<vector<int>>& edges, int numRow, int numColumn) {
    vector<vector<int>> degree(numRow, vector<int>(numColumn, 0));
    for(int i = 0; i < edges.size(); ++i) {
        int columnA = edges[i][0];
        int rowA    = edges[i][1];
        int columnB = edges[i][2];
        int rowB    = edges[i][3];
        degree[columnA][rowA]++;
        degree[columnB][rowB]++;
    }

    int maxDegree = 0;
    for(int h = 0; h < numRow; ++h) {
        for(int w = 0; w < numColumn; ++w) {
            if(maxDegree < degree[h][w]) maxDegree = degree[h][w];
        }
    }

    return maxDegree;
}

int EdgesFileReader::calcMaxLength(const vector<vector<int>>& edges) {
    int maxLength = 0;
    for(int i = 0; i < edges.size(); ++i) {
        int columnA = edges[i][0];
        int rowA    = edges[i][1];
        int columnB = edges[i][2];
        int rowB    = edges[i][3];
        int dColumn = std::abs(columnA - columnB);
        int dRow    = std::abs(rowA - rowB);

        int length = dColumn + dRow;
        if(maxLength < length) maxLength = length;
    }
    return maxLength;
}
