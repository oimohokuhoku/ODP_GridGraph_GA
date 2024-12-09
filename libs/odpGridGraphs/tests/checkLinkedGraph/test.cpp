#include <gtest/gtest.h>
#include <string>
#include "../../include/gridGraphs.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using std::string;

const string EDGES_FILE_DIR = "../_edgesFile/";

class CheckLinkedGraphTest: public ::testing::Test {
public:
    GridGraph linkedGraph = GridGraph(3, 3, 4, 2);      //S字グラフ
    GridGraph dislinkedGraph = GridGraph(3, 3, 4, 2);

    CheckLinkedGraphTest() {
        linkedGraph.clear();
        linkedGraph.addEdge(0, 1);
        linkedGraph.addEdge(1, 2);
        linkedGraph.addEdge(3, 4);
        linkedGraph.addEdge(4, 5);
        linkedGraph.addEdge(6, 7);
        linkedGraph.addEdge(7, 8);
        linkedGraph.addEdge(0, 3);
        linkedGraph.addEdge(5, 8);

        dislinkedGraph.clear();
        dislinkedGraph.addEdge(0, 1);
        dislinkedGraph.addEdge(1, 2);
        dislinkedGraph.addEdge(3, 4);
        dislinkedGraph.addEdge(4, 5);
        dislinkedGraph.addEdge(6, 7);
        dislinkedGraph.addEdge(7, 8);
    }
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(CheckLinkedGraphTest, Check_if_graph_is_linked) {
    CheckLinkedGraph checker;
    bool linked = checker.checkLinked(linkedGraph);
    EXPECT_TRUE(linked);
    EXPECT_EQ(checker.dislinkedNode(), -1);
}

TEST_F(CheckLinkedGraphTest, Check_if_graph_is_dislinked) {
    CheckLinkedGraph checker;
    bool dislinked = checker.checkLinked(dislinkedGraph);
    EXPECT_FALSE(dislinked);
    EXPECT_NE(checker.dislinkedNode(), -1);
}