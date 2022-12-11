#pragma once

/*

A single edge between two nodes

*/

class Edge {
    public:
        unsigned id_1;
        unsigned id_2;

        /**
         * @brief Construct a new Edge object
         * 
         * @param a 
         * @param b 
         * @param weight 
         */
        Edge(unsigned a, unsigned b, unsigned int weight) : id_1(a), id_2(b), weight_(weight) { }

        /**
         * @brief Get the weight of the edge
         * 
         * @return unsigned 
         */
        unsigned getWeight() const { return weight_; }

        /**
         * @brief Set the weight of the edge
         * 
         * @param weight 
         */
        void setWeight(int weight) { weight_ = weight; }

        /**
         * @brief overloaded <, smaller if edge has a smaller weight
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator< (const Edge& other) const { return weight_ < other.weight_; }
        
        /**
         * @brief overloaded >, larger if edge has a larger weight
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator> (const Edge& other) const { return weight_ > other.weight_; }

        /**
         * @brief overloaded ==, edges are equal if they contain the same ids
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator== (const Edge& other) const {
            if (id_1 == other.id_1 && id_2 == other.id_2) return true;
            if (id_1 == other.id_2 && id_2 == other.id_1) return true;
            return false;
        }

    private:
        unsigned weight_;
};
