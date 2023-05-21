#include <iostream>
#include <vector>

const int MAXN = 1e5 + 5, MAXLOG = 33 - __builtin_ctz(MAXN);

int root;
std::vector<int> edges[MAXN];
int altitude[MAXN];

// LCA template, binary lifting variant.
// However, we only use the binary lifting part.
int up[MAXLOG][MAXN];
void dfs(int v = root, int p = root) {
    up[0][v] = p;
    for (int l = 1; l < MAXLOG; l++)
        up[l][v] = up[l - 1][up[l - 1][v]];
    for (int w : edges[v]) {
        if (w != p)
            dfs(w, v);
    }
}

int main() {
    int N, M, s, m;

    std::cin >> N >> root;

    // Read parents of nodes.
    for (int i = 1; i <= N; i++) {
        std::cin >> s;
        edges[s].push_back(i);
    }

    // Read altitude MSL of vertex i.
    for (int i = 1; i <= N; i++) {
        std::cin >> altitude[i];
    }

    // Set up binary lifting.
    dfs();

    // The number of mountaineers.
    std::cin >> M;

    while (std::cin >> s >> m) {
        // Starting point of Mountaineer: s.
        // Maximum altitude: m + altitude[s].
        m += altitude[s];

        // Output the index of the highest situated vertex he will reach.
        // We climb up the tree, until we reach the root or a vertex with altitude > m.
        // Climbing using binary lifting! Otherwise, too slow.
        for (int l = MAXLOG - 1; l >= 0; l--) {
            if (altitude[up[l][s]] <= m) {
                s = up[l][s];
            }
        }

        std::cout << s << std::endl;
    }
}