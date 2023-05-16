#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;
int n, a[MAXN], t[MAXN];

void inc(int i, int delta) {
    for (; i < n; i = (i | (i + 1)))
        t[i] += delta;
}

void init() {
    for (int i = 0; i < n; i++)
        inc(i, a[i]);
}

int sum(int r) {
    int res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
        res += t[r];
    return res;
}

int sum(int l, int r) { return sum(r) - sum(l - 1); }
