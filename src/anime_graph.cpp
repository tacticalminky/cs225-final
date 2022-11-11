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
}
    
/* Graph Getters*/

std::unordered_map<Node*, Edge*> AnimeGraph::getAdjacentEdges(Node* node) const { 
    // TODO: Implement function
}

Edge* AnimeGraph::getEdge(Node* first, Node* second) const { 
    // TODO: Implement function
}

Node* AnimeGraph::getMostPopular() const { 
    // TODO: Implement function
}

Node* AnimeGraph::getNode(std::string anime_name) const {
    // TODO: Implement function
}

Node* AnimeGraph::getNode(unsigned anime_id) const { 
    // TODO: Implement function
}

/* Check existence of node or edge */

bool AnimeGraph::nodeExists(Node* node) const { 
    // TODO: Implement function
}

bool AnimeGraph::edgeExists(Node* first, Node* second) const { 
    // TODO: Implement function
}

/* Private Helpers */
void AnimeGraph::importAnime(std::string frame) { 
    // TODO: Implement function
}
void AnimeGraph::importRatings(std::string frame) { 
    // TODO: Implement function
}
