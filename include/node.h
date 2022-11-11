#pragma once

/*

The struct for each node / show

*/

#include <string>
#include <vector>

struct Node {
    unsigned id;
    std::string name;
    std::vector<std::string> genres;
    int episodes;
    double rating;
    unsigned members;
};
