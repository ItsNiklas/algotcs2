#include <iostream>
#include <set>
#include <vector>

// Kahn's Algorithm template, kahn.cpp
const int MAXN = 100001;
int indeg[MAXN];
std::vector<int> edges[MAXN];

// The queue inside is exchanged with a multiset
// to create the lexographically smallest solution.
std::vector<int> kahn(int n) {
    std::vector<int> res;
    std::multiset<int> q;
    for (int i = 1; i <= n; i++)
        if (!indeg[i])
            q.insert(i);
    while (!q.empty()) {
        int v = *q.begin();
        q.erase(q.begin());
        for (auto u : edges[v])
            if (--indeg[u] == 0)
                q.insert(u);
        res.emplace_back(v);
    }
    return res;
}

int main() {
    int N, M, a, b;
    std::cin >> N >> M;

    // Read edges and increase indegree.
    while (std::cin >> a >> b) {
        edges[a].emplace_back(b);
        indeg[b]++;
    }

    // Result is simply the output of
    // Kahn with a multiset.
    for (auto i : kahn(N))
        std::cout << i << " ";

    std::cout << std::endl;
}