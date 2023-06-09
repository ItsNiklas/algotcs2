#include <iostream>
#include <vector>

const int MAXN = 1e5 + 5;

int root;
std::vector<int> edges[MAXN];

// LCA template, interval tree variant.
std::vector<int> visit;
int firstVisit[MAXN];
int depth[MAXN];
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
int tree[8 * MAXN];
void lca_build_tree(int v = 1, int tl = 0, int tr = visit.size() - 1) {
    if (tl == tr)
        tree[v] = visit[tl];
    else {
        int tm = (tl + tr) / 2;
        lca_build_tree(2 * v, tl, tm);
        lca_build_tree(2 * v + 1, tm + 1, tr);
        if (depth[tree[2 * v]] < depth[tree[2 * v + 1]])
            tree[v] = tree[2 * v];
        else
            tree[v] = tree[2 * v + 1];
    }
}
void lca_prepare() {
    lca_dfs();
    lca_build_tree();
}
int lca_get_tree(int l, int r, int v = 1, int tl = 0, int tr = visit.size() - 1) {
    if (l == tl && r == tr)
        return tree[v];
    int tm = (tl + tr) / 2;
    if (r <= tm)
        return lca_get_tree(l, r, 2 * v, tl, tm);
    if (l > tm)
        return lca_get_tree(l, r, 2 * v + 1, tm + 1, tr);
    int lmin = lca_get_tree(l, tm, 2 * v, tl, tm);
    int rmin = lca_get_tree(tm + 1, r, 2 * v + 1, tm + 1, tr);
    return depth[lmin] < depth[rmin] ? lmin : rmin;
}
int lca(int a, int b) {
    int l = std::min(firstVisit[a], firstVisit[b]);
    int r = std::max(firstVisit[a], firstVisit[b]);
    return lca_get_tree(l, r);
}

int main() {
    int N, a, k, r;

    // The number of rivers.
    std::cin >> N;

    for (int i = 1; i < N; i++) {
        // one line containing all connections between rivers, given via integers
        // a2, ..., an, with ai being the index of the river that river i flows into.
        std::cin >> a;
        edges[a].push_back(i + 1);
    }

    // 1 being the index of the large stream everything ultimately flows into before it reaches the
    // ocean.
    root = 1;

    // Initialize the LCA.
    lca_prepare();

    while (std::cin >> k and k) {
        // k numbers r1, ..., rk, representing the indices of the rivers the pollutants
        // are dumped into output the index of the river in which the given pollutants meet.
        // (assuming that each pollutant contaminates all rivers
        // that carry it further downstream)
        std::cin >> r;

        // Find the LCA of all polluted rivers by iterating over them.
        // This is possible because the LCA is associative.
        for (int i = 1; i < k; i++) {
            std::cin >> a;
            r = lca(r, a);
        }

        std::cout << r << std::endl;
    }
}