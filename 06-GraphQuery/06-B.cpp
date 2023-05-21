#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int MAXN = 1000005, MAXLOG = 33 - __builtin_ctz(MAXN);

std::vector<int> edges[MAXN];
int root;

// LCA template, sparse table variant.
std::vector<int> visit;
int firstVisit[MAXN];
int depth[MAXN];
int st[MAXN][MAXLOG];
void lca_dfs(int v = root, int d = 1) {
    firstVisit[v] = visit.size();
    visit.push_back(v);
    depth[v] = d;
    for (int w : edges[v]) {
        if (depth[w] != 0)
            continue;
        lca_dfs(w, d + 1);
        visit.push_back(v);
    }
}
void lca_build_st() {
    int n = visit.size();
    for (int i = 0; i < n; i++) {
        st[i][0] = visit[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            int u = st[i][j - 1];
            int v = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = depth[u] < depth[v] ? u : v;
        }
    }
}
int lca_get_st(int l, int r) {
    int j = 31 - __builtin_clz(r - l + 1); // log2(r - l + 1)
    int u = st[l][j];
    int v = st[r - (1 << j) + 1][j];
    return depth[u] < depth[v] ? u : v;
}
void lca_prepare() {
    lca_dfs();
    lca_build_st();
}
int lca(int a, int b) {
    int l = std::min(firstVisit[a], firstVisit[b]);
    int r = std::max(firstVisit[a], firstVisit[b]);
    return lca_get_st(l, r);
}

int main() {
    int K, a, b;
    std::string type;
    std::vector<std::pair<int, int>> queries;

    // Original species.
    root = 1;

    std::cin >> K;
    while (std::cin >> type >> a >> b) {
        if (type == "ADD")
            // Denoting that species b has evolved from species a.
            // Add an edge from a to b.
            edges[a].push_back(b);
        else if (type == "GET")
            // requesting the index of the latest evolved species of which both a and b descended
            // Important in this problem: THE GET QUERIES CAN BE DELAYED!
            // This is because the answer to a query is preserved even if the tree is updated,
            // as only descendants are added.
            queries.push_back({a, b});
    }

    // Prepare the LCA.
    // By caching the queries, we can answer them in O(1) time, as we
    // only need to prepare the LCA once.
    lca_prepare();

    // Answer the queries.
    for (std::pair<int, int> q : queries)
        std::cout << lca(q.first, q.second) << std::endl;
}