#include <bits/stdc++.h>
using namespace std;
typedef long double lf;

struct vec3 {
    lf x, y, z;
    vec3() : x(0), y(0), z(0) {}
    vec3(lf x, lf y, lf z) : x(x), y(y), z(z) {}
    vec3 &operator+=(const vec3 &o) { x+=o.x; y+=o.y; z+=o.z; return *this; }
    vec3 &operator-=(const vec3 &o) { x-=o.x; y-=o.y; z-=o.z; return *this; }
    vec3 &operator*=(const lf &o) { x *= o; y *= o; z *= o; return *this; }
    vec3 &operator/=(const lf &o) { x /= o; y /= o; z /= o; return *this; }
    friend vec3 operator+(vec3 a, const vec3 &b) { return a += b; }
    friend vec3 operator-(vec3 a, const vec3 &b) { return a -= b; }
    friend vec3 operator-(const vec3 &a) { return vec3(-a.x, -a.y, -a.z); }
    friend vec3 operator*(vec3 a, const lf &b) { return a *= b; }
    friend vec3 operator*(const lf &b, vec3 a) { return a *= b; }
    friend vec3 operator/(vec3 a, const lf &b) { return a /= b; }
    friend ostream& operator<<(ostream& out, const vec3 v) {
        return out << "(" << v.x << "," << v.y << "," << v.z << ")";
    }
};

const lf PI = acos(-1);

lf dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

lf norm(vec3 a) {
    return sqrt(dot(a,a));
}

vec3 cross(vec3 a, vec3 b) {
    return vec3(a.y * b.z - a.z * b.y,
                            a.z * b.x - a.x * b.z,
                            a.x * b.y - a.y * b.x);
}

lf det(vec3 a, vec3 b, vec3 c) {
    return dot(a, cross(b, c));
}

lf sphere_angle(vec3 a, vec3 b, vec3 c) {
    lf y = norm(b) * det(a, b, c);
    lf x = dot(cross(b, a), cross(b, c));
    lf t = atan2(y, x);
    return t < 0 ? t + 2 * PI : t;
}

lf sphere_area(vector<vec3> p) {
    int n = p.size();
    lf res = -(n - 2) * PI;
    for (int i = 0; i < n; i++) {
        int q = i ? i - 1 : n - 1;
        int s = i + 1 < n ? i + 1 : 0;
        res += sphere_angle(p[s], p[i], p[q]);
    }
    return min(res, 4*PI - res);
}

