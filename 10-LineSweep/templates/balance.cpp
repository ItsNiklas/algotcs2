#include<bits/stdc++.h>
using namespace std;

int a[MAXN];

int solve() {
    int prevbalance = 0;
    int balance = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        balance += a[i] - 1;
        if (balance != 0 && !(balance > 0 && prevbalance < 0))
            cnt++;
        prevbalance = balance;
    }
    return cnt;
}

