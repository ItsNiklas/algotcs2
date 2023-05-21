#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5, MAXLOG = 18; // 1 << (MAXLOG-1) >= MAXN

int root;
vector<int> edges[MAXN];
int tin[MAXN], tout[MAXN], timer = 1;
int up[MAXLOG][MAXN];

void dfs(int v = root, int p = root) {
    tin[v] = timer++;
    up[0][v] = p;
    for (int l = 1; l < MAXLOG; l++)
        up[l][v] = up[l - 1][up[l - 1][v]];
    for (int w : edges[v]) {
        if (w != p)
            dfs(w, v);
    }
    tout[v] = timer++;
}
// bool upper(int a, int b) { return tin[a] <= tin[b] && tout[a] >= tout[b]; }
// int lca(int a, int b) {
//     if (upper(a, b))
//         return a;
//     if (upper(b, a))
//         return b;
//     for (int l = MAXLOG - 1; l >= 0; l--)
//         if (!upper(up[l][a], b))
//             a = up[l][a];
//     return up[0][a];
// }

int altitude[MAXN];

int main() {
    int N, M, s, m;

    cin >> N >> root;

    // Read parents of nodes.
    for (int i = 1; i <= N; i++) {
        cin >> s;
        edges[s].push_back(i);
    }

    // Read altitude MSL of vertex i.
    for (int i = 1; i <= N; i++) {
        cin >> altitude[i];
    }

    // Set up binary lifting.
    dfs();

    cin >> M; // the number of mountaineers

    while (cin >> s >> m) {
        // Starting point of Mountaineer: s
        // Maximum altitude: m + altitude[s]
        m += altitude[s];

        //cerr << "Starting at " << s << " with max " << m << endl;

        // output the index of the highest situated vertex he will reach.
        // By climbing up the tree, until we reach the root or a vertex with altitude > m.
        // Using binary lifting! Otherwise, too slow.
        for (int l = MAXLOG - 1; l >= 0; l--) {
            if (altitude[up[l][s]] <= m) {
                s = up[l][s];
            }
        }

        cout << s << endl;
    }
}