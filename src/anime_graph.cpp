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

std::unordered_map<Node*, Edge*> AnimeGraph::getAdjacentEdges(Node* node) const { 
    // TODO: Implement function
    (void)node;
    return std::unordered_map<Node*, Edge*>();
}

Edge* AnimeGraph::getEdge(Node* first, Node* second) const { 
    // TODO: Implement function
    (void)first;
    (void)second;
    return new Edge(NULL, NULL, 0);
}

Node* AnimeGraph::getMostPopular() const { 
    // TODO: Implement function
    return new Node();
}

Node* AnimeGraph::getNode(std::string anime_name) const {
    // TODO: Implement function
    (void)anime_name;
    return new Node();
}

Node* AnimeGraph::getNode(unsigned anime_id) const { 
    // TODO: Implement function
    (void)anime_id;
    return new Node();
}

/* Check existence of node or edge */

bool AnimeGraph::nodeExists(Node* node) const { 
    // TODO: Implement function
    (void)node;
    return false;
}

bool AnimeGraph::edgeExists(Node* first, Node* second) const { 
    // TODO: Implement function
    (void)first;
    (void)second;
    return false;
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
