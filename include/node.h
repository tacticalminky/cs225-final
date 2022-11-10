#pragma once

/*

The struct for each node / show

*/

#include <string>
#include <vector>

struct Node {
    unsigned int id;
    std::string name;
    std::vector<std::string> genres;
    int episodes;
    double rating;
    unsigned int members;
     
    EdgeList neighbors;
};

// I know you need some sort of declartion of edge_list.h to put it in the struct,
// I just dont know where so im putting it here

#include "edge_list.h"
