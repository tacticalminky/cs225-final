#include "anime_graph.h"
#include <iostream>

int main() {
    AnimeGraph a;
    a.makeGraph("/workspaces/cs225/final/cs225-final/data/anime-filtered.csv", "");
    std::cout << a.adjacency_list.size() << std::endl;
    // for (auto entry : a.adjacency_list) {
    //     std::cout << entry.first->id << std::endl;
    //     std::cout << entry.first->name << std::endl;
    //     for (std::string genre : entry.first->genres) std::cout << genre << ", ";
    //     std::cout << std::endl;
    //     std::cout << entry.first->episodes << std::endl;
    //     std::cout << entry.first->rating << std::endl;
    //     std::cout << entry.first->members << std::endl;
    //     std::cout << std::endl;
    // }
    return 0;
}
