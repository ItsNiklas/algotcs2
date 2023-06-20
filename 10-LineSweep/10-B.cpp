#include <algorithm>
#include <iostream>
#include <vector>

struct interval {
    int l, r;
};
bool operator<(interval a, interval b) {
    return (a.l == b.l) ? (a.r < b.r) : (a.l < b.l);
}

/*
Given a set of segments [Li, Ri] with integer end points Li, Ri, you are to
find a subset of it that completely covers the segment [0, M ] and, in doing
so, consists of a minimal number of segments.
*/

int main() {
    int M, l, r;

    std::vector<interval> v;

    std::cin >> M;
    while (std::cin >> l >> r) {
        if (l == 0 and r == 0) {
            break;
        }
        v.push_back({l, r});
    }

    sort(v.begin(), v.end());

    // Output the minimum number of segments to cover the segment [0, M ]. If
    // there is no solution output “No solution”
    int cnt = 0;
    int cur = 0;
    size_t i = 0;
    while (cur < M) {
        int best = -1;
        while (i < v.size() and v[i].l <= cur) {
            if (best == -1 or v[i].r > v[best].r) {
                best = i;
            }
            i++;
        }
        if (best == -1) {
            std::cout << "No solution" << std::endl;
            return 0;
        }
        cnt++;
        cur = v[best].r;
    }
    std::cout << cnt << std::endl;
}