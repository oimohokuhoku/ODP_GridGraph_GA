#include "adjAspl.hpp"

#include <iostream>
#include <climits>
#include <cstdint>
#include "gridGraph.hpp"
#include "grid.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;

/// @brief Computes the diameter and ASPL of a graph.
/// @param numNode The number of nodes in the graph.
/// @param adjacent The adjacency list in class GridGraph.
/// @param nodeDegrees The degree list of each node in class GridGraph.
/// @return An AdjAspl object containing the diameter, ASPL, and the index of any disconnected node.
AdjAspl AdjAspl::computeDiameterAndAspl(int numNode, int const *const *const adjacent, int const *const nodeDegrees) {
    /* Implementation Hint:
    ** An Matrix is represented by a 2D array of 64-bit integers. 
    ** The segment represents the number of 64-bit integers in the row.
    ** For example, if the number of nodes is 100, the matrix is represented by a 2D int64_t array of 2x100.
    ** We can consider the row of the matrix as 64x2 elements. (28 bits are not used).
    */

    int numSegment = (numNode + (_BIT_LENGTH - 1)) / _BIT_LENGTH;
    int numMatrixBit = numNode * numNode;
    int64_t** A     = newIdentityMatrix(numNode, numSegment);
    int64_t** nextA = newIdentityMatrix(numNode, numSegment);

    long distanceSum = (numNode * numNode) - numNode; // Initial count of zeros in the identity matrix
    int k = 1;
    while(k < numNode) {
        // Update matrix A
        for(int node = 0; node < numNode; ++node) {
            for(int d = 0; d < nodeDegrees[node]; ++d) {
                int adjNode = adjacent[node][d];
                for(int seg = 0; seg < numSegment; ++seg)
                    nextA[node][seg] |= A[adjNode][seg];
            }
        }

        // Count the number of zeros
        int numZero = numMatrixBit;
        for(int row = 0; row < numNode; ++row) {
            for(int seg = 0; seg < numSegment; ++seg) {
                numZero -= __builtin_popcountl(nextA[row][seg]);
            }
        }

        if(numZero == 0) break;

        distanceSum += numZero;
        k++;

        // Swap A and nextA
        int64_t** temp = A;
        A = nextA;
        nextA = temp;
    }

    int diameter;
    double aspl;
    int dislinkedNode;
    if(k == numNode) { /* not linked graph */
        diameter = GridGraph::INF_DIAMETER;
        aspl     = GridGraph::INF_ASPL;
        dislinkedNode = findDislinkedNode(A, numSegment);
    }
    else { /* linked graph */
        diameter = k;
        aspl     = (double)distanceSum / ((numNode - 1) * numNode);
        dislinkedNode = -1;
    }

    for(int i = 0; i < numNode; ++i) {
        delete[] A[i];
        delete[] nextA[i];
    }
    delete[] A;
    delete[] nextA;

    return AdjAspl(diameter, aspl, dislinkedNode);
}

/// @brief Creates a new identity matrix.
/// @param numNode The number of nodes in the graph.
/// @param numSegment The number of segments in the matrix.
/// @return A pointer to the newly created identity matrix.
int64_t** AdjAspl::newIdentityMatrix(int numNode, int numSegment) {
    int64_t** matrix = new int64_t*[numNode];
    for(int i = 0; i < numNode; ++i) matrix[i] = new int64_t[numSegment];
    for(int i = 0; i < numNode; ++i) {
        for(int j = 0; j < numSegment; ++j) 
            matrix[i][j] = 0;
    }

    // Set diagonal elements to 1
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

/// @brief Finds the first node disconnecting to node[0].
/// @param matrix The matrix representing the graph.
/// @param numSegment The number of segments in the matrix.
/// @return The index of the first disconnected node.
/// @details This function scans the matrix to find the first node that is not connected to node 0.
int AdjAspl::findDislinkedNode(int64_t** matrix, int numSegment) {
    for(int seg = 0; seg < numSegment; ++seg) {
        for(int bit = _BIT_LENGTH - 1; bit >= 0; --bit) {
            uint64_t mask = ((uint64_t)1 << bit);
            uint64_t n = mask & matrix[0][seg];

            if(n == 0) 
                return (seg * _BIT_LENGTH + (_BIT_LENGTH - bit)) - 1;
        }
    }
    
    throw std::logic_error("linked graph is considered dislinked graph");
}

/// @brief Constructs an AdjAspl object with the given diameter, ASPL, and disconnected node index.
/// @param diameter The diameter of the graph.
/// @param aspl The ASPL of the graph.
/// @param dislinkedNode The index of the disconnected node, or -1 if the graph is fully connected.
AdjAspl::AdjAspl(int diameter, double aspl, int dislinkedNode) :
    _diameter(diameter),
    _aspl(aspl),
    _dislinkedNode(dislinkedNode)
{}
