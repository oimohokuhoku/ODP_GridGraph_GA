#pragma once
#include <climits>
#include <cfloat>
#include "grid.hpp"

namespace Cselab23Kimura::OdpGridGraphs
{
	class Grid;
	constexpr int INF_DIAMETER = INT_MAX;
	constexpr double INF_ASPL = DBL_MAX;

	class GridGraph {
	public:
		int **adjacent;	  ///@brief int[頂点数][次数] : "_adjacent[i][d]==k" なら頂点iと頂点kが隣接する
		int *nodeDegrees; ///@brief int[頂点数]       : "_nodeDegrees[i]==d" なら頂点iの次数はd

		GridGraph(int numRow, int numColumn, int degree, int maxLength);
		GridGraph(const Grid& grid);
		GridGraph(const GridGraph &obj);
		GridGraph(GridGraph &&obj);
		~GridGraph();

		GridGraph &operator=(const GridGraph &obj);
		GridGraph &operator=(GridGraph &&obj);

		void clear();
		void addEdge(int node1, int node2);
		void removeEdge(int node1, int node2);
		bool betterThan(const GridGraph &graph) const;
		bool worseThan(const GridGraph &graph) const;
		bool haveEdge(int node1, int node2) const;
		bool fullDegree(int node) const;
		bool matchGraph(const GridGraph &graph) const;

		void tryAddEdge(int node1, int node2, bool allowMultipleEdge = false, bool allowLoopEdge = false);
		void tryRemoveEdge(int node1, int node2);
		void showGraph() const;

		inline Grid grid()     const { return _grid; }
		inline int numRow()    const { return _grid.numRow; }
		inline int numColumn() const { return _grid.numColumn; }
		inline int degree()    const { return _grid.degree; }
		inline int maxLength() const { return _grid.maxLength; }
		inline int numNode()   const { return _grid.numNode; }
		int diameter() const;
		double aspl() const;

	private:
		const Grid _grid;
		mutable int _diameter;
		mutable double _aspl;
		mutable bool _evaluated;

		void evaluate() const;
		int findDegreeIndex(int node1, int node2) const;
		void findDegreeIndexForLoopEdge(int node, int *degree1, int *degree2) const;
	};
}
