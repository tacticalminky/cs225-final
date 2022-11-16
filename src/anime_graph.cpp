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
void AnimeGraph::importRatings(std::string frame) { 
    // TODO: Implement function
    (void)frame;
}
