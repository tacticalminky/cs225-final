#pragma once

/*

The doubly linked-list of edges

*/

#include "edge.h"

class EdgeList {
    public:

    void insert(Edge* edge);
    Edge* find(Edge* edge);
    Edge* find(Node* node); // How does this one work???

    private:

    struct EdgeListNode {
        Edge* edge;
        EdgeListNode* prev;
        EdgeListNode* next;
    };

    EdgeListNode* head_;
    EdgeListNode* tail_;
};
