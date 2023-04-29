#include <algorithm>
#include <iostream>
#include <vector>

// Strongly Connected Components and Condensation Graph implementation template.
// https://cp-algorithms.com/graph/strongly-connected-components.html
const int MAXN = 3005;
std::vector<std::vector<int>> adj(MAXN), adj_rev(MAXN), adj_scc(MAXN);
std::vector<int> order, component, root_nodes, roots(MAXN, 0);
std::vector<bool> used;

void dfs1(int v) {
    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);

    order.emplace_back(v);
}
void dfs2(int v) {
    used[v] = true;
    component.emplace_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            dfs2(u);
}
void scc_condensate(int n) {
    used.assign(MAXN, false);

    for (int i = 1; i <= n; i++)
        if (!used[i])
            dfs1(i);

    used.assign(MAXN, false);
    reverse(order.begin(), order.end());

    for (auto v : order)
        if (!used[v]) {
            dfs2(v);
            int root = component.front();
            for (auto u : component)
                roots[u] = root;
            root_nodes.emplace_back(root);

            component.clear();
        }
    for (int v = 1; v <= n; v++)
        for (auto u : adj[v]) {
            int root_v = roots[v], root_u = roots[u];

            if (root_u != root_v)
                adj_scc[root_v].emplace_back(root_u);
        }
}

int main() {
    int N, M, a, b;
    std::cin >> N >> M;

    // Read edges and reversed edges.
    while (std::cin >> a >> b) {
        adj[a].emplace_back(b);
        adj_rev[b].emplace_back(a);
    }

    // Find strongly connected components and condensate them.
    scc_condensate(N);

    // adj_scc contains condensated scc graph. Nodes are in root_nodes.
    // The solution is the number of SCCs without any incoming edges, as
    // a firestation has to placed there, and can reach other components
    // from there.
    std::cout << std::count_if(root_nodes.begin(), root_nodes.end(), [&](int i) {
        return adj_scc[i].empty();
    }) << std::endl;
}