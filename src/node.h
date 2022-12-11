#pragma once

#include <string>
#include <vector>

#include "edge.h"

/**
 * @brief Node structure representing an anime
 * id: id of the anime, used as key in maps
 * name: name of the anime
 * genres: list of the anime's genres
 * episodes: number of episodes
 * ratings: the anime's rating out of 10
 * members: the number of people who have rated the anime
 * 
 */
struct Node {
    unsigned id;
    std::string name;
    std::vector<std::string> genres;
    int episodes;
    double rating;
    unsigned members;
    std::unordered_map<unsigned, Edge*> edges;
};
