#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

// Template dfs_cutpoint.cpp and bfs.cpp.
const int MAXN = 100001;
std::vector<int> edges[MAXN];
int used[MAXN], tin[MAXN], fout[MAXN], timer;
std::set<int> cutpoints;
std::map<int, int> parents;
int forbidden_v = -1; // Inserted.
void dfs_cutpoint(int v, bool root = true) {
    used[v] = 1;
    fout[v] = tin[v] = ++timer;
    int fwd_edges = 0;
    for (auto u : edges[v])
        if (!used[u]) {
            dfs_cutpoint(u, false);
            fout[v] = std::min(fout[v], fout[u]);
            if (tin[v] <= fout[u] && !root)
                cutpoints.insert(v);
            fwd_edges++;
        } else
            fout[v] = std::min(fout[v], tin[u]);
    if (root && fwd_edges >= 2)
        cutpoints.insert(v);
}
void bfs(int s, int goal) {
    parents.clear();
    std::queue<int> q;
    std::vector<int> visited(MAXN);
    if (s == forbidden_v)
        return; // Inserted.
    visited[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : edges[v]) {
            if (u == forbidden_v)
                continue; // Inserted.
            if (!visited[u]) {
                parents[u] = v;
                visited[u] = 1;
                if (u == goal)
                    return;
                q.push(u);
            }
        }
    }
}

std::vector<int> bfs_path(int end, int curr) {
    // Execute bfs.
    bfs(end, curr);

    // Reverse retrace path using the parents
    // array filled by bfs.
    std::vector<int> path;
    while (true) {
        if (!parents.count(curr)) {
            path.clear();
            break; // Path was not found.
        }

        curr = parents[curr];
        if (curr == end)
            break; // Path was found.
        path.emplace_back(curr);
    }
    return path;
}

int main() {
    int N, M, w, h, a, b;
    std::cin >> N >> M >> w >> h;

    // Read edges.
    while (std::cin >> a >> b) {
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }

    // Find cutpoints.
    // Afterwards located in global cutpoints array.
    dfs_cutpoint(w);

    // Find any path between h and w.
    // Intersect path and the cutpoints.
    // This will eleminate cutpoints which do not lie on the main path.
    std::vector<int> path_ = bfs_path(h, w);
    std::vector<int> path;
    std::copy_if(path_.begin(), path_.end(), std::back_inserter(path),
                 [&](int i) { return cutpoints.count(i); }); // Contained

    // Path can still contain nodes which are articulation points
    // for components which do not matter, i.e. contain
    // neither w or h. These are removed by iteratively holding
    // one vertice out and trying to find a path.
    std::vector<int> res;
    for (const int v : path) {
        forbidden_v = v;
        if (bfs_path(h, w).empty())
            res.emplace_back(v); // v really is unavoidable!
    }

    // Print.
    std::cout << res.size() << std::endl;
    for (const int &i : res)
        std::cout << i << " ";
    std::cout << std::endl;
}