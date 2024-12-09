#pragma once
#include <climits>
#include <cfloat>

namespace Cselab23Kimura::OdpGridGraphs
{
	constexpr int INF_DIAMETER = INT_MAX;
	constexpr double INF_ASPL = DBL_MAX;

	class GridGraph
	{
	public:
		int **adjacent;	  ///@brief int[頂点数][次数] : "_adjacent[i][d]==k" なら頂点iと頂点kが隣接する
		int *nodeDegrees; ///@brief int[頂点数]       : "_nodeDegrees[i]==d" なら頂点iの次数はd

		GridGraph();
		GridGraph(int numRow, int numColumn, int degree, int maxLength);
		GridGraph(const GridGraph &obj);
		GridGraph(GridGraph &&obj);
		~GridGraph();

		GridGraph &operator=(const GridGraph &obj);
		GridGraph &operator=(GridGraph &&obj);

		void clear();
		void evaluate();
		void addEdge(int node1, int node2);
		void removeEdge(int node1, int node2);
		bool betterThan(const GridGraph &indiv) const;
		bool worseThan(const GridGraph &indiv) const;
		bool haveEdge(int node1, int node2) const;
		bool fullDegree(int node) const;
		bool matchGraph(const GridGraph &indiv) const;

		void tryAddEdge(int node1, int node2, bool allowMultipleEdge = false, bool allowLoopEdge = false);
		void tryRemoveEdge(int node1, int node2);
		void showGraph() const;

		inline int numRow()    const { return _numRow; }
		inline int numColumn() const { return _numColumn; }
		inline int degree()    const { return _degree; }
		inline int maxLength() const { return _maxLength; }
		inline int numNode()   const { return _numNode; }
		inline int diameter()  const { return _diameter; }
		inline double aspl()   const { return _aspl; }

		static void setDefaultGraphCondition(int numRow, int numColumn, int degree, int maxLength);

	private:
		const int _numRow;
		const int _numColumn;
		const int _degree;
		const int _maxLength;
		const int _numNode;
		int _diameter;
		double _aspl;

		static int s_defaultNumRow;
		static int s_defaultNumColumn;
		static int s_defaultDegree;
		static int s_defaultMaxLength;

		int findDegreeIndex(int node1, int node2) const;
		void findDegreeIndexForLoopEdge(int node, int *degree1, int *degree2) const;
	};
}
