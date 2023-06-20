#include <bits/stdc++.h>
using namespace std;
typedef double lf;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

struct vec2 {
    lf x, y;
    vec2() : x(0), y(0) {}
    vec2(lf x, lf y) : x(x), y(y) {}
    vec2 &operator+=(const vec2 &o) { x += o.x; y += o.y; return *this; }
    vec2 &operator-=(const vec2 &o) { x -= o.x; y -= o.y; return *this; }
    vec2 &operator*=(const lf &o) { x *= o; y *= o; return *this; }
    vec2 &operator/=(const lf &o) { x /= o; y /= o; return *this; }
    friend vec2 operator+(vec2 a, const vec2 &b) { return a += b; }
    friend vec2 operator-(vec2 a, const vec2 &b) { return a -= b; }
    friend vec2 operator*(vec2 a, const lf &b) { return a *= b; }
    friend vec2 operator*(const lf &b, vec2 a) { return a *= b; }
    friend vec2 operator/(vec2 a, const lf &b) { return a /= b; }
    friend bool operator==(const vec2 &a, const vec2 &b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const vec2 &a, const vec2 &b) { return !(a == b); }
    friend ostream &operator<<(ostream &s, vec2 v) { s << "(" << v.x << "," << v.y << ")"; return s; }
};
typedef vector<vec2> poly;

struct seg {
    vec2 a, b;
    seg(vec2 a, vec2 b) : a(a), b(b) {}
    friend ostream &operator<<(ostream &s, seg t) { s << "[" << t.a << "," << t.b << "]"; return s; }
};
// compare segments by y-coordinates; assumes the segments have a common x-interval and don't intersect
// they may touch at one end if the intersection interval has positive length
// also allows comparison of point and segment
struct seg_y_compare {
    using is_transparent = void;
    bool operator()(const seg &s1, const seg &s2) const {
        vec2 s1a = s1.a.x < s1.b.x ? s1.a : s1.b;
        vec2 s1b = s1.a.x < s1.b.x ? s1.b : s1.a;
        vec2 s2a = s2.a.x < s2.b.x ? s2.a : s2.b;
        vec2 s2b = s2.a.x < s2.b.x ? s2.b : s2.a;
        lf x = 0.5 * (max(s1a.x, s2a.x) + min(s1b.x, s2b.x));
        lf y1 = s1a.x == s1b.x ? s1a.y : (x - s1a.x) / (s1b.x - s1a.x) * (s1b.y - s1a.y) + s1a.y;
        lf y2 = s2a.x == s2b.x ? s2a.y : (x - s2a.x) / (s2b.x - s2a.x) * (s2b.y - s2a.y) + s2a.y;
        return y1 < y2;
    }
};
typedef tree<seg,null_type,seg_y_compare,rb_tree_tag,tree_order_statistics_node_update> sweep_line;

// check for all given points whether they are inside of the given polygon
// assumes polygon to be simple but no convexity is needed
// returns vector of bools ret such that point pts[i] is inside <=> ret[i] == 1
vector<bool> points_in_poly(poly p, vector<vec2> pts) {
    vector<pair<lf, int>> s;
    for (int i = 0; i < p.size(); i++)
        s.push_back({p[i].x, -(i+1)});
    for (int i = 0; i < pts.size(); i++)
        s.push_back({pts[i].x, i});
    sort(s.begin(), s.end());
    
    sweep_line l;
    vector<bool> res(pts.size());
    
    for (auto pt : s) {
        if (pt.second < 0) { // polygon-node
            int i = -pt.second-1;
            int nxt = (i + 1) % p.size();
            int prv = i == 0 ? p.size() - 1 : i - 1;
            // erase finished segment(s)
            if (p[i].x != p[nxt].x)
                l.erase(seg(p[i], p[nxt]));
            if (p[i].x != p[prv].x)
                l.erase(seg(p[i], p[prv]));
            // add new segment(s)
            if (p[nxt].x > p[i].x)
                l.insert(seg(p[i], p[nxt]));
            if (p[prv].x > p[i].x)
                l.insert(seg(p[i], p[prv]));
        } else { // query point
            int i = pt.second;
            res[i] = l.order_of_key(seg(pts[i], pts[i])) & 1;
        }
    }
    return res;
}

