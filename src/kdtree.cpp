#include <algorithm>

#include "kdtree.h"

KDTree::KDTree(const std::unordered_map<unsigned, Node*>& adjacency_list) {
    if (adjacency_list.empty()) {
      root = nullptr;
      size = 0;
      return;
    }
    std::vector<Node*> points;
    for (auto pair : adjacency_list) points.push_back(pair.second);
    buildTree(points, 0, points.size() - 1, 0, root);
    size = adjacency_list.size();
}

KDTree::KDTree(const KDTree& other) {
    buildCopy(root, other.root);
    size = other.size;
}

KDTree const& KDTree::operator=(const KDTree& other) {
    if (this->root == other.root) return *this;
    this->~KDTree();
    *this = KDTree(other);
    return *this;
}

KDTree::~KDTree() {
    size = 0;
    deleteNode(root);
}

Node* KDTree::findNearestNeighbor(const Node* query) const { return findNearestNeighbor(query, 0, root); }

int KDTree::partition(std::vector<Node*>& arr, int start, int end, int p_idx, int d) {
    Node* pivot_value = arr[p_idx];
    Node* temp = arr[end];
    arr[end] = arr[p_idx];
    arr[p_idx] = temp;
    int idx = start;
    for (int i = start; i < end; i++) {
        if (smallerDimVal(arr[i], pivot_value, d)) {
        Node* t = arr[i];
        arr[i] = arr[idx];
        arr[idx] = t;
        idx++;
        }
    }
    temp = arr[end];
    arr[end] = arr[idx];
    arr[idx] = temp;
    return idx;
}

int KDTree::median(std::vector<Node*>& arr, int start, int end, int k, int d) {
    if (start == end) return start;
    int p_idx = k;
    p_idx = partition(arr, start, end, p_idx, d);
    if (k == p_idx) return k;
    if (k < p_idx) return median(arr, start, p_idx - 1, k, d);
    return median(arr, p_idx + 1, end, k, d);
}

void KDTree::buildTree(std::vector<Node*>& arr, int start, int end, int d, TreeNode*& curr) {
    if (start <= end) {
    int middle = median(arr, start, end, (start+end)/2, d);
    curr = new TreeNode(arr[middle]);
    d = (d + 1) % 4;
    buildTree(arr, start, middle - 1, d, curr->left);
    buildTree(arr, middle + 1, end, d, curr->right);
  } else {
    curr = nullptr;
  }
}

void KDTree::buildCopy(TreeNode*& curr, const TreeNode* other) {
    if (other != NULL) {
    curr = new TreeNode(other->anime);
    buildCopy(curr->left, other->left);
    buildCopy(curr->right, other->right);
    } else {
        curr = NULL;
    }
}

void KDTree::deleteNode(TreeNode*& root) {
    if (root) {
    deleteNode(root->left);
    deleteNode(root->right);
    delete root;
    root = NULL;
  }
}

Node* KDTree::findNearestNeighbor(const Node* query, int d, TreeNode* curr) const {
    if (!curr->left && !curr->right) return curr->anime;
    int next_d = (d + 1) % 4;
    Node* nearest = curr->anime;
    if (smallerDimVal(query, curr->anime, d) && curr->left) nearest = findNearestNeighbor(query, next_d, curr->left);
    else if (!smallerDimVal(query, curr->anime, d) && curr->right) nearest = findNearestNeighbor(query, next_d, curr->right);
    if (shouldReplace(query, nearest, curr->anime)) nearest = curr->anime;
    double radius = getRadius(query, nearest);
    double splitDist = getSplitDist(query, curr->anime, d);
    if (radius >= splitDist) {
        Node* temp = curr->anime;
        if (smallerDimVal(query, curr->anime, d) && curr->right) temp = findNearestNeighbor(query, next_d, curr->right);
        else if (!smallerDimVal(query, curr->anime, d) && curr->left) temp = findNearestNeighbor(query, next_d, curr->left);
        if (shouldReplace(query, nearest, temp)) nearest = temp;
    }
    return nearest;
}

bool KDTree::shouldReplace(const Node* target, const Node* currentBest, const Node* potential) const {
    double curr_dist = getRadius(target, currentBest);
    double new_dist = getRadius(target, potential);
    return ((curr_dist != new_dist) ? new_dist < curr_dist : potential < currentBest);
}

bool KDTree::smallerDimVal(const Node* first, const Node* second, int curDim) const {
    switch(curDim) {
        case 0:
            for (std::string genre : first->genres) if (std::find(second->genres.begin(), second->genres.end(), genre) != second->genres.end()) return true;
            return false;
        case 1:
            return first->episodes < second->episodes;
        case 2:
            return first->rating < second->rating;
        case 3: 
            return first->members < second->members;
    }
    return false;
}

double KDTree::getRadius(const Node* node1, const Node* node2) const {
    double radius = 0;
    for (int i = 0; i < 4; i++) radius += getSplitDist(node1, node2, i);
    return radius;
}

double KDTree::getSplitDist(const Node* node1, const Node* node2, int d) const {
    switch(d) {
        case 0: {
            // scale weight of each missing genre by 10
            double dist = 0;
            bool found = false;
            for (std::string genre : node1->genres) {
                if (std::find(node2->genres.begin(), node2->genres.end(), genre) == node2->genres.end()) {
                    dist += 10;
                }
            }
            return dist;
        }
        case 1:
            if (node1->episodes == 0 || node2->episodes == 0) return 50;
            return (node1->episodes - node2->episodes) * (node1->episodes - node2->episodes);
        case 2:
            if (node1->rating == 0 || node2->rating == 0) return 50;
            return (node1->rating - node2->rating) * (node1->rating - node2->rating);
        case 3:
            // scale weight of members down by 10000^2
            return (node1->members - node2->members) * (node1->members - node2->members) / 100000000;
    }
    return 0;
}
