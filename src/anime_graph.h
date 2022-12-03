#pragma once

/*

The graph of nodes and edges

*/

#include <unordered_map>

#include "node.h"
#include "edge.h"
#include "kdtree.h"

// typedef std::unordered_map<Node*, Edge*> EdgeList;
// typedef std::unordered_map<Node*, EdgeList> AdjacencyList;

class AnimeGraph {

    public:
        AnimeGraph();
        ~AnimeGraph();
        
        void makeGraph(std::string anime_list_fname, std::string rating_list_fname);

        std::unordered_map<Node*, Edge*> getAdjacentEdges(Node* node) const;
        Edge* getEdge(Node* first, Node* second) const;
        Node* getMostPopular() const;
        Node* getNode(std::string anime_name) const;
        Node* getNode(unsigned anime_id) const; 
        
        bool nodeExists(Node* node) const;
        bool edgeExists(Node* first, Node* second) const;

        KDTree* getTree() const;

    private:
        std::unordered_map<unsigned, Node*> node_list;
        std::unordered_map<Node*, std::unordered_map<Node*, Edge*>> adjacency_list;
        KDTree* tree;

        void importAnime(std::string fname);

        /**
         * @brief 
         * 
         * @param fname filename of ratings.csv
         * @return map of anime ids to list of user ids
         */
        std::unordered_map<unsigned, std::vector<unsigned>> importRatings(std::string fname);
};

