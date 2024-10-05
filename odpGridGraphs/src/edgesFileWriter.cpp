#include "edgesFileWriter.hpp"

#include "gridGraph.hpp"
#include "grid.hpp"
#include <string>
#include <fstream> 
using std::string;
using namespace Cselab23Kimura::OdpGridGraphs;

/// @brief Individualオブジェクトから.edgesファイルを生成
void EdgesFileWriter::write(const GridGraph& indiv, const string& filepath) {
    std::ofstream ofs(filepath);
    Grid grid(indiv);

    for(int node1 = 0; node1 < indiv.numNode(); ++node1) {
        for(int d = 0; d < indiv.degree(); ++d) {
            int node2 = indiv.adjacent[node1][d];

            if(node2 == -1)    continue;
            if(node2 <= node1) continue;

            int column1 = grid.getColumn(node1);
            int row1    = grid.getRow(node1);
            int column2 = grid.getColumn(node2);
            int row2    = grid.getRow(node2);

            ofs << column1 << "," << row1 << " " << column2 << "," << row2 << std::endl;
        }
    }
}
