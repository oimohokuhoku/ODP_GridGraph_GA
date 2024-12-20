#include "adjAspl.hpp"

#include <iostream>
#include <climits>
#include <cstdint>
#include "gridGraph.hpp"
#include "grid.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;

void AdjAspl::operator() (const GridGraph& graph) {
	//高速化のために関数を分離せずにべた書きしてます.
	//アルゴリズムはこちらを参照(http://research.nii.ac.jp/graphgolf/2019/candar19/graphgolf2019-nakao.pdf).

	//int64を無理やりbit列として扱って計算量を削減している.
	//"a = 128" なら "a = 0000...0010000000" として考える.

	int numNode = graph.numNode();
    int numSegment = (numNode + (_BIT_LENGTH - 1)) / _BIT_LENGTH;
	int numMatrixBit = numNode * numNode;
	int64_t** A     = newIdentityMatrix(numNode, numSegment);
    int64_t** nextA = newIdentityMatrix(numNode, numSegment);

    long distanceSum = (numNode * numNode) - numNode; //単位行列の0の個数
    int k = 1;
	while(k < numNode) {
		//行列Aを更新
		for(int node = 0; node < numNode; ++node) {
			for(int d = 0; d < graph.nodeDegrees[node]; ++d) {
				int adjNode = graph.adjacent[node][d];
				for(int seg = 0; seg < numSegment; ++seg)
					nextA[node][seg] |= A[adjNode][seg];
			}
		}

		//0の個数をカウント
		int numZero = numMatrixBit;
		for(int row = 0; row < numNode; ++row) {
			for(int seg = 0; seg < numSegment; ++seg) {
				numZero -= __builtin_popcountl(nextA[row][seg]);
			}
		}

		if(numZero == 0) break;

		distanceSum += numZero;
		k++;

		//A, nextAをスワップ
		int64_t** temp = A;
		A = nextA;
		nextA = temp;
    }

	//非連結
	if(k == numNode) {
		this->_diameter = INF_DIAMETER;
		this->_aspl     = INF_ASPL;
		this->_dislinkedNode = findDislinkedNode(A, numSegment);
	}
	//連結
    else {
	    this->_diameter = k;
	    this->_aspl = (double)distanceSum / ((numNode - 1) * numNode);
	    this->_dislinkedNode = -1;
    }

	for(int i = 0; i < numNode; ++i) {
		delete[] A[i];
		delete[] nextA[i];
	}
	delete[] A;
	delete[] nextA;
}

int64_t** AdjAspl::newIdentityMatrix(int numNode, int numSegment) {
	int64_t** matrix = new int64_t*[numNode];
	for(int i = 0; i < numNode; ++i) matrix[i] = new int64_t[numSegment];
	for(int i = 0; i < numNode; ++i) {
		for(int j = 0; j < numSegment; ++j) 
			matrix[i][j] = 0;
	}

	//対角成分を1に
	int bitPos = _BIT_LENGTH - 1;
	int segmentIndex = 0;
	for(int i = 0; i < numNode; ++i) {
		matrix[i][segmentIndex] = (0x1ULL << bitPos);

		--bitPos;

		if(bitPos < 0) {
			segmentIndex++;
			bitPos = _BIT_LENGTH - 1;
		}
	}

	return matrix;
}

int AdjAspl::findDislinkedNode(int64_t** matrix, int numSegment) {
	for(int seg = 0; seg < numSegment; ++seg) {
		for(int bit = _BIT_LENGTH - 1; bit >= 0; --bit) {
			uint64_t mask = ((uint64_t)1 << bit);
			uint64_t n = mask & matrix[0][seg];

			if(n == 0) 
				return (seg * _BIT_LENGTH + (_BIT_LENGTH - bit)) - 1;
		}
	}
	
	std::cerr << "Error in AdjAspl::findDislinkedNode(int64_t**, int)" << std::endl;
	std::cerr << "This graph is linked, but this judge being dislinked" << std::endl;
	exit(1);
	return 0; //vscodeのインテリセンス対策(特に意味はない)
}
