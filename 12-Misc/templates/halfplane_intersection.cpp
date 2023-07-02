#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef double lf;
const lf EPSI = 1e-20, INF = 1e-100, PI = acos(-1);

struct vec3 {
    lf x, y, z;
    vec3() : x(0), y(0), z(0) {}
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
    friend ostream &operator<<(ostream &out, const vec2 v) {
        return out << "(" << v.x << "," << v.y << ")";
    }
};
typedef vector<vec2> poly;
// dot product
lf dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
// cross product
lf cross(vec2 a, vec2 b) { return a.x * b.y - a.y * b.x; }
// get a vector perpendicular to a (rotated by 90deg)
vec2 perp(vec2 a) { return vec2(-a.y, a.x); }
// check whether a, b, c lie counter-clockwise
bool cw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) > EPSI; }
// check whether a, b, c lie clockwise
bool ccw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) < -EPSI; }
// lexicographical compare
bool cmp_lex(vec2 a, vec2 b) { return tie(a.x, a.y) < tie(b.x, b.y); }

poly hull(vector<vec2> points) {
    sort(points.begin(), points.end(), cmp_lex);
    vector<vec2> lo, hi;
    for (vec2 p : points) {
        if (!cw(p, points[0], points[points.size() - 1])) {
            while (hi.size() > 1 && (ccw(hi[hi.size() - 2], hi[hi.size() - 1], p) ||
                                     !cw(hi[hi.size() - 2], hi[hi.size() - 1], p) &&
                                         hi[hi.size() - 1] != vec2(0, 0)))
                hi.pop_back();
            hi.push_back(p);
        }
        if (!ccw(p, points[0], points[points.size() - 1])) {
            while (lo.size() > 1 && (cw(lo[lo.size() - 2], lo[lo.size() - 1], p) ||
                                     !ccw(lo[lo.size() - 2], lo[lo.size() - 1], p) &&
                                         lo[lo.size() - 1] != vec2(0, 0)))
                lo.pop_back();
            lo.push_back(p);
        }
    }
    poly res(lo.begin(), lo.end());
    for (int i = hi.size() - 2; i > 0; i--)
        res.push_back(hi[i]);
    return res;
}

struct cmp_dir {
    vec2 d;
    bool operator()(vec2 a, vec2 b) { return dot(a, d) < dot(b, d); }
};
lf full_angle(vec2 a, vec2 b) {
    return fmod(atan2(cross(a, b), dot(a, b)) + 2 * PI, 2 * PI);
}
vec3 linear_separate(vector<vec2> A, vector<vec2> B) {
    A = hull(A);
    B = hull(B);
    vec2 d = vec2(1, 0);
    int minA = min_element(A.begin(), A.end(), cmp_dir({d})) - A.begin();
    int maxA = max_element(A.begin(), A.end(), cmp_dir({d})) - A.begin();
    int minB = min_element(B.begin(), B.end(), cmp_dir({d})) - B.begin();
    int maxB = max_element(B.begin(), B.end(), cmp_dir({d})) - B.begin();

    if (A.size() == 0 && B.size() != 0)
        return vec3(d.x, d.y, -dot(B[minB], d) + 1);
    else if (B.size() == 0 && A.size() != 0)
        return vec3(d.x, d.y, -dot(A[minA], d) + 1);
    else if (A.size() == 0 && B.size() == 0)
        return vec3(0, 0, 0);

    for (int i = 0; i <= A.size() + B.size(); i++) {
        lf minAa = A.size() == 1
                       ? 1
                       : full_angle(-perp(d), A[(minA + 1) % A.size()] - A[minA]);
        lf maxAa =
            A.size() == 1 ? 1 : full_angle(perp(d), A[(maxA + 1) % A.size()] - A[maxA]);
        lf minBa = B.size() == 1
                       ? 1
                       : full_angle(-perp(d), B[(minB + 1) % B.size()] - B[minB]);
        lf maxBa =
            B.size() == 1 ? 1 : full_angle(perp(d), B[(maxB + 1) % B.size()] - B[maxB]);

        lf a = min({minAa, maxAa, minBa, maxBa});
        if (a >= 2) {
            a = 2;
            i--;
        }

        if (minAa == a)
            minA = (minA + 1) % A.size();
        if (maxAa == a)
            maxA = (maxA + 1) % A.size();
        if (minBa == a)
            minB = (minB + 1) % B.size();
        if (maxBa == a)
            maxB = (maxB + 1) % B.size();
        d = vec2(cos(a) * d.x - sin(a) * d.y, sin(a) * d.x + cos(a) * d.y);

        if (dot(A[minA] - B[maxB], d) > EPSI)
            return vec3(d.x, d.y, -0.5 * dot(A[minA] + B[maxB], d));
        else if (dot(B[minB] - A[maxA], d) > EPSI)
            return vec3(d.x, d.y, -0.5 * dot(B[minB] + A[maxA], d));
    }
    return vec3(0, 0, 0);
}

vector<vec3> halfplane_intersection(vector<vec3> h) {
    vector<vec2> neg({vec2(0, 0)}), pos;
    for (vec3 l : h)
        (l.z < 0 ? neg : pos).pb(vec2(l.x / l.z, l.y / l.z));

    vec3 sep = linear_separate(neg, pos);
    if (sep.z == 0)
        return vector<vec3>();
    vec2 o(sep.x / sep.z, sep.y / sep.z);

    vector<vec2> d({vec2(0, 0)});
    for (vec3 l : h) {
        lf cc = l.z + l.x * o.x + l.y * o.y;
        d.pb(vec2(l.x / cc, l.y / cc));
    }
    d = hull(d);
    vector<vec3> res;
    for (int i = 0; i < d.size(); i++) {
        int j = i ? i - 1 : d.size() - 1;
        if (d[i] == vec2(0, 0) || d[j] == vec2(0, 0))
            res.pb(vec3(d[j].y - d[i].y, d[i].x - d[j].x, 0));
        else {
            vec2 dir = perp(d[i] - d[j]);
            lf c = -dot(dir, d[i]);
            res.pb(vec3(dir.x / c + o.x, dir.y / c + o.y, 1));
        }
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<vec3> h(n);
    for (int i = 0; i < n; i++)
        cin >> h[i].x >> h[i].y >> h[i].z;

    auto r = halfplane_intersection(h);

    for (auto v : r)
        cout << v.x << " " << v.y << " " << v.z << "\n";
}
