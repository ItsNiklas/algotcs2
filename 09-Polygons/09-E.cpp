#include <bits/stdc++.h>
using namespace std;
typedef long double lf;

// Convex Hull Trick template.
const lf INF = 1 / .0;
// line a x + b that is relevant up to x = e
// The line is modified to include the id of the cyclist c.
struct line {
    mutable lf a, b, e;
    mutable int c;
    bool operator<(line o) const { return tie(a, b) < tie(o.a, o.b); }
    bool operator<(lf x) const { return e < x; }
};
struct cht : private set<line, less<>> {
    bool process(iterator i, iterator j) {
        if (j == end()) {
            i->e = INF;
            return false;
        };
        if (i->a == j->a)
            i->e = (i->b > j->b ? INF : -INF);
        else
            i->e = (j->b - i->b) / (i->a - j->a);
        return i->e >= j->e;
    }
    // add line {a x + b}
    void add(lf a, lf b, int c) {
        iterator nxt = insert({a, b, 0, c}).first, it = nxt++, prv = it;
        while (process(it, nxt))
            nxt = erase(nxt);
        if (prv != begin() && process(--prv, it))
            process(prv, it = erase(it));
        while ((it = prv) != begin() && (--prv)->e >= it->e)
            process(prv, erase(it));
    }
    // ask max_i a_i x + b_i
    pair<lf, int> query(lf x) {
        if (empty())
            return {-INF, -1};
        line l = *lower_bound(x);
        return {l.a * x + l.b, l.c};
    }
};

int main() {
    int N, t, a, c;
    lf s;
    cin >> N;

    // Store all queries for later
    // Store all cyclists with their id.
    vector<int> queries;
    map<int, line> cyclists;
    cht cht;

    // push back x-axis line.
    for (int i = 1; i <= N; i++) {
        cht.add(0, 0, i);
    }

    while (cin >> t >> a) {
        if (a == 1) {
            cin >> c >> s;
            // at t, slope is s (index is c)
            // calculate intecept a
            // mx + a = y

            // if c in cyclists...
            // We need to know the previous location of the cyclist.
            auto f = cyclists.find(c);
            lf y;
            if (f != cyclists.end()) {
                y = f->second.a * t + f->second.b;
            } else {
                y = 0;
            }

            lf a = y - s * t;

            // Add new line to cht.
            cht.add(s, a, c);
            cyclists[c] = {s, a, 0, c};
        } else {
            queries.push_back(t);
        }
    }

    // Answer queries. (Including the id of the cyclist)
    for (int q : queries) {
        auto ans = cht.query(q);
        cout << (long) ans.first << " " << ans.second << endl;
    }
}