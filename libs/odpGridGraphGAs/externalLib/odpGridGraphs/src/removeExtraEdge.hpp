#pragma once

namespace Cselab23Kimura::OdpGridGraphs {
    class GridGraph;

    /// @brief 多重辺とループ辺を取り除く関数オブジェクト
    class RemoveExtraEdge {
    public:
        RemoveExtraEdge() = default;
        void operator()(GridGraph &graph);

    private:
        void removeLoopEdge(GridGraph &graph);
        void removeMultipleEdge(GridGraph &graph);

        RemoveExtraEdge(RemoveExtraEdge &obj)  = delete;
        RemoveExtraEdge(RemoveExtraEdge &&obj) = delete;
        void operator=(RemoveExtraEdge &obj)   = delete;
        void operator=(RemoveExtraEdge &&obj)  = delete;
    };
}