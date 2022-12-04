#pragma once

/*

A single edge between two nodes

*/

class Edge {

    public:

    unsigned first;
    unsigned second;

    Edge(unsigned a, unsigned b, unsigned int weight) : first(a), second(b), weight_(weight) { }

    unsigned getWeight() const { return weight_; }

    void setWeight(int weight) { weight_ = weight; }

    bool operator< (const Edge& other) const { return weight_ < other.weight_; }

    bool operator== (const Edge& other) const {
        if (first == other.first && second == other.second) { return true; }
        if (first == other.second && second == other.first) { return true; }
        return false;
    }

    private:

    unsigned weight_;
};
