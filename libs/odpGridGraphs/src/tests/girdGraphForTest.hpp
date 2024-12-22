#pragma once
#include "../gridGraph.hpp"

namespace Cselab23Kimura::OdpGridGraphs::Tests
{
	class SimpleGraphGenerate {
	public:
		/// @brief row2_column2_degree3_length2_diameter2_aspl1.333333
		static GridGraph h2w2d3r2_A() {
            GridGraph graph(2, 2, 3, 2);
            graph.clearEdges();
            graph.addEdge(0, 1);
            graph.addEdge(1, 3);
            graph.addEdge(3, 2);
            graph.addEdge(2, 0);
            return graph;
        }
        
        /// @brief row2_column2_degree3_length2_diameter2_aspl1.166666
        static GridGraph h2w2d3r2_B() {
            GridGraph graph(2, 2, 3, 2);
            graph.clearEdges();
            graph.addEdge(0, 1);
            graph.addEdge(1, 3);
            graph.addEdge(3, 2);
            graph.addEdge(2, 0);
            graph.addEdge(0, 3);
            return graph;
        }

        /// @brief row2_column2_degree3_length2_diameter1_aspl1.0
        static GridGraph h2w2d3r2_C() {
            GridGraph graph(2, 2, 3, 2);
            graph.clearEdges();
            graph.addEdge(0, 1);
            graph.addEdge(1, 3);
            graph.addEdge(3, 2);
            graph.addEdge(2, 0);
            graph.addEdge(0, 3);
            graph.addEdge(1, 2);
            return graph;
        }
	};
}