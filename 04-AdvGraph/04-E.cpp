#include <iostream>
#include <queue>
#include <vector>

const int MAXN = 1e4, INF = 1e9;

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
    edgind[v].push_back((int)edglist.size());
    edglist.push_back({v, u, 0, 0});
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
    int N;
    std::string name;
    std::vector<std::string> bricks;

    // Read N and name.
    std::cin >> N >> name;

    // Store bricks.
    for (int i = 0; i < N; i++) {
        std::string brick;
        std::cin >> brick;
        bricks.push_back(brick);
    }

    // We represent each letter as a node in a graph.
    // This will correspond to 1 to 26.
    // We also add a source and a sink. Let 0 be the source and MAXN-1 the sink.
    // For each letter in the sisters name we add an edge from the source to the letter.
    for (size_t i = 0; i < name.length(); i++) {
        dinic_addedge(0, name[i] - 'A' + 1, 1);
    }

    // For each brick, we add an edge from the brick number to the sink.
    // The brick nodes are offset by 30, so that they don't conflict with the letter nodes.
    for (size_t i = 0; i < bricks.size(); i++) {
        dinic_addedge(30 + i, MAXN - 1, 1);
    }

    // For each letter on each brick, add an edge from the letter node to the respective brick node.
    for (size_t i = 0; i < bricks.size(); i++) {
        for (auto letter : bricks[i]) {
            dinic_addedge(letter - 'A' + 1, 30 + i, 1);
        }
    }

    // Now we run dinic's algorithm to find the maximum flow.
    unsigned long long flow = dinic(MAXN, 0, MAXN - 1);

    // If the maximum flow is equal to the length of the name, then we can spell the
    // name. We output 'YES', 'NO' otherwise.
    std::cout << (flow == name.length() ? "YES" : "NO") << std::endl;
}