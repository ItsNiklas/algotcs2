#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

// dfs_scc_kosaraju.cpp template.
const int MAXN = 1000001;
std::vector<int> edges[MAXN], redges[MAXN], color_rep, topsort;
int color[MAXN], used[MAXN];

void dfs_topsort(int v) {
    used[v] = 1;
    for (auto u : edges[v])
        if (!used[u])
            dfs_topsort(u);
    topsort.emplace_back(v);
}
void find_topsort(int n) {
    for (int i = 1; i <= n; i++)
        if (!used[i])
            dfs_topsort(i);
    reverse(topsort.begin(), topsort.end());
}
void dfs_reverse(int v, int comp = 1) {
    color[v] = comp;
    for (auto u : redges[v])
        if (!color[u])
            dfs_reverse(u, comp);
}
int find_scc(int n) {
    find_topsort(n);
    int colorcnt = 0;
    for (auto v : topsort)
        if (!color[v]) {
            color_rep.emplace_back(v);
            dfs_reverse(v, ++colorcnt);
        }
    return colorcnt;
}

int main() {
    int N, M, a, b;

    std::cin >> N >> M;

    // Read edges and reverse edges.
    while (std::cin >> a >> b) {
        edges[a].emplace_back(b);
        redges[b].emplace_back(a);
    }

    // Find strongly connected components.
    // Return the number of components.
    int colorcnt = find_scc(N);

    // If we only have one SCC, we can stop with 0 links.
    // (Early stopping)
    if (colorcnt == 1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    // Fake condensation.
    // Imitate condensated SCCs and check the indgrees and
    // outdegrees of the components.
    std::vector<bool> indeg(colorcnt + 1, true);
    std::vector<bool> outdeg(colorcnt + 1, true);

    // Iterate over all edges and set degree if they
    // are not in the same component.
    for (int i = 1; i <= N; i++)
        for (auto k : edges[i]) {
            // Edge i --> k.
            int curr_c = color[i];
            int edge_c = color[k];

            if (edge_c != curr_c) {
                outdeg[curr_c] = false;
                indeg[edge_c] = false;
            }
        }

    // Solution is the maximum of:
    // - Number of SCCs without incoming edges,
    // - Number of SCCs without outgoing edges.
    int totalIn = std::accumulate(indeg.begin(), indeg.end(), -1);
    int totalOut = std::accumulate(outdeg.begin(), outdeg.end(), -1);
    std::cout << std::max(totalIn, totalOut) << std::endl;
}