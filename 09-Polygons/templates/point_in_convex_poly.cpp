#include <bits/stdc++.h>
using namespace std;
typedef double lf;
const lf INF = 1e9, EPSI = 1e-9;

struct vec2 {
    lf x, y;
    vec2() : x(0), y(0) {}
    vec2(lf x, lf y) : x(x), y(y) {}
    vec2 &operator+=(const vec2 &o) {
        x += o.x;
        y += o.y;
        return *this;
    }
    vec2 &operator-=(const vec2 &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }
    vec2 &operator*=(const lf &o) {
        x *= o;
        y *= o;
        return *this;
    }
    vec2 &operator/=(const lf &o) {
        x /= o;
        y /= o;
        return *this;
    }
    friend vec2 operator+(vec2 a, const vec2 &b) { return a += b; }
    friend vec2 operator-(vec2 a, const vec2 &b) { return a -= b; }
    friend vec2 operator*(vec2 a, const lf &b) { return a *= b; }
    friend vec2 operator*(const lf &b, vec2 a) { return a *= b; }
    friend vec2 operator/(vec2 a, const lf &b) { return a /= b; }
    friend bool operator==(const vec2 &a, const vec2 &b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator!=(const vec2 &a, const vec2 &b) { return !(a == b); }
    friend ostream &operator<<(ostream &out, const vec2 v) {
        return out << "(" << v.x << "," << v.y << ")";
    }
};
typedef vector<vec2> poly;
lf dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
lf cross(vec2 a, vec2 b) { return a.x * b.y - a.y * b.x; }
vec2 perp(vec2 a) { return vec2(-a.y, a.x); }
bool cw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) >= EPSI; }
bool ccw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) <= -EPSI; }

lf angle(vec2 a) { return atan2(a.y, a.x); }
bool cmp_angle(vec2 a, vec2 b) { return angle(a) < angle(b); }
vec2 c;
vector<vec2> rp;
void precalc(const vector<vec2> &p) {
    c = accumulate(p.begin(), p.end(), vec2{0, 0}) / p.size();
    for (vec2 a : p)
        rp.push_back(a - c);
    auto mn = min_element(rp.begin(), rp.end(), cmp_angle);
    rotate(rp.begin(), mn, rp.end());
}
bool check_inside(vec2 pt) {
    pt -= c;
    auto it = lower_bound(rp.begin(), rp.end(), pt, cmp_angle);
    vec2 p1, p2;
    if (it == rp.end() || it == rp.begin())
        p2 = *rp.begin(), p1 = *rp.rbegin();
    else
        p2 = *it, p1 = *(--it);
    return !cw(pt, p1, p2);
}
