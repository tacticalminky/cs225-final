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

  Edge e1(n1->id, n2->id, 0);
  Edge e1_reverse(n2->id, n1->id, 0);
  Edge e2(n1->id, n3->id, 0);
  Edge e3(n2->id, n3->id, 0);

  REQUIRE(e1 == e1);
  REQUIRE(e1 == e1_reverse);
  REQUIRE_FALSE(e1 == e2);
  REQUIRE_FALSE(e1 == e3);
  REQUIRE_FALSE(e2 == e3);

  delete n1;
  delete n2;
  delete n3;
}

TEST_CASE("AnimeGraph::~AnimeGraph", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  REQUIRE_NOTHROW(a.~AnimeGraph());
}

TEST_CASE("AnimeGraph::importAnime Tests", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  REQUIRE(a.nodeExists(1));
  REQUIRE(a.nodeExists(6));
  REQUIRE(a.nodeExists(7));
  REQUIRE(a.nodeExists(8));
  REQUIRE(a.nodeExists(15));
  
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

TEST_CASE("AnimeGraph::makeGraph Tests", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  REQUIRE(a.edgeExists(1, 6));
  REQUIRE(a.getEdge(1, 6)->getWeight() == 2);
  REQUIRE(a.getEdge(1, 6) == a.getEdge(6, 1));
  REQUIRE(a.edgeExists(1, 7));
  REQUIRE(a.getEdge(1, 7)->getWeight() == 3);
  REQUIRE(a.getEdge(1, 7) == a.getEdge(7, 1));
  REQUIRE(a.edgeExists(1, 8));
  REQUIRE(a.getEdge(1, 8)->getWeight() == 1);
  REQUIRE(a.getEdge(1, 8) == a.getEdge(8, 1));
  REQUIRE(a.edgeExists(6, 7));
  REQUIRE(a.getEdge(6, 7)->getWeight() == 2);
  REQUIRE(a.getEdge(6, 7) == a.getEdge(7, 6));
  REQUIRE(a.edgeExists(7, 8));
  REQUIRE(a.getEdge(7, 8)->getWeight() == 1);
  REQUIRE(a.getEdge(7, 8) == a.getEdge(8, 7));
  REQUIRE(!a.edgeExists(1, 15));
  REQUIRE(!a.edgeExists(1, 1));
}

TEST_CASE("AnimeGraph::getAdjacentEdges Tests", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  std::unordered_map<unsigned, Edge*> edges = a.getAdjacentEdges(7);
  REQUIRE(edges.size() == 3);
  REQUIRE(edges.find(1) != edges.end());
  REQUIRE(edges.find(6) != edges.end());
  REQUIRE(edges.find(8) != edges.end());
  REQUIRE(edges.find(7) == edges.end());
}

TEST_CASE("KDTree::findNearestNeighbor Exact Tests", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  KDTree* tree = a.getTree();
  std::unordered_map<unsigned, Edge*> default_edges;
  
  Node* test1 = new Node{21, "test1", std::vector<std::string> {"Action", "Adventure", "Comedy", "Drama", "Sci-Fi", "Space"}, 26, 8.82, 486824, default_edges};
  Node* actual1 = a.getNode(1);
  REQUIRE(tree->findNearestNeighbor(test1) == actual1);
  
  Node* test2 = new Node{22, "test2", std::vector<std::string> {"Action, Comedy, Sci-Fi"}, 26, 8.32, 283069, default_edges};
  Node* actual2 = a.getNode(6);
  REQUIRE(tree->findNearestNeighbor(test2) == actual2);

  Node* test3 = new Node{23, "test3", std::vector<std::string> {"Action, Drama, Magic, Mystery, Police, Supernatural"}, 26, 7.36, 64905, default_edges};
  Node* actual3 = a.getNode(7);
  REQUIRE(tree->findNearestNeighbor(test3) == actual3);

  Node* test4 = new Node{24, "test4", std::vector<std::string> {"Action, Comedy, Shounen, Sports"}, 145, 8.08, 83648, default_edges};
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
  std::unordered_map<unsigned, Edge*> default_edges;
  
  Node* test1 = new Node{21, "test1", std::vector<std::string> {"Action", "Adventure", "Comedy"}, 25, 9.00, 486000, default_edges};
  Node* actual1 = a.getNode(1);
  REQUIRE(tree->findNearestNeighbor(test1) == actual1);
  
  Node* test2 = new Node{22, "test2", std::vector<std::string> {"Action, Sci-Fi"}, 27, 8.00, 283000, default_edges};
  Node* actual2 = a.getNode(6);
  REQUIRE(tree->findNearestNeighbor(test2) == actual2);

  Node* test3 = new Node{23, "test3", std::vector<std::string> {"Police, Supernatural"}, 26, 7.00, 64000, default_edges};
  Node* actual3 = a.getNode(7);
  REQUIRE(tree->findNearestNeighbor(test3) == actual3);

  Node* test4 = new Node{24, "test4", std::vector<std::string> {"Shounen"}, 150, 8.00, 83000, default_edges};
  Node* actual4 = a.getNode(15);
  REQUIRE(tree->findNearestNeighbor(test4) == actual4);

  delete test1;
  delete test2;
  delete test3;
  delete test4;
}

TEST_CASE("AnimeGraph::dfsSearch Tests", "") {
  AnimeGraph a;
  a.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");
  std::unordered_map<unsigned, Edge*> default_edges;
  Node test1{0, "Cowboy Bebop", std::vector<std::string>(), 0, 0, 0, default_edges};
  std::vector<unsigned> rec = a.dfsSearch(test1);
  REQUIRE(rec.size() == 4);
  REQUIRE(rec[0] == 1);
  REQUIRE(rec[1] == 6);
  REQUIRE(rec[2] == 7);
  REQUIRE(rec[3] == 8);

  Node test2{0, "", std::vector<std::string> {"Action", "Adventure", "Comedy"}, 25, 9.00, 486000, default_edges};
  std::vector<unsigned> rec2 = a.dfsSearch(test2);
  REQUIRE(rec2.size() == 4);
  REQUIRE(rec2[0] == 1);
  REQUIRE(rec2[1] == 6);
  REQUIRE(rec2[2] == 7);
  REQUIRE(rec2[3] == 8);
}
