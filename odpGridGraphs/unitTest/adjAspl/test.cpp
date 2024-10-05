#include <gtest/gtest.h>
#include <string>
#include "../../include/gridGraphs.hpp"
using std::string;
using namespace Cselab23Kimura::OdpGridGraphs;

const string EDGES_FILE_DIR = "../_edgesFile/";

TEST(AdjAsplTest, SmallGraph5x5_4_2) {
    GridGraph graph = EdgesFileReader::read(EDGES_FILE_DIR + "w5h5d4r2_best.edges");
    graph.evaluate();

    EXPECT_EQ(4, graph.diameter());
    EXPECT_DOUBLE_EQ(2.2666666666666666, graph.aspl());
}

TEST(AdjAsplTest, SmallGraph5x10_4_2) {
    GridGraph graph = EdgesFileReader::read(EDGES_FILE_DIR + "w5h10d4r2_best.edges");
    graph.evaluate();

    EXPECT_EQ(7, graph.diameter());
    EXPECT_DOUBLE_EQ(3.106938775510204, graph.aspl());
}

TEST(AdjAsplTest, SmallGraph10x10_4_2) {
    GridGraph graph = EdgesFileReader::read(EDGES_FILE_DIR + "w10h10d4r2_best.edges");
    graph.evaluate();

    EXPECT_EQ(9, graph.diameter());
    EXPECT_DOUBLE_EQ(3.985858585858586, graph.aspl());
}

TEST(AdjAsplTest, SmallGraph10x10_6_3) {
    GridGraph graph = EdgesFileReader::read(EDGES_FILE_DIR + "w10h10d6r3_best.edges");
    graph.evaluate();

    EXPECT_EQ(6, graph.diameter());
    EXPECT_DOUBLE_EQ(2.903030303030303, graph.aspl());
}

TEST(AdjAsplTest, SmallGraph10x10_8_4) {
    GridGraph graph = EdgesFileReader::read(EDGES_FILE_DIR + "w10h10d8r4_best.edges");
    graph.evaluate();

    EXPECT_EQ(5, graph.diameter());
    EXPECT_DOUBLE_EQ(2.426262626262626, graph.aspl());
}

TEST(AdjAsplTest, SmallGraph100x100_4_2) {
    GridGraph graph = EdgesFileReader::read(EDGES_FILE_DIR + "w100h100d4r2_best.edges");
    graph.evaluate();

    EXPECT_EQ(99, graph.diameter());
    EXPECT_DOUBLE_EQ(33.672444684468445, graph.aspl());
}

TEST(AdjAsplTest, SmallGraph100x100_6_3) {
    GridGraph graph = EdgesFileReader::read(EDGES_FILE_DIR + "w100h100d6r3_best.edges");
    graph.evaluate();

    EXPECT_EQ(66, graph.diameter());
    EXPECT_DOUBLE_EQ(22.574951135113512, graph.aspl());
}

TEST(AdjAsplTest, SmallGraph100x100_8_4) {
    GridGraph graph = EdgesFileReader::read(EDGES_FILE_DIR + "w100h100d8r4_best.edges");
    graph.evaluate();

    EXPECT_EQ(50, graph.diameter());
    EXPECT_DOUBLE_EQ(17.06150103010301, graph.aspl());
}
