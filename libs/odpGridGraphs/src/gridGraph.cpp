#include "gridGraph.hpp"
#include <iostream>
#include <climits>
#include <utility>
#include "grid.hpp"
#include "adjAspl.hpp"
#include "checkLinkedGraph.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;

GridGraph::GridGraph(int numRow, int numColumn, int degree, int maxLength) :
	GridGraph(Grid(numRow, numColumn, degree, maxLength))
{}

GridGraph::GridGraph(const Grid& grid) : 
	_grid(grid),
	_adjacent(nullptr),
	_nodeDegrees(nullptr)
{
	newPointerArrays();
	clearEdges();
	_diameterCache   = INF_DIAMETER;
	_asplCache       = INF_ASPL;
	_evaluated  = false;
}

GridGraph::GridGraph(const GridGraph& rhs) : 
	_grid(rhs._grid),
	_adjacent(nullptr),
	_nodeDegrees(nullptr)
{
	*this = rhs;
}

GridGraph::GridGraph(GridGraph&& rhs) : 
	_grid(rhs._grid),
	_adjacent(nullptr),
	_nodeDegrees(nullptr)
{
	*this = std::move(rhs);
}

GridGraph::~GridGraph() {
	if(_adjacent != nullptr) {
		for(int i = 0; i < _grid.numNode; ++i) delete[] _adjacent[i];
		delete[] _adjacent;
		_adjacent = nullptr;
	}
	if(_nodeDegrees != nullptr) {
		delete[] _nodeDegrees;
		_nodeDegrees = nullptr;
	}
}

GridGraph& GridGraph::operator= (const GridGraph& rhs) {
	if(!rhs.isValidObject())     throw std::logic_error("Invalid object is referenced");
	if(this->_grid != rhs._grid) throw std::invalid_argument("Cannot substitute graph with different constraints.");

	int numNode = _grid.numNode;
	int degree  = _grid.degree;

	if(this->_adjacent == nullptr) {
		_adjacent = new int*[numNode];
		for(int i = 0; i < numNode; ++i) 
			_adjacent[i] = new int[degree];
	}
	if(this->_nodeDegrees == nullptr) {
		_nodeDegrees = new int[numNode];
	}

	for(int n = 0; n < numNode; ++n) {
		for(int d = 0; d < degree; ++d) {
			this->_adjacent[n][d] = rhs._adjacent[n][d];
		}
	}
	for(int n = 0; n < numNode; ++n) {
		this->_nodeDegrees[n] = rhs._nodeDegrees[n];
	}
	this->_asplCache      = rhs._asplCache;
	this->_diameterCache  = rhs._diameterCache;
	this->_evaluated = rhs._evaluated;

	return *this;
}

GridGraph& GridGraph::operator= (GridGraph&& rhs) {
	if(!rhs.isValidObject())     throw std::logic_error("Invalid object is referenced");
	if(this->_grid != rhs._grid) throw std::invalid_argument("Cannot substitute graph with different constraints.");

	this->deletePointerArrays();

	this->_adjacent    = rhs._adjacent;
	this->_nodeDegrees = rhs._nodeDegrees;
	this->_asplCache       = rhs._asplCache;
	this->_diameterCache   = rhs._diameterCache;
	this->_evaluated = rhs._evaluated;

	rhs._adjacent    = nullptr;
	rhs._nodeDegrees = nullptr;
	rhs._diameterCache   = INF_DIAMETER;
	rhs._asplCache       = INF_ASPL;

	return *this;
}

/// @brief Remove all edges.
void GridGraph::clearEdges() {
	for(int n = 0; n < _grid.numNode; ++n) {
		for(int d = 0; d < _grid.degree; ++d) {
			this->_adjacent[n][d] = EMPTY_PORT;
		}
	}
	for(int n = 0; n < _grid.numNode; ++n) {
		this->_nodeDegrees[n] = 0;
	}
	this->_diameterCache  = INF_DIAMETER;
	this->_asplCache      = INF_ASPL;
	this->_evaluated = true;
}

/// @brief Add edge to this graph. But, removing a loop edge isn't supported.
void GridGraph::addEdge(int nodeA, int nodeB) {
	if(nodeA < 0 || _grid.numNode <= nodeA) throw std::out_of_range("The node[" + std::to_string(nodeA) +"] isn't exists");
	if(nodeB < 0 || _grid.numNode <= nodeB) throw std::out_of_range("The node[" + std::to_string(nodeB) +"] isn't exists");
	if(fullDegree(nodeA)) throw std::invalid_argument("Degree of the node[" + std::to_string(nodeA) + "] is already full");
	if(fullDegree(nodeB)) throw std::invalid_argument("Degree of the node[" + std::to_string(nodeB) + "] is already full");
	if(nodeA == nodeB)    throw std::invalid_argument("Not allowed to add loop edge[" + std::to_string(nodeA) + "-" + std::to_string(nodeB) + "]");
	if(!_grid.closeEnough(nodeA, nodeB)) throw std::invalid_argument("The edge[" + std::to_string(nodeA) + "-" + std::to_string(nodeB) + "] over constarint length");

	addToAdajcentList(nodeA, nodeB);
	addToAdajcentList(nodeB, nodeA);
	this->_evaluated = false;
}

/// @brief Remove edge from this graph. But, removing a loop edge isn't supported.
void GridGraph::removeEdge(int nodeA, int nodeB) {
	if(nodeA < 0 || _grid.numNode <= nodeA) throw std::out_of_range("The node[" + std::to_string(nodeA) +"] isn't exists");
	if(nodeB < 0 || _grid.numNode <= nodeB) throw std::out_of_range("The node[" + std::to_string(nodeB) +"] isn't exists");
	if(nodeA == nodeB) throw std::invalid_argument("Not allowed to remove loop edge[" + std::to_string(nodeA) + "-" + std::to_string(nodeB) + "]");
	if(!haveEdge(nodeA, nodeB)) throw std::invalid_argument("The Edge[" + std::to_string(nodeA) + "-" + std::to_string(nodeB) + "] isn't exists.");

	removeFromAdjacentList(nodeA, nodeB);
	removeFromAdjacentList(nodeB, nodeA);
	this->_evaluated = false;
}

void GridGraph::addEdgeAllowingLoops(int nodeA, int nodeB) {
	if(nodeA < 0 || _grid.numNode <= nodeA) throw std::out_of_range("The node[" + std::to_string(nodeA) +"] isn't exists");
	if(nodeB < 0 || _grid.numNode <= nodeB) throw std::out_of_range("The node[" + std::to_string(nodeB) +"] isn't exists");
	if(fullDegree(nodeA)) throw std::invalid_argument("Degree of the node[" + std::to_string(nodeA) + "] is already full");
	if(fullDegree(nodeB)) throw std::invalid_argument("Degree of the node[" + std::to_string(nodeB) + "] is already full");
	if(!_grid.closeEnough(nodeA, nodeB)) throw std::invalid_argument("The edge[" + std::to_string(nodeA) + "-" + std::to_string(nodeB) + "] over constarint length");

	addToAdajcentList(nodeA, nodeB);
	addToAdajcentList(nodeB, nodeA);
	this->_evaluated = false;
}

void GridGraph::removeEdgeAllowingLoops(int nodeA, int nodeB) {
	if(nodeA < 0 || _grid.numNode <= nodeA) throw std::out_of_range("The node[" + std::to_string(nodeA) +"] isn't exists");
	if(nodeB < 0 || _grid.numNode <= nodeB) throw std::out_of_range("The node[" + std::to_string(nodeB) +"] isn't exists");
	if(!haveEdge(nodeA, nodeB)) throw std::invalid_argument("The Edge[" + std::to_string(nodeA) + "-" + std::to_string(nodeB) + "] isn't exists.");

	if(nodeA != nodeB) {
		removeFromAdjacentList(nodeA, nodeB);
		removeFromAdjacentList(nodeB, nodeA);
	}
	else {
		removeLoopEdgeFromAdajcentList(nodeA);
	}
	this->_evaluated = false;
}

/// @brief Check if this diameter or ASPL smaller than argument's.
bool GridGraph::betterThan(const GridGraph& graph) const {
	this->evaluate();
	graph.evaluate();

	if(this->_diameterCache < graph._diameterCache) return true;
	if(this->_diameterCache > graph._diameterCache) return false;

	if(this->_asplCache < graph._asplCache) return true;
	else						  return false;
}

/// @brief Check if this diameter or ASPL larger than that of the argument.
bool GridGraph::worseThan(const GridGraph& graph) const {
	this->evaluate();
	graph.evaluate();

	if(this->_diameterCache > graph._diameterCache) return true;
	if(this->_diameterCache < graph._diameterCache) return false;

	if(this->_asplCache > graph._asplCache) return true;
	else						return false;
}

/// @brief Check if this diameter or ASPL larger than that of the argument.
bool GridGraph::haveEdge(int nodeA, int nodeB) const {
	for(int d = 0; d < _nodeDegrees[nodeA]; ++d) {
		if(_adjacent[nodeA][d] == nodeB) return true;
	}
	return false;
}

/// @brief Check if the node has max degree.
bool GridGraph::fullDegree(int node) const {
	return (this->_nodeDegrees[node] == _grid.degree);
}

/// @brief Check if this topology match argument's topology. Maching graphs when rotate are considered different topology.
bool GridGraph::matchGraph(const GridGraph& graph) const {
	if(this->_evaluated && graph._evaluated) {
		if(this->_diameterCache != graph._diameterCache) return false;
		if(this->_asplCache     != graph._asplCache)     return false;
	}

	for(int node1 = 0; node1 < _grid.numNode; ++node1) {
		for(int d1 = 0; d1 < this->_nodeDegrees[node1]; ++d1) {
			int node2A = this->_adjacent[node1][d1];
			if(node1 == node2A) continue;

			bool existMatchEdge = false;
			for(int d2 = 0; d2 < graph._nodeDegrees[node1]; ++d2) {
				int node2B = graph._adjacent[node1][d2];
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

/// @brief [For Debug] show graph topology with adjacents list.
void GridGraph::showGraph() const {
	for(int n = 0; n < _grid.numNode; ++n) {
		std::cout << n << ": ";
		for(int d = 0; d < _grid.degree; ++d) {
			std::cout << _adjacent[n][d] << " ";
		}
		std::cout << "(degree=" << _nodeDegrees[n] << ")" << std::endl;
	}
}

/// @brief Compute diameter of this graph. If no edges is changed, diameter isn't recompute.
int GridGraph::computeDiameter() const {
	evaluate();
	return _diameterCache;
}

/// @brief Compute ASPL of this graph. If no edges is changed, ASPL isn't recompute.
double GridGraph::computeAspl() const {
	evaluate();
	return _asplCache;
}

/* private */
void GridGraph::evaluate() const {
	if(_evaluated) return;

	AdjAspl evaluate = AdjAspl::computeDiameterAndAspl(_grid.numNode, _adjacent, _nodeDegrees);
	this->_diameterCache = evaluate.diameter();
	this->_asplCache     = evaluate.aspl();
	this->_evaluated = true;
}

void GridGraph::newPointerArrays() {
	_adjacent = new int*[_grid.numNode];
	for(int i = 0; i < _grid.numNode; ++i) {
		_adjacent[i] = new int[_grid.degree];
	}

	_nodeDegrees = new int[_grid.numNode];
}

void GridGraph::deletePointerArrays() {
	if(_adjacent != nullptr) {
		for(int i = 0; i < _grid.numNode; ++i) delete[] _adjacent[i];
		delete[] _adjacent;
	}
	if(_nodeDegrees != nullptr) {
		delete[] _nodeDegrees;
	}
}

int GridGraph::findPortIndex(int srcNode, int distNode) const {
	for(int d = 0; d < _nodeDegrees[srcNode]; ++d) {
		if(_adjacent[srcNode][d] == distNode) return d;
	}
	return -1;
}

void GridGraph::findPortIndexForLoopEdge(int node, int* degree1, int* degree2) const {
	for(int d = 0; d < _nodeDegrees[node]; ++d) {
		if(_adjacent[node][d] == node) { 
			*degree1 = d; 
			break;
		}
	}

	for(int d = *degree1 + 1; d < _nodeDegrees[node]; ++d) {
		if(_adjacent[node][d] == node) { 
			*degree2 = d; 
			break;
		}
	}
}

void GridGraph::addToAdajcentList(int srcNode, int distNode) {
	int portIndex = _nodeDegrees[srcNode];
	_adjacent[srcNode][portIndex] = distNode;
	_nodeDegrees[srcNode]++;
}

void GridGraph::removeFromAdjacentList(int srcNode, int distNode) {
	int portIndex     = findPortIndex(srcNode, distNode);
	int lastPortIndex = _nodeDegrees[srcNode] - 1;
	_adjacent[srcNode][portIndex] = _adjacent[srcNode][lastPortIndex];
	_adjacent[srcNode][lastPortIndex] = EMPTY_PORT;

	_nodeDegrees[srcNode]--;
}

void GridGraph::removeLoopEdgeFromAdajcentList(int node) {
	int firstPortIndex = -1, secondPortIndex = -1;
	findPortIndexForLoopEdge(node, &firstPortIndex, &secondPortIndex);

	int lastPortIndex = _nodeDegrees[node] - 1;
	_adjacent[node][secondPortIndex] = _adjacent[node][lastPortIndex];
	_adjacent[node][lastPortIndex] = EMPTY_PORT;
	_nodeDegrees[node]--;

	lastPortIndex = _nodeDegrees[node] - 1;
	_adjacent[node][firstPortIndex] = _adjacent[node][lastPortIndex];
	_adjacent[node][lastPortIndex] = EMPTY_PORT;
	_nodeDegrees[node]--;
}
