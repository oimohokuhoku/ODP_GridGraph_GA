#include "edgeSwap.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <stack>
#include <algorithm>
#include "gridGraph.hpp"
#include "grid.hpp"
using std::vector;
using std::mt19937;
using namespace Cselab23Kimura::OdpGridGraphs;

EdgeSwap::EdgeSwap(int numSwappedEdge): _numSwappedEdge(numSwappedEdge) {
    if(numSwappedEdge <= 1) {
        std::cerr << "Runtime Error in EdgeSwap::EdgeSwap(int)." << std::endl;
        std::cerr << "Argument \"numSwappedEdge\" should be 2 or more." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void EdgeSwap::swap(GridGraph& graph, mt19937& rand) {
    int startNode = rand() % graph.numNode();
    swap(graph, startNode, rand);
}

void EdgeSwap::swap(GridGraph& graph, int startNodeIndex, std::mt19937& rand) {
    vector<int> swappedEdgeTour = selectSwappedEdgeTour(graph, startNodeIndex, rand);
    swapEdges(graph, swappedEdgeTour);
}

vector<int> EdgeSwap::selectSwappedEdgeTour(const GridGraph& graph, int startNode, mt19937& rand) {
    std::vector<int> stack(_numSwappedEdge * 2);
    Grid grid(graph);
    int stackSize = 0;
    std::vector<bool> passed(graph.numNode(), false); 

    stack[stackSize++] = startNode;
    passed[startNode] = true;
    selectSwappedEdgeTourBFS(graph, grid, stack, stackSize, passed, rand);

    return stack;
}

bool EdgeSwap::selectSwappedEdgeTourBFS(const GridGraph& graph, const Grid& grid, std::vector<int>& stack, int stackSize, std::vector<bool>& passed, std::mt19937& rand) {
    if(stackSize == _numSwappedEdge * 2) {
        int startInTour = stack[0];
        int endInTour = stack[stackSize - 1];
        if(grid.closeEnough(startInTour, endInTour))
            return true;
        else                                         
            return false;
    }

    int startNode = stack[stackSize - 1];

    if(stackSize % 2 == 0) {
        //辺の有無にかかわらずstartNodeと近い頂点を探索
        vector<int> nearNode = grid.selectNearNode(startNode);
        std::shuffle(nearNode.begin(), nearNode.end(), rand);
        for(int nextNode: nearNode) {
            if(passed[nextNode]) continue;

            stack[stackSize] = nextNode;
            passed[nextNode] = true;
            if(selectSwappedEdgeTourBFS(graph, grid, stack, stackSize + 1, passed, rand)) return true;

            passed[nextNode] = false;
        }
    }
    else {
        //startNodeと隣接する頂点を探索
        for(int d = 0; d < graph.nodeDegrees[startNode]; ++d) {
            int nextNode = graph.adjacent[startNode][d];

            if(passed[nextNode]) continue;

            stack[stackSize] = nextNode;
            passed[nextNode] = true;
            if(selectSwappedEdgeTourBFS(graph, grid, stack, stackSize + 1, passed, rand)) return true;

            passed[nextNode] = false;
        }
    }

    return false;
}

void EdgeSwap::swapEdges(GridGraph& graph, const vector<int>& swappedEdgeTour) {
    int size = swappedEdgeTour.size();
    for(int i = 0; i < size; i += 2) {
        int nodeA = swappedEdgeTour[i];
        int nodeB = swappedEdgeTour[i + 1];
        graph.removeEdge(nodeA, nodeB);
    }
    for(int i = 1; i < size; i += 2) {
        int nodeA = swappedEdgeTour[i];
        int nodeB = swappedEdgeTour[(i + 1) % size];
        graph.addEdge(nodeA, nodeB);
    }
}
