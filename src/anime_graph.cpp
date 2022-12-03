#include "anime_graph.h"
#include <fstream>
#include <iostream>
#include <algorithm>

/* Constructor and Deconstructor */

AnimeGraph::AnimeGraph() : tree(NULL) { 
    // TODO: Implement function
    adjacency_list = std::unordered_map<Node*, std::unordered_map<Node*, Edge*>>();
}

AnimeGraph::~AnimeGraph() { 
    // TODO: Implement function
}
    
/* Graph Creator */

void AnimeGraph::makeGraph(std::string anime_list_frame, std::string rating_list_frame) {
    importAnime(anime_list_frame);
    std::unordered_map<unsigned, std::vector<unsigned>> anime_ratings = importRatings(rating_list_frame);

    unsigned count = 1;
    // for (const auto& [anime_id_1, user_ids_1] : anime_ratings) {
    for (auto iter_1 = anime_ratings.begin(); std::next(iter_1) != anime_ratings.end(); ++iter_1) {
    //     for (const auto& [anime_id_2, user_ids_2] : anime_ratings) {
        // std::cout << count << std::endl;
        for (auto iter_2 = std::next(iter_1); iter_2 != anime_ratings.end(); ++iter_2) {
            for (unsigned user : iter_1->second) {
                if (std::binary_search(iter_2->second.begin(), iter_2->second.end(), user)) {
                    Node* anime1 = getNode(iter_1->first);
                    Node* anime2 = getNode(iter_2->first);
                    if (edgeExists(anime1, anime2)) {
                        Edge* edge = getEdge(anime1, anime2);
                        edge->setWeight(edge->getWeight() + 1);
                    } else {
                        Edge* edge = new Edge (anime1, anime2, 1);
                        adjacency_list[anime1][anime2] = edge;
                        adjacency_list[anime2][anime1] = edge;
                    }
                }
            }
        }
        ++count;
    }

    tree = new KDTree(adjacency_list);
}
    
/* Graph Getters*/

// Returns the adjacent edges of a node. This function assumes the node exists within the graph
std::unordered_map<Node*, Edge*> AnimeGraph::getAdjacentEdges(Node* node) const {
    if (!nodeExists(node)) return std::unordered_map<Node*, Edge*>();

    return adjacency_list.at(node);
}

// Returns the edges of two nodes. This function assumes the node exists within the graph
Edge* AnimeGraph::getEdge(Node* first, Node* second) const {
    if (!edgeExists(first, second)) {
        return NULL;
    }

    return adjacency_list.at(first).at(second);
}

// Return the node with the largest # of members. If two shows have the same # of members, the better rated shows gets taken.
// If the map is empty, returns NULL
Node* AnimeGraph::getMostPopular() const { 
    if (node_list.empty()) { 
        return NULL;
    }

    Node* biggest = NULL;
    for (const auto& [id, node] : node_list) {
        if (!biggest) {
            biggest = node;
        } else if (node->members > biggest->members) {
            biggest = node;
        } else if (node->members == biggest->members && node->rating > biggest->rating) {
            biggest = node;
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
    if (!node_list.contains(anime_id)) return NULL;

    return node_list.at(anime_id);
}

// Returns a constant pointer to the KDTree
KDTree* AnimeGraph::getTree() const { return tree; }

/* Check existence of node or edge */

// Returns whether the node exists in adjacency_list
bool AnimeGraph::nodeExists(Node* node) const { 
    return node_list.contains(node->id); 
}

// Returns whether the edge between two nodes exists
bool AnimeGraph::edgeExists(Node* first, Node* second) const { 
    if (!nodeExists(first) || !nodeExists(second)) {
        return false;
    }

    return adjacency_list.at(first).contains(second);
}

/* Private Helpers */

void AnimeGraph::importAnime(std::string frame) {
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

        node_list[anime->id] = anime;
        adjacency_list[anime] = std::unordered_map<Node*, Edge*>();
    }
}

std::unordered_map<unsigned,std::vector<unsigned>> AnimeGraph::importRatings(std::string frame) { 
    std::unordered_map<unsigned, std::vector<unsigned>> anime_ratings;
    
    std::fstream f(frame);
    std::string line;
    std::getline(f, line); // skip first line
    while (std::getline(f, line)) {
        size_t pos1 = 0;
        size_t pos2 = line.find(",", pos1);
        unsigned userid = std::stoi(line.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        pos2 = line.find(",", pos1);
        unsigned animeid = std::stoi(line.substr(pos1, pos2 - pos1));

        anime_ratings[animeid].push_back(userid);
    }

    // sort each vector
    for (auto& [anime_id, user_ids] : anime_ratings) {
        std::sort(user_ids.begin(), user_ids.end());
    }
    
    return anime_ratings;
}
