#include <catch2/catch_test_macros.hpp>

#include "edge.h"
#include "anime_graph.h"
#include "iostream"

TEST_CASE("Edge Tests", "") {
  Node* n1 = new Node;
  n1->id = 1;

  Node* n2 = new Node;
  n2->id = 2;

  Node* n3 = new Node;
  n3->id = 3;

  Edge e1(n1, n2, 0);
  Edge e1_reverse(n2, n1, 0);
  Edge e2(n1, n3, 0);
  Edge e3(n2, n3, 0);

  REQUIRE(e1 == e1);
  REQUIRE(e1 == e1_reverse);
  REQUIRE_FALSE(e1 == e2);
  REQUIRE_FALSE(e1 == e3);
  REQUIRE_FALSE(e2 == e3);

  delete n1;
  delete n2;
  delete n3;
}

TEST_CASE("AnimeGraph::importAnime Tests", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  REQUIRE(a.nodeExists(a.getNode(1)));
  REQUIRE(a.nodeExists(a.getNode(6)));
  REQUIRE(a.nodeExists(a.getNode(7)));
  REQUIRE(a.nodeExists(a.getNode(8)));
  REQUIRE(a.nodeExists(a.getNode(15)));
  
  Node* node = a.getNode(1);
  REQUIRE(node->id == 1);
  REQUIRE(node->name == "Cowboy Bebop");
  REQUIRE(node->genres.size() == 6);
  REQUIRE(node->genres[1] == "Adventure");
  REQUIRE(node->episodes == 26);
  REQUIRE(node->rating == 8.82);
  REQUIRE(node->members == 486824);

  node = a.getNode(8);
  REQUIRE(node->id == 8);
  REQUIRE(node->name == "Beet the Vandel Buster");
  REQUIRE(node->genres.size() == 1);
  REQUIRE(node->genres[0] == "Default");
  REQUIRE(node->episodes == -1);
  REQUIRE(node->rating == -1);
  REQUIRE(node->members == 9848);
}

// TEST_CASE("AnimeGraph::importRatings Tests", "") {
//   AnimeGraph a;
//   a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
//   std::unordered_map<int,std::vector<int>> r = a.testImportRatings("../tests/data/test_rating.csv");
//   REQUIRE(r.size() == 4);
//   REQUIRE(r.at(1).size() == 3);
//   REQUIRE(r.at(6).size() == 2);
//   REQUIRE(r.at(7).size() == 3);
//   REQUIRE(r.at(8).size() == 1);
//   REQUIRE(r.at(6).at(0) == 1);
//   REQUIRE(r.at(6).at(1) == 3); 
// }

TEST_CASE("AnimeGraph::makeGraph Tests", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  Node* node1 = a.getNode(1);
  Node* node2 = a.getNode(6);
  Node* node3 = a.getNode(7);
  Node* node4 = a.getNode(8);
  Node* node5 = a.getNode(15);
  REQUIRE(a.edgeExists(node1, node2));
  REQUIRE(a.getEdge(node1, node2)->getWeight() == 2);
  REQUIRE(a.getEdge(node1, node2) == a.getEdge(node2, node1));
  REQUIRE(a.edgeExists(node1, node3));
  REQUIRE(a.getEdge(node1, node3)->getWeight() == 3);
  REQUIRE(a.getEdge(node1, node3) == a.getEdge(node3, node1));
  REQUIRE(a.edgeExists(node1, node4));
  REQUIRE(a.getEdge(node1, node4)->getWeight() == 1);
  REQUIRE(a.getEdge(node1, node4) == a.getEdge(node4, node1));
  REQUIRE(a.edgeExists(node2, node3));
  REQUIRE(a.getEdge(node2, node3)->getWeight() == 2);
  REQUIRE(a.getEdge(node2, node3) == a.getEdge(node3, node2));
  REQUIRE(a.edgeExists(node3, node4));
  REQUIRE(a.getEdge(node3, node4)->getWeight() == 1);
  REQUIRE(a.getEdge(node3, node4) == a.getEdge(node4, node3));
  REQUIRE(!a.edgeExists(node1, node5));
  REQUIRE(!a.edgeExists(node1, node1));
}

TEST_CASE("AnimeGraph::getAdjacentEdges Tests", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  Node* node = a.getNode(7);
  std::unordered_map<Node*, Edge*> edges = a.getAdjacentEdges(node);
  REQUIRE(edges.size() == 3);
  REQUIRE(edges.find(a.getNode(1)) != edges.end());
  REQUIRE(edges.find(a.getNode(6)) != edges.end());
  REQUIRE(edges.find(a.getNode(8)) != edges.end());
  REQUIRE(edges.find(a.getNode(7)) == edges.end());
}

TEST_CASE("KDTree::findNearestNeighbor Exact Tests", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  KDTree* tree = a.getTree();
  
  Node* test1 = new Node{21, "test1", std::vector<std::string> {"Action", "Adventure", "Comedy", "Drama", "Sci-Fi", "Space"}, 26, 8.82, 486824};
  Node* actual1 = a.getNode(1);
  REQUIRE(tree->findNearestNeighbor(test1) == actual1);
  
  Node* test2 = new Node{22, "test2", std::vector<std::string> {"Action, Comedy, Sci-Fi"}, 26, 8.32, 283069};
  Node* actual2 = a.getNode(6);
  REQUIRE(tree->findNearestNeighbor(test2) == actual2);

  Node* test3 = new Node{23, "test3", std::vector<std::string> {"Action, Drama, Magic, Mystery, Police, Supernatural"}, 26, 7.36, 64905};
  Node* actual3 = a.getNode(7);
  REQUIRE(tree->findNearestNeighbor(test3) == actual3);

  Node* test4 = new Node{24, "test4", std::vector<std::string> {"Action, Comedy, Shounen, Sports"}, 145, 8.08, 83648};
  Node* actual4 = a.getNode(15);
  REQUIRE(tree->findNearestNeighbor(test4) == actual4);
  
  delete test1;
  delete test2;
  delete test3;
  delete test4;
}

TEST_CASE("KDTree::findNearestNeighbor Closest Tests", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  KDTree* tree = a.getTree();
  
  Node* test1 = new Node{21, "test1", std::vector<std::string> {"Action", "Adventure", "Comedy"}, 25, 9.00, 486000};
  Node* actual1 = a.getNode(1);
  REQUIRE(tree->findNearestNeighbor(test1) == actual1);
  
  Node* test2 = new Node{22, "test2", std::vector<std::string> {"Action, Sci-Fi"}, 27, 8.00, 283000};
  Node* actual2 = a.getNode(6);
  REQUIRE(tree->findNearestNeighbor(test2) == actual2);

  Node* test3 = new Node{23, "test3", std::vector<std::string> {"Police, Supernatural"}, 26, 7.00, 64000};
  Node* actual3 = a.getNode(7);
  REQUIRE(tree->findNearestNeighbor(test3) == actual3);

  Node* test4 = new Node{24, "test4", std::vector<std::string> {"Shounen"}, 150, 8.00, 83000};
  Node* actual4 = a.getNode(15);
  REQUIRE(tree->findNearestNeighbor(test4) == actual4);

  delete test1;
  delete test2;
  delete test3;
  delete test4;
}
