#pragma once

/*

The graph of nodes and edges

*/

#include "node.h"
#include "edge.h"

#include <list>

class Graph {

    public:

    private:
    std::vector<Node*> vertices;
    std::list<Edge*> edges;

};
