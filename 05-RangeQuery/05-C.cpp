#include <iostream>
#include <map>
#include <string>

// Sparse Table Template.
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

int main() {
    // Read input.
    int N, g, l, r, i;
    std::string type;
    std::map<int, int> students; // std::map GPI to index.

    std::cin >> N;

    for (int i = 0; i < N; i++) {
        std::cin >> g;
        sparse[0][i] = g;
        students[g] = i + 1; // Store student index.
    }

    // Build sparse table.
    build(N);

    while (std::cin >> type) {
        if (type == "QUESTION") {
            // Query
            std::cin >> l >> r;

            // Print student index with lowest GPI in range [l, r].
            std::cout << students[get(l - 1, r - 1)] << std::endl;
        } else {
            // Dropout
            std::cin >> i;

            if (i == -1) // End of input.
                break;

            // Set GPI to INF and rebuild sparse table.
            // Could be optimized by batching multiple dropouts and rebuilding once.
            sparse[0][i - 1] = INF;
            build(N);
        }
    }
}