#include "generateOrthogonalBlockEmbeddMap.hpp"
#include <algorithm>

using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::vector;

vector<EmbeddMap> GenerateOrthogonalBlockEmbeddMapUnits::execute(int numGraphRow, int numGraphColumn, std::mt19937& random) {
    vector<int> divisionRows    = decideDevidePositions(numGraphRow,    random);
    vector<int> divisionColumns = decideDevidePositions(numGraphColumn, random);

    int numGraphNode  = numGraphRow * numGraphColumn;
    int numUnitRow    = divisionRows.size()    - 1;
    int numUnitColumn = divisionColumns.size() - 1;
    int numUnit       = numUnitRow * numUnitColumn;
    vector<EmbeddMap> embeddMapUnits(numUnit);

    for(int unit = 0; unit < numUnit; ++unit) {
        EmbeddMap map(numGraphNode, 0);

        int unitRow    = unit / numUnitColumn;
        int unitColumn = unit % numUnitColumn;
        int top    = divisionRows[unitRow];
        int bottom = divisionRows[unitRow + 1];
        int left   = divisionColumns[unitColumn];
        int right  = divisionColumns[unitColumn + 1];

        for(int r = top; r < bottom; ++r) {
            for(int c = left; c < right; ++c) {
                int n = (r * numGraphColumn) + c;
                map[n] = true;
            }
        }

        embeddMapUnits[unit] = std::move(map);
    }

    return embeddMapUnits;
}

/// @brief 分割位置の決定. (分割位置が1なら)
/// @param width 分割方向の列数or行数
/// @return 両端(0, width-1)を含む分割する行番号を保持する配列
vector<int> GenerateOrthogonalBlockEmbeddMapUnits::decideDevidePositions(int width, std::mt19937& random) {
    //FIXME リファクタリング必須
    //この関数汚ねぇ
    int maxNumDivision = (width / 5) + 1;   //widthが5増えるごとに1分割ふえる
    int numDivision = (random() % maxNumDivision) + 1;

    vector<int> rows(width - 2);
    for(int i = 0; i < rows.size(); ++i) rows[i] = i + 1; //1~(width-2)まで順番に
    std::shuffle(rows.begin(), rows.end(), random);

    vector<int> division(numDivision + 2);
    division[0] = 0;
    division[division.size() - 1] = width;
    for(int i = 1; i < division.size() - 1; ++i)
        division[i] = rows[i - 1];

    return division;
}