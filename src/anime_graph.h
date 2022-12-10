#pragma once

/*

The graph of nodes and edges

*/

#include <unordered_map>
#include <vector>

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
        
        bool nodeExists(unsigned anime_id) const;
        bool edgeExists(unsigned id_1, unsigned id_2) const;

        std::vector<std::string> findTop10Related(Node query) const;

        KDTree* getTree() const;
        void writeToCSV() const;

        std::vector<unsigned> dfsSearch(Node node) const;

    private:
        std::unordered_map<unsigned, Node*> node_list;
        KDTree* tree;

        void importAnime(std::string fname);
        void importRatings(std::string fname);
        
        std::vector<unsigned> Node15(Node* query) const;
        std::vector<std::string> top10Related(Node* query) const;
};
