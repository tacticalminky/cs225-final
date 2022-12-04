#pragma once

/*

The graph of nodes and edges

*/

#include <unordered_map>

#include "node.h"
#include "edge.h"
#include "kdtree.h"

class AnimeGraph {

    public:
        AnimeGraph();
        ~AnimeGraph();
        
        void makeGraph(std::string anime_list_fname, std::string rating_list_fname);

        std::unordered_map<unsigned, Edge*> getAdjacentEdges(unsigned node) const;
        Edge* getEdge(unsigned first, unsigned second) const;
        Node* getMostPopular() const;
        Node* getNode(std::string anime_name) const;
        Node* getNode(unsigned anime_id) const; 
        
        bool nodeExists(unsigned node) const;
        bool edgeExists(unsigned first, unsigned second) const;

        KDTree* getTree() const;

    private:
        std::unordered_map<unsigned, Node*> adjacency_list;
        KDTree* tree;

        void importAnime(std::string fname);

        /**
         * @brief 
         * 
         * @param fname filename of ratings.csv
         * @return map of anime ids to list of user ids
         */
        void importRatings(std::string fname);
};

