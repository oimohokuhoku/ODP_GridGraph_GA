#include "edgesFileWriter.hpp"

#include "gridGraph.hpp"
#include "grid.hpp"
#include <string>
#include <fstream> 
using std::string;
using namespace Cselab23Kimura::OdpGridGraphs;

/// @brief Individualオブジェクトから.edgesファイルを生成
void EdgesFileWriter::write(const GridGraph& graph, const string& filepath) {
    std::ofstream ofs(filepath);
    Grid grid = graph.grid();

    for(int node1 = 0; node1 < graph.numNode(); ++node1) {
        for(int d = 0; d < graph.degree(); ++d) {
            int node2 = graph.adjacent[node1][d];

            if(node2 == -1)    continue;
            if(node2 <= node1) continue;

            int column1 = grid.getColumnIndex(node1);
            int row1    = grid.getRowIndex(node1);
            int column2 = grid.getColumnIndex(node2);
            int row2    = grid.getRowIndex(node2);

            ofs << column1 << "," << row1 << " " << column2 << "," << row2 << std::endl;
        }
    }
}
