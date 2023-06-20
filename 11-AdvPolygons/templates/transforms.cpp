#include <bits/stdc++.h>
using namespace std;
typedef double lf;

struct vec3 {
    lf x, y, z;
    vec3(lf x, lf y, lf z) : x(x), y(y), z(z) {}
    vec3 &operator+=(const vec3 &o) {
        x += o.x;
        y += o.y;
        z += o.z;
        return *this;
    }
    vec3 &operator-=(const vec3 &o) {
        x -= o.x;
        y -= o.y;
        z -= o.z;
        return *this;
    }
    vec3 &operator*=(const lf &o) {
        x *= o;
        y *= o;
        z *= o;
        return *this;
    }
    vec3 &operator/=(const lf &o) {
        x /= o;
        y /= o;
        z /= o;
        return *this;
    }
    friend vec3 operator+(vec3 a, const vec3 &b) { return a += b; }
    friend vec3 operator-(vec3 a, const vec3 &b) { return a -= b; }
    friend vec3 operator-(const vec3 &a) { return vec3(-a.x, -a.y, -a.z); }
    friend vec3 operator*(vec3 a, const lf &b) { return a *= b; }
    friend vec3 operator*(const lf &b, vec3 a) { return a *= b; }
    friend vec3 operator/(vec3 a, const lf &b) { return a /= b; }
    friend ostream &operator<<(ostream &out, const vec3 v) {
        return out << "(" << v.x << "," << v.y << "," << v.z << ")";
    }
};
lf dot(vec3 a, vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
vec3 cross(vec3 a, vec3 b) {
    return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
lf det(vec3 a, vec3 b, vec3 c) { return dot(a, cross(b, c)); }

struct tf3 {
    vec3 x, y, z, p;
    tf3() : x(1, 0, 0), y(0, 1, 0), z(0, 0, 1), p(0, 0, 0) {}
    tf3(vec3 x, vec3 y, vec3 z, vec3 p) : x(x), y(y), z(z), p(p) {}
};
vec3 tf_point(vec3 a, tf3 T) { return a.x * T.x + a.y * T.y + a.z * T.z + T.p; }
vec3 tf_vec(vec3 v, tf3 T) { return v.x * T.x + v.y * T.y + v.z * T.z; }
vec3 itf_vec(vec3 a, tf3 T) {
    lf d = det(T.x, T.y, T.z);
    return vec3(det(a, T.y, T.z) / d, det(T.x, a, T.z) / d, det(T.x, T.y, a) / d);
}
vec3 itf_point(vec3 a, tf3 T) { return itf_vec(a - T.p, T); }
