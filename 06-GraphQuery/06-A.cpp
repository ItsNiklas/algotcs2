#include <algorithm>
#include <iostream>

const int MAXN = 1e5 + 5;

// Union-Find template.
int parent[MAXN], ranks[MAXN];
void make_set(int v) {
    parent[v] = v;
    ranks[v] = 0;
}
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (ranks[a] < ranks[b])
            std::swap(a, b);
        parent[b] = a;
        if (ranks[a] == ranks[b])
            ++ranks[a];
    }
}

int main() {
    int N, M, a, b, j = 1;

    // the number of villages to be connected.
    std::cin >> N;

    // Initialize the Union-Find.
    for (int i = 1; i <= N; i++)
        make_set(i);

    // the number of roads that the king’s subjects are willing to build following his initial
    // order.
    std::cin >> M;

    for (int i = 1; i <= M; i++) {
        std::cin >> a >> b;

        // road i now connects villages ai and bi (bidirectionally).
        union_sets(a, b);

        // If road i makes the last connections that were missing, output i and exit.
        // Check if all villages are connected.

        // If the minimum number of connections required (based on N) is not reached, this can be
        // skipped.
        if (i < N)
            continue;

        // Cursed loop:
        // Compare until a city is not connected to the first city.
        // Continue on the next iteration with the same index j
        // until every city is connected to the first city.
        for (; find_set(j) == find_set(1); j++) {
            if (j == N) {
                std::cout << i << std::endl;
                return 0;
            }
        }
    }

    // If there are still cities not connected by the M roads you are given, output ”Build some
    // more!”.
    std::cout << "Build some more!" << std::endl;
}
