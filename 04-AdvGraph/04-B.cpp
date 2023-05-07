#include <iostream>
#include <queue>
#include <vector>

const int MAXN = 105, INF = 1e9;

// Dinic template.
struct edge {
    int v, u, c, flow;
};
int dis[MAXN], ptr[MAXN];
std::vector<edge> edglist;
std::vector<int> edgind[MAXN];
void dinic_addedge(int u, int v, int c) {
    edgind[u].push_back((int)edglist.size());
    edglist.push_back({u, v, c, 0});
    // Comment out as we manually insert the reverse edge.
    // edgind[v].push_back((int)edglist.size());
    // edglist.push_back({v, u, 0, 0});
}
bool bfs_dinic(int s, int t) {
    std::queue<int> q;
    q.push(s);
    dis[s] = 0;
    while (!q.empty() && dis[t] == -1) {
        int v = q.front();
        q.pop();
        for (auto ind : edgind[v]) {
            auto e = edglist[ind];
            if (dis[e.u] == -1 && e.flow < e.c) {
                q.push(e.u);
                dis[e.u] = dis[v] + 1;
            }
        }
    }
    return dis[t] != -1;
}
int dfs_dinic(int v, int t, int flow) {
    if (!flow || v == t)
        return flow;
    for (; ptr[v] < (int)edgind[v].size(); ptr[v]++) {
        int ind = edgind[v][ptr[v]];
        auto e = edglist[ind];
        if (dis[e.u] != dis[v] + 1)
            continue;
        int pushed = dfs_dinic(e.u, t, std::min(flow, e.c - e.flow));
        if (pushed) {
            edglist[ind].flow += pushed;
            edglist[ind ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}
long long dinic(int n, int s, int t) {
    long long flow = 0;
    while (true) {
        std::fill(dis, dis + n + 1, -1);
        if (!bfs_dinic(s, t))
            break;
        std::fill(ptr, ptr + n + 1, 0);
        while (int pushed = dfs_dinic(s, t, INF))
            flow += pushed;
    }
    return flow;
}

int main() {
    int N, M, a, b, c;

    // Read input.
    std::cin >> N >> M;
    while (std::cin >> a >> b >> c) {
        // Add edge and its reverse.
        dinic_addedge(a, b, c);
        dinic_addedge(b, a, c);
    }

    // The result is simply the maximum flow from 1 to N.
    // Run Dinic's algorithm.
    std::cout << dinic(N, 1, N) << std::endl;
}