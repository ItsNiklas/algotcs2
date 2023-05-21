#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOGN = 19; // 1 << 19 > 100000

vector<int> edges[MAXN];
int root = 0;

vector<int> visit;
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
    int l = min(firstVisit[a], firstVisit[b]);
    int r = max(firstVisit[a], firstVisit[b]);
    return lca_get_tree(l, r);
}

int main() {
    int N, M;
    unsigned long long x, y, z, s = 0, v = 0;

    // Numbers of vertices and edges in the graph
    cin >> N >> M;
    vector<int> a(2 * M + 1);

    // one line containing N − 1 integers, the i-th of which being the ancestor of vertex i
    // push into edges.
    for (int i = 1; i < N; ++i) {
        cin >> x;
        edges[x].push_back(i);
    }

    lca_prepare();

    cin >> a[1] >> a[2] >> x >> y >> z;
    for (int i = 3; i <= 2 * M; ++i) {
        a[i] = (x * a[i - 2] + y * a[i - 1] + z) % N;
    }

    // v is the response to the i-1 th request
    for (int i = 1; i <= M; ++i) {
        // i-th request
        v = lca((a[2 * i - 1] + v) % N, a[2 * i]);
        s += v;
    }

    cout << s << endl;
}