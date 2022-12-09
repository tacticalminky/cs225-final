#include "anime_graph.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stack>

/* Constructor and Deconstructor */

AnimeGraph::AnimeGraph() : tree(NULL) {
    node_list = std::unordered_map<unsigned, Node*>();
}

AnimeGraph::~AnimeGraph() { 
    for (auto& [id, node_ptr] : node_list) {
        for (auto& [id_other, edge_ptr] : node_ptr->edges) {
            delete edge_ptr;
            edge_ptr = NULL;
            
            node_list.at(id_other)->edges.erase(id);
        } 
        node_ptr->edges.clear();

        delete node_ptr;
        node_ptr = NULL;
    }
    node_list.clear();

    if (tree != NULL) {
        delete tree;
        tree = NULL;
    }
}
    
/* Graph Creator */

void AnimeGraph::makeGraph(std::string anime_list_frame, std::string rating_list_frame) {
    importAnime(anime_list_frame);
    importRatings(rating_list_frame);
    tree = new KDTree(node_list);
}
    
/* Graph Getters*/

// Returns the adjacent edges of a node. This function assumes the node exists within the graph
std::unordered_map<unsigned, Edge*> AnimeGraph::getAdjacentEdges(unsigned node) const {
    if (!nodeExists(node)) return std::unordered_map<unsigned, Edge*>();

    return node_list.at(node)->edges;
}

// Returns the edges of two nodes. This function assumes the node exists within the graph
Edge* AnimeGraph::getEdge(unsigned first, unsigned second) const {
    if (!edgeExists(first, second)) {
        return NULL;
    }

    return node_list.at(first)->edges.at(second);
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
    for (const auto& [id, node] : node_list) {
        if (node->name == anime_name) {
            return node;
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
bool AnimeGraph::nodeExists(unsigned anime_id) const { 
    return node_list.contains(anime_id); 
}

// Returns whether the edge between two nodes exists
bool AnimeGraph::edgeExists(unsigned id_1, unsigned id_2) const { 
    if (!nodeExists(id_1) || !nodeExists(id_2)) {
        return false;
    }

    return node_list.at(id_1)->edges.contains(id_2);
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

        anime->edges = std::unordered_map<unsigned, Edge*>();
        
        node_list[anime->id] = anime;
    }
}

void AnimeGraph::importRatings(std::string frame) { 
    std::vector<unsigned> animes;
    
    std::fstream f(frame);
    std::string line;
    std::getline(f, line); // skip first line
    unsigned curr_userid = 0;
    int count = 0;
    while (std::getline(f, line)) {
        if (count % 52836 == 0) {
            std::cout << "[";
            int pos = count / 52836;
            for (int i = 0; i < 99; ++i) {
                if (i < pos) std::cout << "=";
                else if (i == pos) std::cout << ">";
                else std::cout << " ";
            }
            std::cout << "] " << count / 52836 << "%\r";
            std::cout.flush();
        }

        size_t pos1 = 0;
        size_t pos2 = line.find(",", pos1);
        unsigned userid = std::stoi(line.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        pos2 = line.find(",", pos1);
        unsigned animeid = std::stoi(line.substr(pos1, pos2 - pos1));

        if (userid != curr_userid) {
            curr_userid = userid;
            animes.clear();
            animes.push_back(animeid);
        } else {
            for (unsigned anime : animes) {
                if (node_list[animeid]->edges.find(anime) != node_list[animeid]->edges.end()) {
                    Edge* edge = getEdge(animeid, anime);
                    edge->setWeight(edge->getWeight() + 1);
                } else {
                    Edge* edge = new Edge (animeid, anime, 1);
                    node_list[animeid]->edges[anime] = edge;
                    node_list[anime]->edges[animeid] = edge;
                }
            }
            animes.push_back(animeid);
        }
        ++count;
    }
    std::cout << std::endl;
}

std::vector<unsigned> AnimeGraph::dfsSearch(Node node) const {
    std::vector<unsigned> rec;
    std::stack<unsigned> stack;
    Node* first = getNode(node.id);
    if (first == NULL) first = getNode(node.name);
    if (first == NULL) first = tree->findNearestNeighbor(&node);
    rec.push_back(first->id);
    for (const auto& e : first->edges) stack.push(e.first);
    for (int i = 0; i < 9; i++) {
        if (stack.empty()) return rec;
        unsigned to_add = stack.top();
        stack.pop();
        while (std::find(rec.begin(), rec.end(), to_add) != rec.end()) {
            if (stack.empty()) return rec;
            to_add = stack.top();
            stack.pop();
        }
        rec.push_back(to_add);
        for (const auto& e : getNode(to_add)->edges) stack.push(e.first);
    }
    return rec;
}
