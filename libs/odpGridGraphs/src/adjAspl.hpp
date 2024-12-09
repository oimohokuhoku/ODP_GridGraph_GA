#pragma once
#include <cstdint>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    /// @brief ADJ-ASPLによる評価計算(参考 : http://research.nii.ac.jp/graphgolf/2019/candar19/graphgolf2019-nakao.pdf)
    class AdjAspl {
    public:
        AdjAspl() = default;
        void operator()(GridGraph &indiv);
        inline int diameter() const { return _diameter; }
        inline double aspl()  const { return _aspl; }
        inline int dislinkedNode() { return _dislinkedNode; }

    private:
        const int _BIT_LENGTH = 64;
        int _diameter;
        double _aspl;
        int _dislinkedNode = -1;

        int64_t **newIdentityMatrix(int numNode, int numSegment);
        int findDislinkedNode(int64_t **matrix, int numSegment);
    };
}