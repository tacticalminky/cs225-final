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
        std::cout << std::endl << "Please input some of the following information" << std::endl;

        std::cout << "For the folowing please put in a number or 0" << std::endl;
        
        std::cout << "ID: ";
        std::cin >> res;
        node.id = std::stoul(res);

        std::cout << "Name: ";
        std::cin >> node.name;

        std::cout << "List the generes capitalized and separated only by a space" << std::endl;
        std::cin >> res;

        size_t pos_1 = 0;
        while (res != "\n" && pos_1 != res.length()) {
            size_t pos_2 = res.find(' ', pos_1);
            node.genres.push_back(res.substr(pos_1, pos_2));
            pos_1 = pos_2;
        }
        
        std::cout << "For the folowing please put in a number or 0" << std::endl;

        std::cout << "Episodes: ";
        std::cin >> res;
        node.episodes = std::stoi(res);
        
        std::cout << "Rating: ";
        std::cin >> res;
        node.rating = std::stod(res);
        
        std::cout << "Members: ";
        std::cin >> res;
        node.members = std::stoul(res);

        std::cout << "One moment Please." << std::endl;

        std::vector<std::string> recommendations = graph.findTop10Related(node);

        std::cout << "We recommend: " << std::endl;
        for (unsigned i = 0; i < recommendations.size(); ++i) {
            std::cout << i + 1 << ": " << recommendations.at(i) << std::endl;
        }
    }

    return 0;
}
