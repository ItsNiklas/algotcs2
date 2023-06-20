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
lf norm(vec3 a) { return sqrt(dot(a, a)); }

lf volume(vector<vec3> verts, vector<int> trigs) {
    lf res = 0;
    int n = trigs.size() / 3;
    vec3 o = verts[trigs[0]];
    for (int i = 0; i < n; i++) {
        vec3 a = verts[trigs[3 * i]];
        vec3 b = verts[trigs[3 * i + 1]];
        vec3 c = verts[trigs[3 * i + 2]];
        vec3 nrm = cross(b - a, c - a);
        res += abs(dot(nrm, c - o));
    }
    return res / 6.0;
}
