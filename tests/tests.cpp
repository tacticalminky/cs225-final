#include <catch2/catch_test_macros.hpp>

#include "edge.h"
#include "anime_graph.h"

TEST_CASE("Edge Tests", "") {
  Node n1 = new Node(1, "test1", std::vector<std::string>, -1, 0, 1);
  Node n2 = new Node(2, "test2", std::vector<std::string>, -1, 0, 1);
  Node n3 = new Node(3, "test3", std::vector<std::string>, -1, 0, 1);

  Edge e1(n1, n2, 0);
  Edge e1_reverse(n2, n1, 0);
  Edge e2(n1, n3, 0);
  Edge e3(n2, n3, 0);

  REQUIRE(e1 == e1);
  REQUIRE(e1 == e1_reverse);
  REQUIRE(e1 != e2);
  REQUIRE(e1 != e3);
  REQUIRE(e2 != e3);

  delete n1;
  delete n2;
  delete n3;
}

TEST_CASE("AnimeGraph::importAnime Tests", "") {
  // TODO: Implement tests
  REQUIRE(0);
}

TEST_CASE("AnimeGraph::importRatings Tests", "") {
  // TODO: Implement tests
  REQUIRE(0);
}

TEST_CASE("AnimeGraph::makeGraph Tests", "") {
  // TODO: Implement tests
  REQUIRE(0);
}

TEST_CASE("AnimeGraph::getAdjacentEdges Tests", "") {
  // TODO: Implement tests
  REQUIRE(0);
}

TEST_CASE("AnimeGraph::getEdge Tests", "") {
  // TODO: Implement tests
  REQUIRE(0);
}

TEST_CASE("AnimeGraph::getNode Tests", "") {
  // TODO: Implement tests
  REQUIRE(0);
}

TEST_CASE("AnimeGraph::nodeExists Tests", "") {
  // TODO: Implement tests
  REQUIRE(0);
}
