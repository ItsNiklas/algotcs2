#include <cstring>
#include <iostream>

// Fenwick 2D template.
const int MAXN = 2005;
int fenwick[MAXN][MAXN];
int sum(int x, int y) {
    int result = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            result += fenwick[x][j];
    return result;
}
void inc(int x, int y, int delta) {
    for (; x < MAXN; x |= x + 1)
        for (int j = y; j < MAXN; j |= j + 1)
            fenwick[x][j] += delta;
}
int sum(int x0, int x1, int y0, int y1) {
    --x0, --y0;
    return (sum(x1, y1) - sum(x0, y1) - sum(x1, y0) + sum(x0, y0));
}

// Binary search, predicate function check.
bool check(int n, int l, int L) {
    for (int i = 0; i + l <= n; i++) {
        for (int j = 0; j + l <= n; j++) {
            if (sum(i, i + l - 1, j, j + l - 1) <= L) {
                // It is possible to place a square of size l at (i,j),
                // without including any more than L points.
                return true;
            }
        }
    }
    return false;
}

int main() {
    int T, N, W, L, a, b;
    std::cin >> T;

    while (T--) {
        std::cin >> N >> W >> L;

        // Clear fenwick tree.
        std::memset(fenwick, 0, sizeof(fenwick));

        while (W--) {
            std::cin >> a >> b;
            a--, b--;
            inc(a, b, 1);
        }

        // Binary search to find maximal l where check(l) is true.
        int lo = 0, hi = N;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (check(N, mid, L)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        // Output size of largest square.
        std::cout << lo * lo << std::endl;
    }
}
