#include "anime_graph.h"
#include <fstream>
#include <iostream>

/* Constructor and Deconstructor */

AnimeGraph::AnimeGraph() { 
    // TODO: Implement function
    adjacency_list = std::unordered_map<Node*, std::unordered_map<Node*, Edge*>>();
}

AnimeGraph::~AnimeGraph() { 
    // TODO: Implement function
}
    
/* Graph Creator */

void AnimeGraph::makeGraph(std::string anime_list_frame, std::string rating_list_frame) { 
    // TODO: Implement function
    importAnime(anime_list_frame);
    makeEdges(importRatings(rating_list_frame));
}
    
/* Graph Getters*/

// Returns the adjacent edges of a node. This function assumes the node exists within the graph
std::unordered_map<Node*, Edge*> AnimeGraph::getAdjacentEdges(Node* node) const { 
    return adjacency_list.at(node);
}

// Returns the edges of two nodes. This function assumes the node exists within the graph
Edge* AnimeGraph::getEdge(Node* first, Node* second) const {
    return adjacency_list.at(first).at(second);
}

// Return the node with the largest # of members. If two shows have the same # of members, the better rated shows gets taken.
// If the map is empty, returns NULL
Node* AnimeGraph::getMostPopular() const { 
    if (adjacency_list.empty()) { 
        return NULL;
    }

    auto it = adjacency_list.begin();
    Node* biggest = it->first;
    it++;

    for (; it != adjacency_list.end(); it++) {

        if (it->first->members == biggest->members) {
            if (it->first->rating > biggest->rating) {
                biggest = it->first;
            }
        }

        if (it->first->members > biggest->members) {
            biggest = it->first;
        }
    }
    
    return biggest;
}

// Returns the node associated with the specified anime_name. If it does not exist, return NULL
Node* AnimeGraph::getNode(std::string anime_name) const {
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++) {
        if (it->first->name == anime_name) {
            return it->first;
        }
    }
    return NULL;
}

// Returns the node associated with the specified anime_name. If it does not exist, return NULL
Node* AnimeGraph::getNode(unsigned anime_id) const { 
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++) {
        if (it->first->id == anime_id) {
            return it->first;
        }
    }
    return NULL;
}

/* Check existence of node or edge */

// Returns whether the node exists in adjacency_list
bool AnimeGraph::nodeExists(Node* node) const { 
    return (adjacency_list.find(node) != adjacency_list.end()); 
}

// Returns whether the edge between two nodes exists
bool AnimeGraph::edgeExists(Node* first, Node* second) const { 
    if (!nodeExists(first) || !nodeExists(second)) {
        return false;
    }

    return (adjacency_list.at(first).find(second) != adjacency_list.at(first).end());
}

/* Private Helpers */

void AnimeGraph::importAnime(std::string frame) { 
    // TODO: Implement function
    std::fstream f(frame);
    std::string line;
    std::getline(f, line); //skip first line
    while (std::getline(f, line)) {
        Node* anime = new Node;
        size_t pos1 = 0;
        size_t pos2 = line.find(",", pos1);
        anime->id = std::stoi(line.substr(pos1, pos2 - pos1));
        pos1 = pos2 + 1;
        pos2 = line.find(",", pos1);
        anime->name = line.substr(pos1, pos2 - pos1);
        pos1 = line.find("\"", pos1 + 1);
        pos2 = line.find_first_of(",\"", pos1 + 1);
        do {
            std::string genre = line.substr(pos1 + 1, pos2 - pos1 - 1);
            if (genre == "") {
                anime->genres.push_back("Default");
                pos1 = line.find("\"", pos1 + 1) + 1;
                break;
            }
            anime->genres.push_back(genre);
            pos1 = pos2 + 1;
            pos2 = line.find_first_of(",\"", pos1);
        } while (line[pos1] != ',');
        pos2 = line.find(",", pos1 + 1);
        std::string e = line.substr(pos1 + 1, pos2 - pos1 - 1);
        anime->episodes = (e != "Unknown") ? std::stoi(e) : -1;
        pos1 = pos2 + 1;
        pos2 = line.find(",", pos1);
        std::string r = line.substr(pos1, pos2 - pos1);
        anime->rating = (r != "") ? std::stod(r) : -1;
        pos1 = pos2 + 1;
        pos2 = line.find(",", pos1);
        anime->members = std::stoi(line.substr(pos1, pos2 - pos1));
        adjacency_list[anime] = std::unordered_map<Node*, Edge*>();
    }
}
std::unordered_map<int,std::vector<int>> AnimeGraph::importRatings(std::string frame) { 
        
    std::unordered_map<int, std::vector<int>> anime_ratings;
    
    std::fstream f(frame);
    std::string line;
    std::getline(f, line); 
    int userid;
    int animeid;
    while (std::getline(f, line)) {
        size_t pos1 = 0;
        size_t pos2 = line.find(",", pos1);
        userid = std::stoi(line.substr(pos1, pos2 - pos1));
        pos1 = pos2 + 1;
        pos2 = line.find(",", pos1);
        animeid = std::stoi(line.substr(pos1, pos2 - pos1));
        anime_ratings[animeid].push_back(userid);
    }
    
    return anime_ratings;
}

void AnimeGraph::makeEdges(std::unordered_map<int, std::vector<int>> anime_ratings) {
    for (auto pair1 : anime_ratings) {
        for (auto pair2 : anime_ratings) {
            if (pair1.first != pair2.first) {
                for (int user : pair1.second) {
                    if (std::find(pair2.second.begin(), pair2.second.end(), user) != pair2.second.end()) {
                        Node* anime1 = getNode(pair1.first);
                        Node* anime2 = getNode(pair2.first);
                        if (adjacency_list[anime1].find(anime2) != adjacency_list[anime1].end()) {
                            Edge* edge = adjacency_list[anime1][anime2];
                            edge->setWeight(edge->getWeight() + 1);
                        } else {
                            Edge* edge = new Edge (anime1, anime2, 1);
                            adjacency_list[anime1][anime2] = edge;
                        }
                    }
                }
            }
        }
    }
}
