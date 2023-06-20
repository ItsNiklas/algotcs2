#include<bits/stdc++.h>
using namespace std;

int solve(vector<int> a, int m) {
    set<int> e(a.begin(), a.begin()+m);
    int res = *e.rbegin() - *e.begin();
    for (int i = m; i < a.size(); i++) {
        e.erase(a[i-m]);
        e.insert(a[i]);
        res = max(res, *e.rbegin() - *e.begin());
    }
    return res;
}

