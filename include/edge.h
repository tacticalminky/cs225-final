#pragma once

/*

A single edge between two nodes

*/

#include "node.h"

struct Edge { 
    Node* first;
    Node* second;
    unsigned int weight;
    unsigned int id;

    bool operator== (Edge const & other) const { return id == other.id; }
};
