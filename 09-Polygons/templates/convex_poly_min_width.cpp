#include <bits/stdc++.h>
using namespace std;
typedef double lf;

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
    friend vec2 operator-(const vec2 &a) { return vec2(-a.x, -a.y); }
    friend vec2 operator*(vec2 a, const lf &b) { return a *= b; }
    friend vec2 operator*(const lf &b, vec2 a) { return a *= b; }
    friend vec2 operator/(vec2 a, const lf &b) { return a /= b; }
    friend bool operator==(const vec2 &a, const vec2 &b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator!=(const vec2 &a, const vec2 &b) { return !(a == b); }
    friend ostream &operator<<(ostream &o, const vec2 &a) {
        o << "(" << a.x << "," << a.y << ")";
        return o;
    }
};
typedef vector<vec2> poly;
lf dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
lf cross(vec2 a, vec2 b) { return a.x * b.y - a.y * b.x; }
lf full_angle(vec2 a, vec2 b) { return atan2(cross(a, b), dot(a, b)); }
vec2 perp(vec2 a) { return vec2(-a.y, a.x); }
lf norm(vec2 a) { return sqrt(dot(a, a)); }
lf dist(vec2 a, vec2 b) { return norm(a - b); }
lf angle(vec2 a, vec2 b) { return acos(dot(a, b) / (norm(a) * norm(b))); }
vec2 normalize(vec2 a) { return a / norm(a); }

struct cmp_dir {
    vec2 d;
    bool operator()(vec2 a, vec2 b) { return dot(a, d) < dot(b, d); }
};
lf min_width(const poly &p) {
    int n = p.size();
    vec2 d(1, 0);
    int i = min_element(p.begin(), p.end(), cmp_dir{d}) - p.begin();
    int j = max_element(p.begin(), p.end(), cmp_dir{d}) - p.begin();
    lf res = dist(p[i], p[j]);
    for (int k = 0; k < n; k++) {
        if (full_angle(-perp(d), p[(i + 1) % n] - p[i]) <
            full_angle(perp(d), p[(j + 1) % n] - p[j]))
            d = normalize(perp(p[(i + 1) % n] - p[i])), i = (i + 1) % n;
        else
            d = normalize(perp(p[j] - p[(j + 1) % n])), j = (j + 1) % n;
        res = min(res, dot(d, p[j] - p[i]));
    }
    return res;
}
