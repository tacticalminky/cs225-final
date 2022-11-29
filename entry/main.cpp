#include "anime_graph.h"
#include <iostream>

int main() {
    AnimeGraph a;
    a.makeGraph("../data/test_anime.csv", "../data/test_rating.csv");
    std::cout << "here" << std::endl;
    Node* anime1 = a.getNode(1);
    Node* anime2 = a.getNode(6);
    Node* anime3 = a.getNode(7);
    Node* anime4 = a.getNode(8);
    Node* anime5 = a.getNode(15);
    if (a.edgeExists(anime1, anime2)) std::cout << "1 6 " << (a.getEdge(anime1, anime2)->getWeight()) << ' ' << (a.getEdge(anime2, anime1)->getWeight()) << std::endl;
    if (a.edgeExists(anime1, anime3)) std::cout << "1 7 " <<(a.getEdge(anime1, anime3)->getWeight()) << ' ' << (a.getEdge(anime3, anime1)->getWeight()) << std::endl;
    if (a.edgeExists(anime1, anime4)) std::cout << "1 8 " <<(a.getEdge(anime1, anime4)->getWeight()) << ' ' << (a.getEdge(anime4, anime1)->getWeight()) << std::endl;
    if (a.edgeExists(anime1, anime5)) std::cout << "1 15 " <<(a.getEdge(anime1, anime5)->getWeight()) << ' ' << (a.getEdge(anime5, anime1)->getWeight()) << std::endl;
    std::cout << std::endl;
    if (a.edgeExists(anime2, anime3)) std::cout << "6 7 " <<(a.getEdge(anime2, anime3)->getWeight()) << ' ' << (a.getEdge(anime3, anime2)->getWeight()) << std::endl;
    if (a.edgeExists(anime2, anime4)) std::cout << "6 8 " <<(a.getEdge(anime2, anime4)->getWeight()) << ' ' << (a.getEdge(anime4, anime2)->getWeight()) << std::endl;
    if (a.edgeExists(anime2, anime5)) std::cout << "6 15 " <<(a.getEdge(anime2, anime5)->getWeight()) << ' ' << (a.getEdge(anime5, anime2)->getWeight()) << std::endl;
    std::cout << std::endl;
    if (a.edgeExists(anime3, anime4)) std::cout << "7 8 " <<(a.getEdge(anime3, anime4)->getWeight()) << ' ' << (a.getEdge(anime4, anime3)->getWeight()) << std::endl;
    if (a.edgeExists(anime3, anime5)) std::cout << "7 15 " <<(a.getEdge(anime3, anime5)->getWeight()) << ' ' << (a.getEdge(anime5, anime3)->getWeight()) << std::endl;
    std::cout << std::endl;
    if (a.edgeExists(anime4, anime5)) std::cout << "8 15 " <<(a.getEdge(anime4, anime5)->getWeight()) << ' ' << (a.getEdge(anime5, anime4)->getWeight()) << std::endl;
    return 0;
}
