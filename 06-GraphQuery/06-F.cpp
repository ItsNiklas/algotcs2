#include <iostream>
#include <queue>
#include <vector>

const int MAXN = 1e5 + 5, MAXLOG = 33 - __builtin_clz(MAXN), MAXM = 5 * 1e5 + 5;

struct edge {
    int o, ind;
};
std::vector<int> lca_edges[MAXN];
std::vector<edge> edges[MAXN];
int root;

// LCA, Sparse Table variant template.
// (Answer lca queries on lca_edges)
int tin[MAXN], tout[MAXN], t;
int d[MAXN], st[MAXLOG + 1][2 * MAXN], logar[2 * MAXN];
void dfs(int v, int de = 1) {
    d[v] = de;
    st[0][tin[v] = ++t] = v;
    for (int w : lca_edges[v])
        dfs(w, de + 1), st[0][++t] = v;
    tout[v] = t;
}
void build(int r = root) {
    std::fill(tin, tin + MAXN, 0); // Reset because I share the arrays with dfs_bridge.
    std::fill(tout, tout + MAXN, 0);
    dfs(r);
    for (int k = 1; k <= MAXLOG; k++)
        for (int i = 0; i + (1 << k) <= 2 * MAXN; i++) {
            int t1 = st[k - 1][i], t2 = st[k - 1][i + (1 << (k - 1))];
            st[k][i] = (d[t1] < d[t2] ? t1 : t2);
        }
    for (int log = 1, i = 0; log <= MAXLOG; log++)
        while (i < (1 << log) && i < 2 * MAXN)
            logar[i++] = log - 1;
}
int get(int l, int r) {
    if (l > r)
        std::swap(l, r);
    int lg = logar[r - l + 1];
    int t1 = st[lg][l], t2 = st[lg][r - (1 << lg) + 1];
    return (d[t1] < d[t2] ? t1 : t2);
}
int lca(int a, int b) {
    if (tin[a] > tin[b])
        std::swap(a, b);
    if (tout[b] < tout[a])
        return a;
    return get(tout[a], tin[b]);
}
int dist(int a, int b) { return d[a] + d[b] - 2 * d[lca(a, b)]; }

// DFS bridge template.
// Find all bridges in the graph edges.
int timer;
bool bridge[MAXM];
void dfs_bridge(int v, int p = -1, int pind = -1) {
    tout[v] = tin[v] = timer++;
    for (auto e : edges[v]) {
        if (e.o == p && e.ind == pind)
            continue;
        if (!tin[e.o]) {
            dfs_bridge(e.o, v, e.ind);
            tout[v] = std::min(tout[v], tout[e.o]);
            if (tin[v] < tout[e.o])
                bridge[e.ind] = 1;
        } else
            tout[v] = std::min(tout[v], tin[e.o]);
    }
}

// Path-BFS.
// Find the number of bridges on the shortest path from v to each vertex.
// Additionally, fill lca_edges with the edges of the BFS tree.
std::vector<int> bfs_bridge_count(int v, int n) {
    std::vector<int> counts(n + 1, -1); // Initialize all counts as -1.
    counts[v] = 0;                      // The count of the source vertex is 0.
    std::queue<int> q;
    q.push(v);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const edge &e : edges[u]) {
            int nextVertex = e.o;
            if (counts[nextVertex] == -1) { // If the next vertex is not yet visited.
                counts[nextVertex] =
                    counts[u] + bridge[e.ind]; // Increment the count if walking over a bridge.
                q.push(nextVertex);

                // BFS Ancestor.
                // Fill graph from the root turning it into a tree (lca_edges).
                lca_edges[u].push_back(nextVertex);
            }
        }
    }

    return counts;
}

int main() {
    int N, M, K, u, v;

    // Number of cities and roads in Dreamland.
    std::cin >> N >> M >> root;

    // M lines describing Dreamland’s road system.
    for (int i = 0; i < M; ++i) {
        std::cin >> u >> v;
        edges[u].push_back({v, i});
        edges[v].push_back({u, i});
    }

    // Find all bridges.
    // Result is stored in bridge[].
    dfs_bridge(root);

    // Precalculate number of bridges on every shortest path from root to each node.
    // This is precalculated because we need to answer K queries, and we cannot
    // run a BFS for every query.
    // While running the BFS, also convert edges to lca_edges simultaneously.
    // This way we get a tree based on the graph, rooted in the capital.
    std::vector<int> bridgecnt = bfs_bridge_count(root, N);

    // Set up LCA on lca_edges.
    build();

    // K lines, each containing one of the guesses, i.e. two integers in the
    // range 1, ..., N , representing the indices of the cities the wizards guess
    // to be in.
    std::cin >> K;
    while (std::cin >> u >> v) {
        // First, compute the LCA of u and v. We can be sure, that until this
        // point, the two wizards do not meet. Next:
        // Find shortest path from root to lca(u, v) using dfs on edges.
        // Count number of edges in that path that are also bridges.
        // This will be the number of unavoidable paths (bridges)
        // from u and v to the captial.
        std::cout << bridgecnt[lca(u, v)] << std::endl;
    }
}