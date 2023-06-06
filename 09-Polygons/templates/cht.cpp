#include <bits/stdc++.h>
typedef double lf;
using namespace std;

const lf INF = 1 / .0;
// line a x + b that is relevant up to x = e
struct line {
    mutable lf a, b, e;
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
    void add(lf a, lf b) {
        iterator nxt = insert({a, b, 0}).first, it = nxt++, prv = it;
        while (process(it, nxt))
            nxt = erase(nxt);
        if (prv != begin() && process(--prv, it))
            process(prv, it = erase(it));
        while ((it = prv) != begin() && (--prv)->e >= it->e)
            process(prv, erase(it));
    }
    // ask max_i a_i x + b_i
    lf query(lf x) {
        if (empty())
            return -INF;
        line l = *lower_bound(x);
        return l.a * x + l.b;
    }
};
