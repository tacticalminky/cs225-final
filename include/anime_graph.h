#pragma once

/*

The graph of nodes and edges

*/

#include <unordered_map>

#include "node.h"
#include "edge.h"

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

    private:

    std::unordered_map<Node*, std::unordered_map<Node*, Edge*>> adjacency_list;
    std::unordered_map<int, std::vector<int>> animeidtouserid;
    

    void importAnime(std::string fname);
    void importRatings(std::string fname);
};

