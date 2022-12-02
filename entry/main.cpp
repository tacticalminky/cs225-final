#include "anime_graph.h"
#include <iostream>

int main() {
    AnimeGraph graph;
    graph.makeGraph("../data/anime-filtered.csv", "../data/rating-filtered.csv");
    return 0;
}
