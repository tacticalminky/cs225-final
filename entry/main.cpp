#include <iostream>

#include "anime_graph.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Please use as: " << argv[0] << " [anime-list] [ratings-list]" << std::endl;
        return 1;
    }

    AnimeGraph graph;
    graph.makeGraph(argv[1], argv[2]);
    
    std::cout << "Press [Enter] to continue" << std::endl;

    std::cin.ignore();

    std::string res;
    std::cout << "Would you like some recommendations? (y/n) ";
    std::cin >> res;
    while (res == "y" || res == "yes") {
        std::cin.clear();
        res.clear();
        
        Node node;

        std::cout << std::endl << "Please input some of the following information" << std::endl;

        std::cout << "Enter in a numerical number or just press enter." << std::endl;
        std::cout << "ID: ";
        std::getline(std::cin, res);
        node.id = (res != "") ? std::stoul(res) : 0;
        res.clear();

        std::cout << "Name: ";
        std::getline(std::cin, node.name);

        std::cout << "List the generes capitalized and separated only by a space" << std::endl;
        std::getline(std::cin, res);

        size_t pos_1 = 0;
        while (pos_1 != res.length()) {
            size_t pos_2 = res.find(' ', pos_1);
            if (pos_2 == std::string::npos) pos_2 = res.length();
            node.genres.push_back(res.substr(pos_1, pos_2 - 1));
            std::cout << node.genres.front() << std::endl;
            pos_1 = pos_2;
        }
        res.clear();
        
        std::cout << "Enter in a numerical number for the following or just press enter." << std::endl;
        std::cout << "Episodes: ";
        std::getline(std::cin, res);
        node.episodes = (res != "") ? std::stoi(res) : 0;
        res.clear();
        
        std::cout << "Rating: ";
        std::getline(std::cin, res);
        node.rating = (res != "") ? std::stod(res) : 0;
        res.clear();
        
        std::cout << "Members: ";
        std::getline(std::cin, res);
        node.members = (res != "") ? std::stoul(res) : 0;
        res.clear();

        std::cout << std::endl << "One moment Please." << std::endl << std::endl;

        std::vector<std::string> top10 = graph.findTop10Related(node);
        std::vector<std::string> top10_dfs = graph.dfsSearch(node);

        std::cout << "We recommend: " << std::endl;
        for (unsigned i = 0; i < top10.size(); ++i) {
            std::cout << i + 1 << ": " << top10.at(i) << std::endl;
        }
        std::cout << std::endl;

        std::cout << "You might also like: " << std::endl;
        for (unsigned i = 0; i < top10_dfs.size(); ++i) {
            std::cout << i + 1 << ": " << top10_dfs.at(i) << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Would you like another recommendations? (y/n) ";
        std::cin >> res;
    }
    std::cout << std::endl;

    graph.writeToCSV();
    
    return 0;
}
