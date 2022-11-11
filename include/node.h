#pragma once

/*

The struct for each node / show

*/

#include <string>
#include <vector>

#include "edge_list.h"

struct Node {
    unsigned int id;
    std::string name;
    std::vector<std::string> genres;
    int episodes;
    double rating;
    unsigned int members;
     
    EdgeList neighbors;
};
