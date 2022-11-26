#include "kdtree.h"

using namespace KDTree;

KDTree(const std::unordered_map<Node*, std::unordered_map<Node*, Edge*>>& adjacency_list) {
    if (adjacency_list.empty()) {
      root = nullptr;
      size = 0;
      return;
    }
    std::vector<Node*> points;
    for (auto pair : adjacency_list) points.push_back(pair.first);
    buildTree(points, 0, points.size() - 1, 0, root);
    size = adjacency_list.size();
}

KDTree(const KDTree& other) {
    if (other == NULL) return;
    traverse_build(root, other->root);
    size = other->size;
}

KDTree const& operator=(const KDTree& other) {
    if (*this == other) return *this;
    this->~KDTree();
    this = new KDTree(other);
    return *this;
}

~KDTree() {
    size = 0;
    removeTree(root);
}

Node* findNearestNeighbor(const Node* query) const return findNearestNeighbor(query, 0, root);

int partition(vector<Node*>& arr, int start, int end, int p_idx, int d) {
    Point<Dim> pivot_value = arr[p_idx];
    Point<Dim> temp = arr[end];
    arr[end] = arr[p_idx];
    arr[p_idx] = temp;
    int idx = start;
    for (int i = start; i < end; i++) {
        if (smallerDimVal(arr[i], pivot_value, d)) {
        Point<Dim> t = arr[i];
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

int median(vector<Node*>& arr, int start, int end, int k, int d) {
    if (start == end) return start;
    int p_idx = k;
    p_idx = partition(arr, start, end, p_idx, d);
    if (k == p_idx) return k;
    if (k < p_idx) return median(arr, start, p_idx - 1, k, d);
    return median(arr, p_idx + 1, end, k, d);
}

void buildTree(vector<Node*>& arr, int start, int end, int d, TreeNode*& curr) {
    if (start <= end) {
    int middle = median(arr, start, end, (start+end)/2, d);
    curr = new TreeNode(arr[middle]);
    d = (d + 1 == Dim) ? 0 : d + 1;
    buildTree(arr, start, middle - 1, d, curr->left);
    buildTree(arr, middle + 1, end, d, curr->right);
  } else {
    curr = nullptr;
  }
}

void buildCopy(TreeNode*& curr, const TreeNode* other) {
    if (other != NULL) {
    curr = new TreeNode(other->point);
    buildCopy(curr->left, other->left);
    buildCopy(curr->right, other->right);
    } else {
        curr = NULL;
    }
}

void deleteNode(TreeNode*& root) {
    if (root) {
    deleteNode(root->left);
    deleteNode(root->right);
    delete root;
    root = NULL;
  }
}

Node* findNearestNeighbor(const Node*& query, int d, TreeNode* curr) const {
    if (!curr->left && !curr->right) return curr->point;
    int next_d = d + 1 % Dim;
    Node* nearest = curr->point;
    if (smallerDimVal(query, curr->point, d) && curr->left) nearest = findNearestNeighbor(query, next_d, curr->left);
    else if (!smallerDimVal(query, curr->point, d) && curr->right) nearest = findNearestNeighbor(query, next_d, curr->right);
    if (shouldReplace(query, nearest, curr->point)) nearest = curr->point;
    double radius = 0;
    for (int i = 0; i < Dim; i++) radius += (query[i] - nearest[i]) * (query[i] - nearest[i]);
    double splitDist = (curr->point[d] - query[d]) * (curr->point[d] - query[d]);
    if (radius >= splitDist) {
        Node* temp = curr->point;
        if (smallerDimVal(query, curr->point, d) && curr->right) temp =findNearestNeighbor(query, next_d, curr->right);
        else if (!smallerDimVal(query, curr->point, d) && curr->left) temp = findNearestNeighbor(query, next_d, curr->left);
        if (shouldReplace(query, nearest, temp)) nearest = temp;
    }
    return nearest;
}

bool shouldReplace(const Node*& target, const Node*& currentBest, const Node*& potential) const {}

bool smallerDimVal(const Node*& first, const Node*& second, int curDim) const {}