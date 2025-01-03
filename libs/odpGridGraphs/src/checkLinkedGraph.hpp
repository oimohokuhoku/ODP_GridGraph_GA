#pragma once

namespace Cselab23Kimura::OdpGridGraphs
{
    class GridGraph;

    class CheckLinkedGraph {
    public:
        CheckLinkedGraph() = default;
        bool checkLinked(const GridGraph &graph);
        inline int dislinkedNode() const noexcept { return _disLinkedNode; };

    private:
        int _disLinkedNode = -1;

        CheckLinkedGraph(CheckLinkedGraph &obj) = delete;
        CheckLinkedGraph(CheckLinkedGraph &&obj) = delete;
        void operator=(CheckLinkedGraph &obj) = delete;
        void operator=(CheckLinkedGraph &&obj) = delete;
    };
}