#include <algorithm>

#include "kdtree.h"

/**
 * @brief Construct a new KDTree::KDTree object from a list of nodes
 * 
 * @param node_list map of id to node pointer
 */
KDTree::KDTree(const std::unordered_map<unsigned, Node*>& node_list) {
    if (node_list.empty()) {
      root = nullptr;
      size = 0;
      return;
    }
    std::vector<Node*> points;
    for (auto pair : node_list) points.push_back(pair.second);
    buildTree(points, 0, points.size() - 1, 0, root);
    size = node_list.size();
}

/**
 * @brief Construct a new KDTree::KDTree object as a deep copy of another
 * 
 * @param other 
 */
KDTree::KDTree(const KDTree& other) {
    buildCopy(root, other.root);
    size = other.size;
}

/**
 * @brief Sets the KDTree to be the same object as another
 * 
 * @param other 
 * @return KDTree const& 
 */
KDTree const& KDTree::operator=(const KDTree& other) {
    if (this->root == other.root) return *this;
    this->~KDTree();
    *this = KDTree(other);
    return *this;
}

/**
 * @brief Destroy the KDTree::KDTree object
 * 
 */
KDTree::~KDTree() {
    size = 0;
    deleteNode(root);
}

/**
 * @brief find the node closest the the query
 * Calls helper starting at the root node and dimension 0
 * 
 * @param query
 * @return Node* 
 */
Node* KDTree::findNearestNeighbor(const Node* query) const { return findNearestNeighbor(query, 0, root); }

/**
 * @brief puts all points between start and end to the left or right of the median node, based on the dimension
 * 
 * @param arr vector of node pointers
 * @param start index of start point (inclusive)
 * @param end index of end point (inclusive)
 * @param p_idx index of median node in current dimension
 * @param d current dimension
 * @return index of median
 */
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

/**
 * @brief finds the index of the median value between start and end in a given dimension
 * 
 * @param arr vector of node pointers
 * @param start index of start point (inclusive)
 * @param end index of end point (inclusive)
 * @param k desired mid point
 * @param d current dimension
 * @return index of median
 */
int KDTree::median(std::vector<Node*>& arr, int start, int end, int k, int d) {
    if (start == end) return start;
    int p_idx = k;
    p_idx = partition(arr, start, end, p_idx, d);
    if (k == p_idx) return k;
    if (k < p_idx) return median(arr, start, p_idx - 1, k, d);
    return median(arr, p_idx + 1, end, k, d);
}

/**
 * @brief recursively builds a KDTree from an array, cycling through 5 dimensions
 * NOTE: each dimension corresponds to an element of the Node structure
 * 
 * @param arr vector of node pointers
 * @param start index of the start point (inclusive)
 * @param end index of the end point (inclusive)
 * @param d current dimension
 * @param curr current TreeNode
 */
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

/**
 * @brief recursively build a copy of an existing KDTree
 * 
 * @param curr current TreeNode
 * @param other TreeNode of existing KDTree
 */
void KDTree::buildCopy(TreeNode*& curr, const TreeNode* other) {
    if (other != NULL) {
    curr = new TreeNode(other->anime);
    buildCopy(curr->left, other->left);
    buildCopy(curr->right, other->right);
    } else {
        curr = NULL;
    }
}

/**
 * @brief recursively delete all TreeNodes
 * 
 * @param root
 */
void KDTree::deleteNode(TreeNode*& root) {
    if (root) {
        root->anime = NULL;
        deleteNode(root->left);
        deleteNode(root->right);
        delete root;
        root = NULL;
    }
}

/**
 * @brief given a node containing desired anime traits, find the anime that is most similar
 * 
 * @param query desired node
 * @param d current dimension
 * @param curr current TreeNode
 * @return pointer to node that is most similar to query
 */
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

/**
 * @brief returns whether a node is closer to the desired node than the current closest
 * 
 * @param target desired node
 * @param currentBest node closest to target
 * @param potential node potentially closer to target
 * @return true 
 * @return false 
 */
bool KDTree::shouldReplace(const Node* target, const Node* currentBest, const Node* potential) const {
    double curr_dist = getRadius(target, currentBest);
    double new_dist = getRadius(target, potential);
    return ((curr_dist != new_dist) ? new_dist < curr_dist : potential < currentBest);
}

/**
 * @brief determines whether the first node is smaller than the second node in the given dimension
 * NOTE: dim 0 checks if any genre in the first node is also in the second node
 * 
 * @param first 
 * @param second 
 * @param curDim 
 * @return true 
 * @return false 
 */
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

/**
 * @brief returns the distance between 2 nodes in every dimension
 * 
 * @param node1 
 * @param node2 
 * @return double 
 */
double KDTree::getRadius(const Node* node1, const Node* node2) const {
    double radius = 0;
    for (int i = 0; i < 4; i++) radius += getSplitDist(node1, node2, i);
    return radius;
}

/**
 * @brief returns the distance between 2 nodes in a given dimension
 * NOTE: distances are scaled based on decided importance of dimension
 * 
 * @param node1 
 * @param node2 
 * @param d dimension
 * @return double 
 */
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
