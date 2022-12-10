#include <iostream>

#include "anime_graph.h"

int main() {
    AnimeGraph graph;
    graph.makeGraph("../data/anime-filtered.csv", "../data/rating-filtered.csv");
    // graph.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");

    graph.writeToCSV();

    std::string res;
    std::cout << "Would you like some recommendations? (y/n) ";
    std::cin >> res;
    if (res == "y" || res == "yes") {
        Node node;
        std::cout << "Please input some of the following information" << std::endl;

        std::cout << "ID: ";
        std::cin >> res;
        node.id = std::stoi(res);

        std::cout << "Name: ";
        std::cin >> node.name;

        std::cout << "Generes: ";
        std::cin >> res;
        
        std::cout << "Episodes: ";
        std::cin >> res;
        node.episodes = std::stoi(res);
        
        std::cout << "Rating: ";
        std::cin >> res;
        node.rating = std::stoi(res);
        
        std::cout << "Members: ";
        std::cin >> res;
        node.members = std::stoi(res);

        std::vector<std::string> recommendations = graph.findTop10Related(node);

        std::cout << "We recommend: " << std::endl;
        for (unsigned i = 0; i < recommendations.size(); ++i) {
            std::cout << i + 1 << ": " << recommendations.at(i) << std::endl;
        }
    }

    return 0;
}
