#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int LOGN = 21; // 1 << (LOGN-1) >= MAXN

int root;
vector<int> edges[MAXN];

vector<int> visit;
int firstVisit[MAXN];
int depth[MAXN];

int st[MAXN][LOGN]; // Sparse Table

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

// New: Build the sparse table
void lca_build_st() {
    int n = visit.size();
    for (int i = 0; i < n; i++) {
        st[i][0] = visit[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            int u = st[i][j - 1];
            int v = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = depth[u] < depth[v] ? u : v;
        }
    }
}

// New: Use the sparse table to get the LCA (RMQ)
int lca_get_st(int l, int r) {
    int j = log2(r - l + 1);
    int u = st[l][j];
    int v = st[r - (1 << j) + 1][j];
    return depth[u] < depth[v] ? u : v;
}

void lca_prepare() {
    visit.clear();
    memset(firstVisit, 0, sizeof(firstVisit));
    memset(depth, 0, sizeof(depth));

    lca_dfs();
    lca_build_st();
}

int lca(int a, int b) {
    int l = min(firstVisit[a], firstVisit[b]);
    int r = max(firstVisit[a], firstVisit[b]);
    return lca_get_st(l, r);
}

void lca_update(int a, int b) {
    edges[a].push_back(b);
    visit.push_back(a);
    visit.push_back(b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, a, b;
    string type;
    vector<pair<int, int>> queries;

    root = 1;

    cin >> K;
    while (cin >> type >> a >> b) {
        if (type == "ADD") {
            // denoting that species b has evolved from species a
            lca_update(a, b);
        } else if (type == "GET") {
            // requesting the index of the latest evolved species of which both a and b descended
            // THE QUERIES CAN BE CACHED!
            queries.push_back({a, b});
        }
    }

    // update the tree
    lca_prepare();

    // answer the queries
    for (auto q : queries) {
        cout << lca(q.first, q.second) << endl;
    }
}