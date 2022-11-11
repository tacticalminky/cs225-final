#pragma once

/*

The graph of nodes and edges

*/

#include "node.h"
#include "edge.h"

#include <unordered_map>

class AnimeGraph {

    public:

    AnimeGraph();
    ~AnimeGraph();
    
    void makeGraph(std::string anime_list_frame, std::string rating_list_frame);

    std::unordered_map<Node*, Edge*> getAdjacentEdges(Node* node) const;
    Edge* getEdge(Node* first, Node* second) const;
    Node* getMostPopular() const;
    Node* getNode(std::string anime_name) const;
    Node* getNode(unsigned anime_id) const; 

    bool nodeExists(Node* node) const;
    bool edgeExists(Node* first, Node* second) const;

    private:

    std::unordered_map<Node*, std::unordered_map<Node*, Edge*>> adjacency_list;

    void importAnime(std::string frame);
    void importRatings(std::string frame);
};
