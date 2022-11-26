#pragma once

#include <unordered_map>
#include <vector>

#include "anime_graph.h"

class KDTree {
    public:
        KDTree(const std::unordered_map<Node*, std::unordered_map<Node*, Edge*>>& adjacency_list);
        KDTree(const KDTree& other);
        KDTree const& operator=(const KDTree& other);
        ~KDTree();
        Node* findNearestNeighbor(const Node* query) const;

    private:
        struct TreeNode {
            Node* anime;
            TreeNode* left;
            TreeNode* right;

            TreeNode() : anime(NULL), left(NULL), right(NULL) {}
            TreeNode(Node* anime) : anime(anime), left(NULL), right(NULL) {}
        };

        TreeNode* root;
        size_t size;

        int partition(vector<Node*>& arr, int start, int end, int p_idx, int d);
        int median(vector<Node*>& arr, int start, int end, int k, int d);
        void buildTree(vector<Node*>& arr, int start, int end, int d, TreeNode*& curr);
        void buildCopy(TreeNode*& curr, const TreeNode* other);
        void deleteNode(TreeNode*& root);
        Node* findNearestNeighbor(const Node*& query, int d, TreeNode* curr) const;
        bool shouldReplace(const Node*& target, const Node*& currentBest, const Node*& potential) const;
        bool smallerDimVal(const Node*& first, const Node*& second, int curDim) const;
}