#include <bits/stdc++.h>
using namespace std;
typedef double lf;
const lf INF = 1e9;

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

struct seg {
    vec2 a, b;
    seg(vec2 a, vec2 b) : a(a), b(b) {}
};

bool intersect(seg s, seg t) {
    lf det = dot(perp(s.b - s.a), t.a - t.b);
    lf l = dot(perp(t.b - t.a), t.a - s.a);
    lf m = dot(perp(s.b - s.a), t.a - s.a);
    if (det < 0)
        return det <= l && l <= 0 && det <= m && m <= 0;
    else
        return 0 <= l && l <= det && 0 <= m && m <= det;
}
bool inside(vec2 pt, const poly &p) {
    bool res = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = i ? i - 1 : p.size() - 1;
        res ^= intersect(seg(pt, pt + vec2(1, INF)), seg(p[i], p[j]));
    }
    return res;
}
