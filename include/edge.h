#pragma once

/*

A single edge between two nodes

*/

#include "node.h"

class Edge {

    public:

    Node* first;
    Node* second;

    Edge(Node* a, Node* b, unsigned int weight) : first(a), second(b), weight_(weight) { }

    unsigned getWeight() const { return weight_; }

    bool operator< (const Edge& other) const { return weight_ < other.weight_; }

    bool operator== (const Edge& other) const {
        if (first->id == other.first->id && second->id == other.second->id) { return true; }
        if (first->id == other.second->id && second->id == other.first->id) { return true; }
        return false;
    }

    private:

    unsigned weight_;
};
