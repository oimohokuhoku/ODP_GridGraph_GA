#include "gridGraph.hpp"

#include <iostream>
#include <climits>
#include <utility>
#include "grid.hpp"
#include "adjAspl.hpp"
#include "checkLinkedGraph.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;

/// @brief GridGraph::setDefaultGraphCondition(int, int, int, int)によって設定された値をグラフの条件として初期化
GridGraph::GridGraph(): 
	GridGraph(s_defaultNumRow, s_defaultNumColumn, s_defaultDegree, s_defaultMaxLength) 
{}

/// @brief グラフの条件を指定して初期化
GridGraph::GridGraph(int numRow, int numColumn, int degree, int maxLength) :
	_numRow(numRow),
	_numColumn(numColumn),
	_degree(degree),
	_maxLength(maxLength),
	_numNode(numRow * numColumn)
{
	adjacent = new int*[_numNode];
	for(int i = 0; i < _numNode; ++i) adjacent[i] = new int[_degree];

	nodeDegrees = new int[_numNode];
	_diameter   = INF_DIAMETER;
	_aspl       = INF_ASPL;
}

GridGraph::GridGraph(const GridGraph& obj) :
	GridGraph(obj.numRow(), obj.numColumn(), obj.degree(), obj.maxLength())
{
	*this = obj;
}

GridGraph::GridGraph(GridGraph&& obj) :
	_numRow(obj._numRow),
	_numColumn(obj._numColumn),
	_degree(obj._degree),
	_maxLength(obj._maxLength),
	_numNode(obj._numNode)
{
	*this = std::move(obj);
}

GridGraph::~GridGraph() {
	if(adjacent != nullptr) {
		for(int i = 0; i < _numNode; ++i) delete[] adjacent[i];
		delete[] adjacent;
	}
	if(nodeDegrees != nullptr) {
		delete[] nodeDegrees;
	}
}

GridGraph& GridGraph::operator= (const GridGraph& obj) {
	for(int n = 0; n < _numNode; ++n) {
		for(int d = 0; d < _degree; ++d) {
			this->adjacent[n][d] = obj.adjacent[n][d];
		}
	}
	for(int n = 0; n < _numNode; ++n) {
		this->nodeDegrees[n] = obj.nodeDegrees[n];
	}
	this->_aspl     = obj._aspl;
	this->_diameter = obj._diameter;

	return *this;
}

GridGraph& GridGraph::operator= (GridGraph&& obj) {
	if(adjacent != nullptr) {
		for(int i = 0; i < _numNode; ++i) delete[] adjacent[i];
		delete[] adjacent;
	}
	if(nodeDegrees != nullptr) {
		delete[] nodeDegrees;
	}

	this->adjacent    = obj.adjacent;
	this->nodeDegrees = obj.nodeDegrees;
	this->_aspl       = obj._aspl;
	this->_diameter   = obj._diameter;

	obj.adjacent    = nullptr;
	obj.nodeDegrees = nullptr;

	return *this;
}

/// @brief すべての辺を削除する
void GridGraph::clear() {
	for(int n = 0; n < _numNode; ++n) {
		for(int d = 0; d < _degree; ++d) {
			this->adjacent[n][d] = -1;
		}
	}
	for(int n = 0; n < _numNode; ++n) {
		this->nodeDegrees[n] = 0;
	}
	this->_diameter = INF_DIAMETER;
	this->_aspl     = INF_ASPL;
}

void GridGraph::evaluate() {
	AdjAspl evaluate;
	evaluate(*this);
	this->_diameter = evaluate.diameter();
	this->_aspl     = evaluate.aspl();
}

/// @brief 辺を追加する. 高速だが, 安全に追加される保証はない
/// @param node1 追加辺の端頂点
/// @param node2 追加辺の端頂点
void GridGraph::addEdge(int node1, int node2) {
	this->adjacent[node1][nodeDegrees[node1]] = node2;
	nodeDegrees[node1]++;

	this->adjacent[node2][nodeDegrees[node2]] = node1;
	nodeDegrees[node2]++;
}

/// @brief 辺を削除する. 高速だが, 安全に削除される保証はない
/// @param node1 追加辺の端頂点
/// @param node2 追加辺の端頂点
void GridGraph::removeEdge(int node1, int node2) {
	int d1 = -1, d2 = -1;
	int tailDegree1 = -1, tailDegree2 = -1;

	if(node1 == node2) { //ループの削除
		findDegreeIndexForLoopEdge(node1, &d1, &d2);
		tailDegree1 = nodeDegrees[node1] - 1;
		tailDegree2 = nodeDegrees[node2] - 2;
	}
	else {
		d1 = findDegreeIndex(node1, node2);
		d2 = findDegreeIndex(node2, node1);
		tailDegree1 = nodeDegrees[node1] - 1;
		tailDegree2 = nodeDegrees[node2] - 1;
	}

	adjacent[node2][d2] = adjacent[node2][tailDegree2]; //ちょっと気持ち悪いけど
	adjacent[node1][d1] = adjacent[node1][tailDegree1]; //この2行を逆にするとバグります
	adjacent[node1][tailDegree1] = -1;
	adjacent[node2][tailDegree2] = -1;

	nodeDegrees[node1]--;
	nodeDegrees[node2]--;
}

/// @brief グラフの評価値を比較する
bool GridGraph::betterThan(const GridGraph& indiv) const {
	if(this->_diameter < indiv._diameter) return true;
	if(this->_diameter > indiv._diameter) return false;

	if(this->_aspl < indiv._aspl) return true;
	else						  return false;
}

/// @brief グラフの評価値を比較する
bool GridGraph::worseThan(const GridGraph& indiv) const {
	if(this->_diameter > indiv._diameter) return true;
	if(this->_diameter < indiv._diameter) return false;

	if(this->_aspl > indiv._aspl) return true;
	else						return false;
}

/// @brief 辺を持っているか判定
/// @param node1 追加辺の端頂点
/// @param node2 追加辺の端頂点
bool GridGraph::haveEdge(int node1, int node2) const {
	for(int d = 0; d < nodeDegrees[node1]; ++d) {
		if(adjacent[node1][d] == node2) return true;
	}
	return false;
}

/// @brief 頂点の次数が最大値かを判定
bool GridGraph::fullDegree(int node) const {
	return (this->nodeDegrees[node] == _degree);
}

/// @brief 同じトポロジーのグラフかを判定. 回転によって一致するグラフは異なるものとみなす.
bool GridGraph::matchGraph(const GridGraph& indiv) const {
	for(int node1 = 0; node1 < _numNode; ++node1) {
		for(int d1 = 0; d1 < this->nodeDegrees[node1]; ++d1) {
			int node2A = this->adjacent[node1][d1];
			if(node1 == node2A) continue;

			bool existMatchEdge = false;
			for(int d2 = 0; d2 < indiv.nodeDegrees[node1]; ++d2) {
				int node2B = indiv.adjacent[node1][d2];
				if(node2A == node2B) {
					existMatchEdge = true;
					break;
				}
			}

			if(!existMatchEdge) return false;
		}
	}
	return true;
}

/// @brief [For Debug] adjacentとnodeDegreesの値を一括で表示
void GridGraph::showGraph() const {
	for(int n = 0; n < _numNode; ++n) {
		std::cout << n << ": ";
		for(int d = 0; d < _degree; ++d) {
			std::cout << adjacent[n][d] << " ";
		}
		std::cout << "(degree=" << nodeDegrees[n] << ")" << std::endl;
	}
}

/// @brief [For Debug] 無効な追加が行われた場合, 警告してプログラムを終了する
/// @param node1 追加する辺の端点
/// @param node2 追加する辺の端点
void GridGraph::tryAddEdge(int node1, int node2, bool allowMultipleEdge, bool allowLoopEdge) {
	Grid grid(*this);
	bool valid = true;

	if(node1 < 0 || _numNode <= node1) {
		std::cerr << "The specified node[" << node1 << "] is out of the range." << std::endl;
		valid = false;
	}
	if(node2 < 0 || _numNode <= node2) {
		std::cerr << "The specified node[" << node2 << "] is out of the range." << std::endl;
		valid = false;
	}
	if(fullDegree(node1)) {
		std::cerr << "Cannot add an edge to the node[" << node1 << "] anymore for degree condition." << std::endl;
		valid = false;
	}
	if(fullDegree(node2)) {
		std::cerr << "Cannot add an edge to the node[" << node2 << "] anymore for degree condition." << std::endl;
		valid = false;
	}
	if(!grid.closeEnough(node1, node2)) {
		std::cerr << "The length of the edge[" << node1 << "-" << node2 << "] break length condition." << std::endl;
		valid = false;
	}
	if(!allowMultipleEdge && haveEdge(node1, node2)) {
		std::cerr << "The edge[" << node1 << "-" << node2 << "] is already added." << std::endl;
		valid = false;
	}
	if(!allowLoopEdge && node1 == node2) {
		std::cerr << "The loop edge[" << node1 << "-" << node2 << "] is tried to add." << std::endl;
		valid = false;
	}

	if(!valid) { this->showGraph(); exit(-1); }

	addEdge(node1, node2);
}

/// @brief [For Debug] 無効な削除が行われたとき, 警告してプログラムを終了する
/// @param node1 追加する辺の端点
/// @param node2 追加する辺の端点
void GridGraph::tryRemoveEdge(int node1, int node2) {
	bool valid = true;

	if(!haveEdge(node1, node2)) {
		std::cerr << "The length of the edge[" << node1 << "-" << node2 << "] break length condition." << std::endl;
		valid = false;
	}

	if(!valid) { this->showGraph(); exit(-1); }
	removeEdge(node1, node2);
}

/// @brief グラフ条件のデフォルト値を設定. 以降, 引数なしコンストラクタではここで設定した値によって初期化される
void GridGraph::setDefaultGraphCondition(int numRow, int numColumn, int degree, int maxLength) {
	GridGraph::s_defaultNumRow = numRow;
	GridGraph::s_defaultNumColumn = numColumn;
	GridGraph::s_defaultDegree = degree;
	GridGraph::s_defaultMaxLength = maxLength;
}

/* private */
/// @brief adjacent[node1][d] = node2 となるdを取得
/// @return 辺(node1-node2)が存在しないとき-1
int GridGraph::findDegreeIndex(int node1, int node2) const {
	for(int d = 0; d < nodeDegrees[node1]; ++d) {
		if(adjacent[node1][d] == node2) return d;
	}
	return -1;
}

void GridGraph::findDegreeIndexForLoopEdge(int node, int* degree1, int* degree2) const {
	for(int d = 0; d < nodeDegrees[node]; ++d) {
		if(adjacent[node][d] == node) { 
			*degree1 = d; 
			break;
		}
	}

	for(int d = *degree1 + 1; d < nodeDegrees[node]; ++d) {
		if(adjacent[node][d] == node) { 
			*degree2 = d; 
			break;
		}
	}
}

int GridGraph::s_defaultNumRow = -1;
int GridGraph::s_defaultNumColumn = -1;
int GridGraph::s_defaultDegree = -1;
int GridGraph::s_defaultMaxLength = -1;
