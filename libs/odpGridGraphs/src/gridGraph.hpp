#pragma once
#include <climits>
#include <cfloat>
#include "grid.hpp"

namespace Cselab23Kimura::OdpGridGraphs
{
	class Grid;

	class GridGraph {
	public:
		/// @brief Diameter of dislinked graph.
		constexpr static int INF_DIAMETER = INT_MAX;
		/// @brief ASPL of dislinked graph.
		constexpr static double INF_ASPL = DBL_MAX;
		constexpr static int EMPTY_PORT = -1;

		GridGraph(int numRow, int numColumn, int degree, int maxLength);
		GridGraph(const Grid& grid);
		GridGraph(const GridGraph &rhs);
		GridGraph(GridGraph &&rhs);
		~GridGraph();

		GridGraph &operator=(const GridGraph &rhs);
		GridGraph &operator=(GridGraph &&rhs);

		void clearEdges();
		void addEdge(int nodeA, int nodeB);
		void removeEdge(int nodeA, int nodeB);
		void addEdgeAllowingLoops(int node1, int node2);
		void removeEdgeAllowingLoops(int node1, int node2);
		bool betterThan(const GridGraph &graph) const;
		bool worseThan(const GridGraph &graph) const;
		bool haveEdge(int nodeA, int nodeB) const;
		bool fullDegree(int node) const;
		bool matchGraph(const GridGraph &graph) const;
		void showGraph() const;

		int computeDiameter() const;
		double computeAspl() const;

		inline Grid grid()     const noexcept { return _grid; }
		inline int numRow()    const noexcept { return _grid.numRow; }
		inline int numColumn() const noexcept { return _grid.numColumn; }
		inline int degree()    const noexcept { return _grid.degree; }
		inline int maxLength() const noexcept { return _grid.maxLength; }
		inline int numNode()   const noexcept { return _grid.numNode; }
		inline int adjacent(int nodeIndex, int portIndex) const { return _adjacent[nodeIndex][portIndex]; }
		inline int nodeDegree(int index) const { return _nodeDegrees[index]; }
		inline bool isValidObject() const noexcept{ return (_adjacent != nullptr) && (_nodeDegrees != nullptr); }
		
	private:
		const Grid _grid;
		int **_adjacent;	  // int[numNode][degree] : "_adjacent[i][d]==k" represent that i-th node connect k-th node.
		int *_nodeDegrees;    // int[numNode]         : "_nodeDegrees[i]==d" represent that degree of i-th node is d.
		mutable int _diameterCache;
		mutable double _asplCache;
		mutable bool _evaluated;

		void evaluate() const;
		void newPointerArrays();
		void deletePointerArrays();
		void addToAdajcentList(int srcNode, int distNode);
		void removeFromAdjacentList(int srcNode, int distNode);
		int findPortIndex(int srcNode, int distNode) const;
		void removeLoopEdgeFromAdajcentList(int node);
		void findPortIndexForLoopEdge(int node, int *degree1, int *degree2) const;
	};
}
