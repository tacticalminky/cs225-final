#pragma once

/*

A single edge between two nodes

*/

class Edge {
    public:
        unsigned id_1;
        unsigned id_2;

        Edge(unsigned a, unsigned b, unsigned int weight) : id_1(a), id_2(b), weight_(weight) { }

        unsigned getWeight() const { return weight_; }

        void setWeight(int weight) { weight_ = weight; }

        bool operator< (const Edge& other) const { return weight_ < other.weight_; }
        
        bool operator> (const Edge& other) const { return weight_ > other.weight_; }

        bool operator== (const Edge& other) const {
            if (id_1 == other.id_1 && id_2 == other.id_2) return true;
            if (id_1 == other.id_2 && id_2 == other.id_1) return true;
            return false;
        }

    private:
        unsigned weight_;
};
