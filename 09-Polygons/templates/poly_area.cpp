#include <bits/stdc++.h>
typedef double lf;
using namespace std;

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

lf cross(vec2 a, vec2 b) { return a.x * b.y - a.y * b.x; }

lf area(const poly &p) {
    lf res = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = i ? i - 1 : p.size() - 1;
        res += (p[i].y + p[j].y) * (p[i].x - p[j].x);
    }
    return 0.5 * abs(res);
}

lf area_trig(const poly &p) {
    lf res = 0;
    for (int i = 2; i < p.size(); i++)
        res += cross(p[i] - p[0], p[i - 1] - p[0]);
    return 0.5 * abs(res);
}
