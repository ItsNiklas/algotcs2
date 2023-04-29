#include <algorithm>
#include <iostream>
#include <vector>

// Template: dfs_bridges.cpp
const int MAXN = 120, MAXM = 1000001;
struct edge {
    int o, ind;
};
std::vector<edge> edges[MAXN];
int tin[MAXN], fout[MAXN], timer;
std::vector<int> bridge(MAXM);
void dfs_bridge(int v, int p = -1, int pind = -1) {
    fout[v] = tin[v] = timer++;
    for (auto e : edges[v]) {
        if (e.o == p && e.ind == pind)
            continue;
        if (!tin[e.o]) {
            dfs_bridge(e.o, v, e.ind);
            fout[v] = std::min(fout[v], fout[e.o]);
            if (tin[v] < fout[e.o])
                bridge[e.ind] = 1;
        } else
            fout[v] = std::min(fout[v], tin[e.o]);
    }
}

void find_bridges() {
    // Reset.
    std::fill(tin, tin + MAXN, 0);
    std::fill(fout, fout + MAXN, 0);
    std::fill(bridge.begin(), bridge.end(), 0);
    timer = 0;

    // Execute.
    dfs_bridge(1);
}

int main() {
    int M, a, b, m, renovate_idx = -1;
    char t;

    std::cin >> M;

    // Read bridges.
    for (m = 1; m <= M; m++) {
        std::cin >> a >> b;

        edge e1 = {b, m};
        edge e2 = {a, m};
        edges[a].emplace_back(e1);
        edges[b].emplace_back(e2);
    }

    std::cin >> M;

    // Answer queries
    while (std::cin >> t >> a >> b) {
        if (t == 'R') {
            // Renovate a--b.
            // Is it essential?
            find_bridges();

            // Find bridge (a--b) index.
            for (edge &e : edges[a])
                if (e.o == b) {
                    renovate_idx = e.ind;
                    break;
                }

            // Find out if renovate_idx is a essential bridge.
            if (bridge[renovate_idx]) {
                // Yes, in bridge array.
                std::cout << "Impossibile!" << std::endl;
            } else {
                // No, can renovate.
                // Erase renovate_idx from adj vector.
                edges[a].erase(
                    remove_if(edges[a].begin(), edges[a].end(),
                              [renovate_idx](const edge &e) { return e.ind == renovate_idx; }),
                    edges[a].end());

                edges[b].erase(
                    remove_if(edges[b].begin(), edges[b].end(),
                              [renovate_idx](const edge &e) { return e.ind == renovate_idx; }),
                    edges[b].end());

                // Done.
                std::cout << "Va bene!" << std::endl;
            }

        } else {
            // Bridge completed.
            m++;

            edge e1 = {b, m};
            edge e2 = {a, m};
            edges[a].emplace_back(e1);
            edges[b].emplace_back(e2);
        }
    }
}