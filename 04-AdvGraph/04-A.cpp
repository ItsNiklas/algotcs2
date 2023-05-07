#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

// BFS template.
const int MAXN = 1e4;
int used[MAXN];
std::vector<int> edges[MAXN];
void bfs(int s) {
    std::queue<int> q;
    used[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : edges[v])
            if (!used[u]) {
                used[u] = used[v] + 1;
                q.push(u);
            }
    }
}

int main() {
    int N, M, u, v;

    // Read input.
    std::cin >> N >> M;
    while (std::cin >> u >> v) {
        edges[v].push_back(u);
        edges[u].push_back(v);
    }

    // Calculate density index.
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        std::fill(used, used + MAXN, 0); // Reset.

        bfs(i);

        // Accumulate sum of distances minus N (* N).
        sum = std::accumulate(used, used + MAXN, sum) - N;
    }

    // Calculate average pairwise distance.
    double res = (double)sum / ((N - 1) * N);

    // Density is the reciprocal of average pairwise distance.
    std::cout << std::setprecision(6) << std::fixed << 1 / res << std::endl;
}