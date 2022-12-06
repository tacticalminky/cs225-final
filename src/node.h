#pragma once

/*

The struct for each node / show

*/

#include <string>
#include <vector>

#include "edge.h"

struct Node {
    unsigned id;
    std::string name;
    std::vector<std::string> genres;
    int episodes;
    double rating;
    unsigned members;
    std::unordered_map<unsigned, Edge*> edges;
};
