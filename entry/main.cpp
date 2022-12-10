#include "anime_graph.h"
#include <iostream>

int main() {
    AnimeGraph graph;
    graph.makeGraph("../data/anime-filtered.csv", "../data/rating-filtered.csv");
    // graph.makeGraph("../tests/data/test_anime.csv", "../tests/data/test_rating.csv");

    graph.writeToCSV();
    return 0;
}
