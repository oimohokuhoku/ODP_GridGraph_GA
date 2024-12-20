#include "gridGraph.hpp"
#include <iostream>
#include <climits>
#include <utility>
#include "grid.hpp"
#include "adjAspl.hpp"
#include "checkLinkedGraph.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;

/// @brief グラフの条件を指定して初期化
GridGraph::GridGraph(int numRow, int numColumn, int degree, int maxLength) :
	GridGraph(Grid(numRow, numColumn, degree, maxLength))
{}

GridGraph::GridGraph(const Grid& grid) : _grid(grid) {
	adjacent = new int*[_grid.numNode];
	for(int i = 0; i < _grid.numNode; ++i) adjacent[i] = new int[_grid.degree];

	nodeDegrees = new int[_grid.numNode];
	_diameter   = INF_DIAMETER;
	_aspl       = INF_ASPL;
	_evaluated  = false;
}

GridGraph::GridGraph(const GridGraph& obj) : GridGraph(obj._grid) {
	*this = obj;
}

GridGraph::GridGraph(GridGraph&& obj) :
	_grid(obj._grid),
	adjacent(nullptr),
	nodeDegrees(nullptr)
{
	*this = std::move(obj);
}

GridGraph::~GridGraph() {
	if(adjacent != nullptr) {
		for(int i = 0; i < _grid.numNode; ++i) delete[] adjacent[i];
		delete[] adjacent;
		adjacent = nullptr;
	}
	if(nodeDegrees != nullptr) {
		delete[] nodeDegrees;
		nodeDegrees = nullptr;
	}
}

GridGraph& GridGraph::operator= (const GridGraph& obj) {
	int numNode = _grid.numNode;
	int degree  = _grid.degree;

	if(this->adjacent == nullptr) {
		adjacent = new int*[numNode];
		for(int i = 0; i < numNode; ++i) adjacent[i] = new int[degree];
	}
	if(this->nodeDegrees == nullptr) {
		nodeDegrees = new int[numNode];
	}

	for(int n = 0; n < numNode; ++n) {
		for(int d = 0; d < degree; ++d) {
			this->adjacent[n][d] = obj.adjacent[n][d];
		}
	}
	for(int n = 0; n < numNode; ++n) {
		this->nodeDegrees[n] = obj.nodeDegrees[n];
	}
	this->_aspl      = obj._aspl;
	this->_diameter  = obj._diameter;
	this->_evaluated = obj._evaluated;

	return *this;
}

GridGraph& GridGraph::operator= (GridGraph&& obj) {
	if(this->adjacent != nullptr) {
		for(int i = 0; i < _grid.numNode; ++i) delete[] this->adjacent[i];
		delete[] this->adjacent;
	}
	if(nodeDegrees != nullptr) {
		delete[] this->nodeDegrees;
	}

	this->adjacent    = obj.adjacent;
	this->nodeDegrees = obj.nodeDegrees;
	this->_aspl       = obj._aspl;
	this->_diameter   = obj._diameter;
	this->_evaluated = obj._evaluated;

	obj.adjacent    = nullptr;
	obj.nodeDegrees = nullptr;
	obj._diameter   = INF_DIAMETER;
	obj._aspl       = INF_ASPL;

	return *this;
}

/// @brief すべての辺を削除する
void GridGraph::clear() {
	for(int n = 0; n < _grid.numNode; ++n) {
		for(int d = 0; d < _grid.degree; ++d) {
			this->adjacent[n][d] = -1;
		}
	}
	for(int n = 0; n < _grid.numNode; ++n) {
		this->nodeDegrees[n] = 0;
	}
	this->_diameter = INF_DIAMETER;
	this->_aspl     = INF_ASPL;
	this->_evaluated = true;
}

/// @brief 辺を追加する. 高速だが, 安全に追加される保証はない
/// @param node1 追加辺の端頂点
/// @param node2 追加辺の端頂点
void GridGraph::addEdge(int node1, int node2) {
	this->adjacent[node1][nodeDegrees[node1]] = node2;
	nodeDegrees[node1]++;

	this->adjacent[node2][nodeDegrees[node2]] = node1;
	nodeDegrees[node2]++;

	this->_evaluated = false;
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

	this->_evaluated = false;
}

/// @brief グラフの評価値を比較する
bool GridGraph::betterThan(const GridGraph& graph) const {
	if(!_evaluated) evaluate();

	if(this->_diameter < graph._diameter) return true;
	if(this->_diameter > graph._diameter) return false;

	if(this->_aspl < graph._aspl) return true;
	else						  return false;
}

/// @brief グラフの評価値を比較する
bool GridGraph::worseThan(const GridGraph& graph) const {
	if(!_evaluated) evaluate();

	if(this->_diameter > graph._diameter) return true;
	if(this->_diameter < graph._diameter) return false;

	if(this->_aspl > graph._aspl) return true;
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
	return (this->nodeDegrees[node] == _grid.degree);
}

/// @brief 同じトポロジーのグラフかを判定. 回転によって一致するグラフは異なるものとみなす.
bool GridGraph::matchGraph(const GridGraph& graph) const {
	for(int node1 = 0; node1 < _grid.numNode; ++node1) {
		for(int d1 = 0; d1 < this->nodeDegrees[node1]; ++d1) {
			int node2A = this->adjacent[node1][d1];
			if(node1 == node2A) continue;

			bool existMatchEdge = false;
			for(int d2 = 0; d2 < graph.nodeDegrees[node1]; ++d2) {
				int node2B = graph.adjacent[node1][d2];
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
	for(int n = 0; n < _grid.numNode; ++n) {
		std::cout << n << ": ";
		for(int d = 0; d < _grid.degree; ++d) {
			std::cout << adjacent[n][d] << " ";
		}
		std::cout << "(degree=" << nodeDegrees[n] << ")" << std::endl;
	}
}

/// @brief [For Debug] 無効な追加が行われた場合, 警告してプログラムを終了する
/// @param node1 追加する辺の端点
/// @param node2 追加する辺の端点
void GridGraph::tryAddEdge(int node1, int node2, bool allowMultipleEdge, bool allowLoopEdge) {
	bool valid = true;

	if(node1 < 0 || _grid.numNode <= node1) {
		std::cerr << "The specified node[" << node1 << "] is out of the range." << std::endl;
		valid = false;
	}
	if(node2 < 0 || _grid.numNode <= node2) {
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
	if(!_grid.closeEnough(node1, node2)) {
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

	if(!valid) { 
		this->showGraph(); 
		exit(EXIT_FAILURE);
	}

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

int GridGraph::diameter() const {
	if(!_evaluated) evaluate();
	return _diameter;
}

double GridGraph::aspl() const {
	if(!_evaluated) evaluate();
	return _aspl;
}

/* private */
void GridGraph::evaluate() const {
	AdjAspl evaluate;
	evaluate(*this);
	this->_diameter = evaluate.diameter();
	this->_aspl     = evaluate.aspl();
	this->_evaluated = true;
}

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
