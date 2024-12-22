#pragma once
#include <cstdint>

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    /// @brief Computer of diameter of ASPL.
    /// @note Refererence: 
    /// Masahiro Nakao, Maaki Sakai, Yoshiko Hanada,
    /// "Introduction of fast APSP algorithm and optimization algorithms for grid graphs",
    /// Graph Golf Workshop in CANDAR'19, 2019-11-26
    class AdjAspl {
    /* static */
    public:
        static AdjAspl computeDiameterAndAspl(int numNode, int const *const *const adjacent, int const *const nodeDegrees);
    private:
        constexpr static int _BIT_LENGTH = 64;
        static inline int64_t **newIdentityMatrix(int numNode, int numSegment);
        static inline int findDislinkedNode(int64_t **matrix, int numSegment);
        
    /* instance */
    public:
        inline int diameter() const noexcept { return _diameter; }
        inline double aspl()  const noexcept { return _aspl; }
        inline int dislinkedNode()  const noexcept { return _dislinkedNode; }
        inline bool isDislinked()   const noexcept { return _dislinkedNode != -1; }
        inline bool isLinkedGraph() const noexcept { return _dislinkedNode == -1; }
    private:
        const int _diameter;
        const double _aspl;
        const int _dislinkedNode = -1;
        AdjAspl(int diameter, double aspl, int dislinkedNode);
    };
}