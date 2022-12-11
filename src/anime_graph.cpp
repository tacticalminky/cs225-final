#include "anime_graph.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

/* Constructor and Deconstructor */

/**
 * @brief Construct a new Anime Graph:: Anime Graph object
 * 
 */
AnimeGraph::AnimeGraph() : tree(NULL) {
    node_list = std::unordered_map<unsigned, Node*>();
}

/**
 * @brief Destroy the Anime Graph:: Anime Graph object
 * For every node: destroy edges, set other instance of edge to NULL, destroy node
 * 
 */
AnimeGraph::~AnimeGraph() {
    for (auto& [id, node_ptr] : node_list) {
        for (auto& [id_other, edge_ptr] : node_ptr->edges) {
            if (edge_ptr != NULL) {
                delete edge_ptr;
                edge_ptr = NULL;
                
                node_list.at(id_other)->edges.at(id) = NULL;
            }
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

/**
 * @brief takes two csv paths and passes them to importAnime and importRatings, then makes a KDTree from all the nodes
 * 
 * @param anime_list_frame 
 * @param rating_list_frame 
 */
void AnimeGraph::makeGraph(std::string anime_list_frame, std::string rating_list_frame) {
    importAnime(anime_list_frame);
    importRatings(rating_list_frame);
    tree = new KDTree(node_list);
}
 
/* Graph Getters*/

/**
 * @brief finds the map of all edges from a node
 * 
 * @param node 
 * @return std::unordered_map<unsigned, Edge*> 
 */
std::unordered_map<unsigned, Edge*> AnimeGraph::getAdjacentEdges(unsigned node) const {
    if (!nodeExists(node)) return std::unordered_map<unsigned, Edge*>();

    return node_list.at(node)->edges;
}

/**
 * @brief finds the pointer to an edge between two nodes
 * 
 * @param first 
 * @param second 
 * @return Edge* 
 */
Edge* AnimeGraph::getEdge(unsigned first, unsigned second) const {
    if (!edgeExists(first, second)) {
        return NULL;
    }

    return node_list.at(first)->edges.at(second);
}

/**
 * @brief returns the node with the most members, or better rated if tie
 * 
 * @return Node* 
 */
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

/**
 * @brief searches node_list for a node with the given name
 * 
 * @param anime_name 
 * @return Node* 
 */
Node* AnimeGraph::getNode(std::string anime_name) const {
    for (const auto& [id, node] : node_list) {
        if (node->name == anime_name) {
            return node;
        }
    }
    return NULL;
}

/**
 * @brief finds the pointer to the anime node with the given id
 * 
 * @param anime_id 
 * @return Node* 
 */
Node* AnimeGraph::getNode(unsigned anime_id) const {
    if (!node_list.contains(anime_id)) return NULL;

    return node_list.at(anime_id);
}

/**
 * @brief return a constatn pointer to the KDTree
 * 
 * @return KDTree* 
 */
KDTree* AnimeGraph::getTree() const { return tree; }

/* Check existence of node or edge */

/**
 * @brief return whether a node with the given id exists in node_list
 * 
 * @param anime_id 
 * @return true 
 * @return false 
 */
bool AnimeGraph::nodeExists(unsigned anime_id) const { 
    return node_list.contains(anime_id); 
}

/**
 * @brief return whether an edge between two nodes exists
 * 
 * @param id_1 
 * @param id_2 
 * @return true 
 * @return false 
 */
bool AnimeGraph::edgeExists(unsigned id_1, unsigned id_2) const { 
    if (!nodeExists(id_1) || !nodeExists(id_2)) {
        return false;
    }

    return node_list.at(id_1)->edges.contains(id_2);
}

/**
 * @brief finds the graph node closest to the query and the 9 most related nodes
 * 
 * @param query 
 * @return std::vector<std::string> 
 */
std::vector<std::string> AnimeGraph::findTop10Related(Node query) const {
    Node* potential_query = getNode(query.id);
    if (potential_query == NULL) potential_query = getNode(query.name);
    if (potential_query == NULL) {
        potential_query = tree->findNearestNeighbor(&query); // should also include query
        std::vector<std::string> ret;
        ret.push_back(potential_query->name);
        for (const std::string& s : top10Related(potential_query)) ret.push_back(s);
        if (ret.size() > 10) ret.pop_back();
        return ret;
    }
    
    return top10Related(potential_query);
}

/* Private Helpers */

/**
 * @brief parses each line of a given csv into a Node inserted into node_list
 * 
 * @param frame 
 */
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

/**
 * @brief parses the ratings of a given csv into graph Edges
 * NOTE: csv must be sorted by userid
 * 
 * @param frame 
 */
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

/* Output the graph to CSV */

/**
 * @brief finds the 15 highest weighted edges of a given node
 * 
 * @param query 
 * @return std::vector<unsigned> 
 */
std::vector<unsigned> AnimeGraph::Node15(Node* query) const {
    std::priority_queue<Edge> queue;  // Queue to keep the output ordered
    for (const auto& [id, edge] : query->edges) queue.push(*edge);
    
    std::vector<unsigned> ret;  // Iterated every elements in node->edges to find the top15 weighted shows
    unsigned top_num = (queue.size() >= 15) ? 15 : queue.size();
    for (unsigned i = 0; i < top_num; ++i) {
        unsigned curr_id = (queue.top().id_1 != query->id) ? queue.top().id_1 : queue.top().id_2;
        queue.pop();
        ret.push_back(getNode(curr_id)->id);
    }

    return ret;
}

/**
 * @brief writes every node and its closest 15 neighbors to output-graph.csv
 * 
 */
void AnimeGraph::writeToCSV() const {
    
    // Opening the write-to-file
    std::ofstream outputGraph;
    outputGraph.open("../data/output-graph.csv");
    if (!outputGraph.is_open()) {
        std::cout << "Issue with opening / creating the file" << std::endl;
        return;
    }

    // First Line
    outputGraph << "id,name,genres,episodes,rating,members,top_related_id,weight" << std::endl;

    // Write from NODE_DATA,"top1_id,weight1,top2_id,weight2... top15_name,weight15,"
    // Only writing top15_id to cut runtime and to highlights connected components better
    // NODE_DATA will be similar to the anime-filtered.csv file
    for (auto nodes : node_list) {
        Node* node = nodes.second;

        // Push NODE_DATA
        outputGraph << node->id; // id
        outputGraph << ',' << node->name << ',' << '"'; // name
        for (unsigned x = 0; x < node->genres.size(); x++) { // genres :)
            if (x == 0) { outputGraph <<  node->genres[x]; continue; }
            outputGraph << ", " << node->genres[x];
        }
        outputGraph << '"' << ',' << node->episodes; // episodes
        outputGraph << ',' << node->rating; // rating
        outputGraph << ',' << node->members; // members

        // Write top_related_id and weight
        std::vector<unsigned> top15 = Node15(node);

        if (!top15.empty()) {
            outputGraph << ',' << '"';
            bool first = true;
            for (auto point : top15) {
                
                unsigned w = node->edges.at(point)->getWeight();

                if (first) { 
                    outputGraph << point << ',' << w;
                    first = false;
                    continue;
                }
                outputGraph << ',' << point << ',' << w;
            }
            outputGraph << '"';
        }

        outputGraph << '\n';
    }
    std::cout << "Finished writing" << std::endl;  // Lets the user know the code has finished writing the CSV and closes the file
    outputGraph.close();
}

/**
 * @brief traverses the graph using Prim's Algorithm with distance decay to find a node and its 9 closest related nodes
 * 
 * @param query 
 * @return std::vector<std::string> 
 */
std::vector<std::string> AnimeGraph::top10Related(Node* query) const {
    std::unordered_map<unsigned, unsigned> visited;
    for (const auto& [id, node] : node_list) visited[id] = 0;
    visited[query->id] = -1;

    auto cost = [&query, &visited, this] (unsigned id_1, unsigned id_2) {
        if (id_1 == query->id) return getEdge(query->id, id_2)->getWeight();
        if (id_2 == query->id) return getEdge(query->id, id_1)->getWeight();

        unsigned prev_weight = (visited.at(id_1) != 0) ? visited.at(id_1) : visited.at(id_2);

        return (prev_weight + getEdge(id_1, id_2)->getWeight()) / 2;
    };

    std::priority_queue<Edge> queue;
    for (const auto& [id, edge] : query->edges) queue.push(*edge);
    
    std::vector<Edge> top_edges;
    unsigned top_num = (queue.size() >= 10) ? 10 : queue.size();
    for (unsigned i = 0; i < top_num; ++i) {
        top_edges.push_back(queue.top());
        queue.pop();
    }

    for (const Edge& edge : top_edges) {
        queue.push(edge);
        
        unsigned curr_id = (edge.id_1 != query->id) ? edge.id_1 : edge.id_2;
        Node* node = getNode(curr_id);
        
        visited.at(curr_id) = getEdge(query->id, curr_id)->getWeight();
        
        for (const auto& [id, edge] : node->edges) {
            if (id != query->id) {
                Edge e = *edge;
                e.setWeight(cost(e.id_1, e.id_2));
                if (e.id_1 == curr_id) e.id_1 = query->id;
                else if (e.id_2 == curr_id) e.id_2 = query->id;
                
                // if this edge exists, update it
                auto loc = std::find(top_edges.begin(), top_edges.end(), e);
                if (loc != top_edges.end()) {
                    if (e.getWeight() > (*loc).getWeight()) {
                        (*loc).setWeight(e.getWeight());
                    }
                } else {
                    queue.push(e);
                }
            }
        }
    }
    
    std::vector<std::string> ret;
    top_num = (queue.size() >= 10) ? 10 : queue.size();
    for (unsigned i = 0; i < top_num; ++i) {
        unsigned curr_id = (queue.top().id_1 != query->id) ? queue.top().id_1 : queue.top().id_2;
        queue.pop();
        ret.push_back(getNode(curr_id)->name);
    }
    
    return ret;
}

/**
 * @brief finds the closest node to a query node and uses DFS to find a path from there spanning 10 nodes
 * 
 * @param node 
 * @return std::vector<unsigned> 
 */
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
