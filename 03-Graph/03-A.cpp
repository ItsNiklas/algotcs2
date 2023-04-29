#include <iostream>
#include <map>
#include <string>
#include <vector>

// Template: dfs_ancestor.cpp
const int MAXN = 100001;
std::vector<int> edges[MAXN];
int used[MAXN], tin[MAXN], tout[MAXN], timer = 1;
void dfs(int v) {
    used[v] = 1;
    tin[v] = timer++;
    for (auto u : edges[v])
        if (!used[u])
            dfs(u);
    tout[v] = timer++;
}
bool ancestor(int u, int v) { return tin[u] < tin[v] && tout[u] > tout[v]; }

int main() {
    // Read input.
    int N, M, k, a, b;
    std::cin >> N;

    // std::getline to read until linebreak, not whitespace.
    std::map<int, std::string> names;
    for (int i = 0; i <= N; i++)
        getline(std::cin, names[i]);

    // Build graph.
    for (int i = 1; i <= N; i++) {
        std::cin >> k;
        edges[k].emplace_back(i);
    }

    // Start ancestor-dfs at node 0.
    dfs(0);

    // Answer queries.
    std::cin >> M;
    while (std::cin >> a >> b) {
        // Check ancestor relationship.
        if (ancestor(a, b)) {
            std::cout << names[b] << " is an ancestor of " << names[a] << "." << std::endl;
        } else if (ancestor(b, a)) {
            std::cout << names[a] << " is an ancestor of " << names[b] << "." << std::endl;
        } else {
            std::cout << names[a] << " and " << names[b] << " are not related." << std::endl;
        }
    }
}