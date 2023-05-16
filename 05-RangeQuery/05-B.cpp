#include <iostream>
#include <vector>

// Sparse table template.
const int MAXN = 1e6, MAXLOG = 21, INF = 1e9;
int sparse[MAXLOG][MAXN];
int logsize[MAXN];
void build(int n) {
    int c = 2;
    for (int k = 1; k < MAXLOG; k++) {
        for (int i = 0; i + (1 << (k - 1)) < n; i++)
            sparse[k][i] = std::min(sparse[k - 1][i], sparse[k - 1][i + (1 << (k - 1))]);
        while (c <= std::min(2 << k, n))
            logsize[c++] = k;
    }
}
int get(int l, int r) {
    if (l > r)
        return INF;
    int lg = logsize[r - l + 1];
    return std::min(sparse[lg][l], sparse[lg][r - (1 << lg) + 1]);
}

// Structure to represent a binary tree node.
struct Node {
    int val;
    Node *left;
    Node *right;

    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Recursive function to construct the binary tree using sparse table to find min index.
Node *constructTree(const std::vector<int> &depths, int l, int r) {
    if (l > r)
        return nullptr;

    // Find index of minimum value in range [l, r].
    int minIndex = l;
    int minValue = get(l, r);
    for (int i = l + 1; i <= r; i++) {
        if (depths[i] == minValue) {
            minIndex = i;
            break;
        }
    }

    // Create the root of the subtree.
    Node *root = new Node(minIndex + 1);

    // Recursively construct left and right subtrees.
    root->left = constructTree(depths, l, minIndex - 1);
    root->right = constructTree(depths, minIndex + 1, r);

    return root;
}

// Function to perform in-order traversal of the binary tree to print parent values.
void inOrderTraversal(Node *root, std::vector<int> &parents) {
    if (root == nullptr)
        return;

    inOrderTraversal(root->left, parents);
    if (root->left)
        parents[root->left->val - 1] = root->val;
    if (root->right)
        parents[root->right->val - 1] = root->val;
    inOrderTraversal(root->right, parents);
}

int main() {
    int N, ai;
    std::cin >> N;
    std::vector<int> depths(N);

    // Input.
    for (int i = 0; i < N; i++) {
        std::cin >> ai;
        depths[i] = ai;
        sparse[0][i] = ai;
    }

    // Build sparse table.
    build(N);

    // Construct tree.
    Node *root = constructTree(depths, 0, N - 1);

    // Perform a in-order traversal to print parent values.
    std::vector<int> parents(N);

    inOrderTraversal(root, parents);
    for (int i = 0; i < N; i++)
        std::cout << parents[i] << " ";
    std::cout << std::endl;
}
