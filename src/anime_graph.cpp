#include "anime_graph.h"

/* Constructor and Deconstructor */

AnimeGraph::AnimeGraph() { 
    // TODO: Implement function
}

AnimeGraph::~AnimeGraph() { 
    // TODO: Implement function
}
    
/* Graph Creator */

void AnimeGraph::makeGraph(std::string anime_list_frame, std::string rating_list_frame) { 
    // TODO: Implement function
    (void)anime_list_frame;
    (void)rating_list_frame;
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
    (void)frame;
}
void AnimeGraph::importRatings(std::string frame) { 
    // TODO: Implement function
    (void)frame;
}
