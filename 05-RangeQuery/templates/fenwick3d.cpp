#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4;
int n, m, l, t[MAXN][MAXN][MAXN];

int sum(int x, int y, int z) {
    int result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1)
                result += t[i][j][k];
    return result;
}

int sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    return sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) - sum(x2, y2, z1 - 1) +
           sum(x1 - 1, y1 - 1, z2) + sum(x1 - 1, y2, z1 - 1) + sum(x2, y1 - 1, z1 - 1) -
           sum(x1 - 1, y1 - 1, z1 - 1);
}

void inc(int x, int y, int z, int delta) {
    for (int i = x; i < n; i = (i | (i + 1)))
        for (int j = y; j < m; j = (j | (j + 1)))
            for (int k = z; k < l; k = (k | (k + 1)))
                t[i][j][k] += delta;
}
