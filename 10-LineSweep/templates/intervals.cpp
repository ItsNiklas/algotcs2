#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100, MAXM = 100;

struct point {
    int coord, type, index;
};
bool operator<(point a, point b) {
    return (a.coord == b.coord) ? (a.type < b.type) : (a.coord < b.coord);
}
int l[MAXN], r[MAXN], p[MAXM], N, M;

bool solve() {
    vector<point> v;
    for (int i = 0; i < N; i++)
        v.push_back({l[i], 0, i});
    for (int i = 0; i < M; i++)
        v.push_back({p[i], 1, i});
    stable_sort(v.begin(), v.end());
    multiset<int> s;
    int cnt = 0;
    for (point pt : v) {
        if (pt.type == 0) 
            s.insert(r[pt.index]);
        else while (!s.empty()) {
                int pr = *s.begin();
                s.erase(s.begin());
                if (pr >= pt.coord) {
                    cnt++;
                    break;
                }
            }
    }
    return (cnt == N);
}


