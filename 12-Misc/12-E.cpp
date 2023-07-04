#include <algorithm>
#include <complex>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

const long double EPSI = 1e-20, INF = 1e100, PI = acos(-1);

// Halfplane intersection template.
struct vec3 {
    long double x, y, z;
    vec3() : x(0), y(0), z(0) {}
    vec3(long double x, long double y, long double z) : x(x), y(y), z(z) {}
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
    vec3 &operator*=(const long double &o) {
        x *= o;
        y *= o;
        z *= o;
        return *this;
    }
    vec3 &operator/=(const long double &o) {
        x /= o;
        y /= o;
        z /= o;
        return *this;
    }
    friend vec3 operator+(vec3 a, const vec3 &b) { return a += b; }
    friend vec3 operator-(vec3 a, const vec3 &b) { return a -= b; }
    friend vec3 operator-(const vec3 &a) { return vec3(-a.x, -a.y, -a.z); }
    friend vec3 operator*(vec3 a, const long double &b) { return a *= b; }
    friend vec3 operator*(const long double &b, vec3 a) { return a *= b; }
    friend vec3 operator/(vec3 a, const long double &b) { return a /= b; }
    friend std::ostream &operator<<(std::ostream &out, const vec3 v) {
        return out << "(" << v.x << "," << v.y << "," << v.z << ")";
    }
};
struct vec2 {
    long double x, y;
    vec2() : x(0), y(0) {}
    vec2(long double x, long double y) : x(x), y(y) {}
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
    vec2 &operator*=(const long double &o) {
        x *= o;
        y *= o;
        return *this;
    }
    vec2 &operator/=(const long double &o) {
        x /= o;
        y /= o;
        return *this;
    }
    friend vec2 operator+(vec2 a, const vec2 &b) { return a += b; }
    friend vec2 operator-(vec2 a, const vec2 &b) { return a -= b; }
    friend vec2 operator-(const vec2 &a) { return vec2(-a.x, -a.y); }
    friend vec2 operator*(vec2 a, const long double &b) { return a *= b; }
    friend vec2 operator*(const long double &b, vec2 a) { return a *= b; }
    friend vec2 operator/(vec2 a, const long double &b) { return a /= b; }
    friend bool operator==(const vec2 &a, const vec2 &b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator!=(const vec2 &a, const vec2 &b) { return !(a == b); }
    friend std::ostream &operator<<(std::ostream &out, const vec2 v) {
        return out << "(" << v.x << "," << v.y << ")";
    }
};
typedef std::vector<vec2> poly;
// dot product
long double dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
// cross product
long double cross(vec2 a, vec2 b) { return a.x * b.y - a.y * b.x; }
// get a std::vector perpendicular to a (rotated by 90deg)
vec2 perp(vec2 a) { return vec2(-a.y, a.x); }
// check whether a, b, c lie counter-clockwise
bool cw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) > EPSI; }
// check whether a, b, c lie clockwise
bool ccw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) < -EPSI; }
// lexicographical compare
bool cmp_lex(vec2 a, vec2 b) { return std::tie(a.x, a.y) < std::tie(b.x, b.y); }

poly hull(std::vector<vec2> points) {
    sort(points.begin(), points.end(), cmp_lex);
    std::vector<vec2> lo, hi;
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
long double full_angle(vec2 a, vec2 b) {
    return fmod(atan2(cross(a, b), dot(a, b)) + 2 * PI, 2 * PI);
}
vec3 linear_separate(std::vector<vec2> A, std::vector<vec2> B) {
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
        long double minAa =
            A.size() == 1 ? 1
                          : full_angle(-perp(d), A[(minA + 1) % A.size()] - A[minA]);
        long double maxAa =
            A.size() == 1 ? 1 : full_angle(perp(d), A[(maxA + 1) % A.size()] - A[maxA]);
        long double minBa =
            B.size() == 1 ? 1
                          : full_angle(-perp(d), B[(minB + 1) % B.size()] - B[minB]);
        long double maxBa =
            B.size() == 1 ? 1 : full_angle(perp(d), B[(maxB + 1) % B.size()] - B[maxB]);

        long double a = std::min({minAa, maxAa, minBa, maxBa});
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

std::vector<vec3> halfplane_intersection(std::vector<vec3> h) {
    std::vector<vec2> neg({vec2(0, 0)}), pos;
    for (vec3 l : h)
        (l.z < 0 ? neg : pos).push_back(vec2(l.x / l.z, l.y / l.z));

    vec3 sep = linear_separate(neg, pos);
    if (sep.z == 0)
        return std::vector<vec3>();
    vec2 o(sep.x / sep.z, sep.y / sep.z);

    std::vector<vec2> d({vec2(0, 0)});
    for (vec3 l : h) {
        long double cc = l.z + l.x * o.x + l.y * o.y;
        d.push_back(vec2(l.x / cc, l.y / cc));
    }
    d = hull(d);
    std::vector<vec3> res;
    for (int i = 0; i < d.size(); i++) {
        int j = i ? i - 1 : d.size() - 1;
        if (d[i] == vec2(0, 0) || d[j] == vec2(0, 0))
            res.push_back(vec3(d[j].y - d[i].y, d[i].x - d[j].x, 0));
        else {
            vec2 dir = perp(d[i] - d[j]);
            long double c = -dot(dir, d[i]);
            res.push_back(vec3(dir.x / c + o.x, dir.y / c + o.y, 1));
        }
    }
    return res;
}

int main() {
    // s: how many kilograms of stone the daily delivery consists of
    // m: how many grinders there are on the plant
    // n: number of different types of gravel the plant can produce
    int s, m, n;
    std::cin >> s >> m >> n;

    // Let's denote xi as the kilograms of type i gravel produced.
    std::vector<long double> x(n);

    // p_i is the profit per kilogram of type i gravel.
    std::vector<long double> p(n);
    for (int i = 0; i < n; i++)
        std::cin >> p[i];

    // t_i is the time (seconds) it takes to produce one kilogram of type i gravel in
    // one grinder.
    std::vector<long double> t(n);
    for (int i = 0; i < n; i++)
        std::cin >> t[i];

    // FIRST
    // The objective function to be maximized (which in this case is the profit) can be
    // represented as:
    // maximize Z = p^T * x
    // subject to:
    // ∑(xi) == s
    // ∑(ti * xi) <= 86400 * m
    // xi >= 0

    // This is equivalent to the dual problem:
    // minimize W = s * u + 86400 * m * v
    // subject to:
    // u + ti * v >= pi
    // v >= 0

    auto profit = [&](long double u, long double v) { return s * u + 86400 * m * v; };

    // This is equivalent to the following system of inequalities:
    // minimize W = s * u + 86400 * m * v
    // subject to:
    // -u - ti * v + pi <= 0
    // -v <= 0

    // We can solve this problem using the half-plane intersection method.
    // Store constraints described by ai u + bi v + ci ≤ 0 we
    std::vector<vec3> h(n + 1);

    for (int i = 0; i < n; i++) {
        h[i].x = -1;    // Coefficient of u
        h[i].y = -t[i]; // Coefficient of v, given as input
        h[i].z = p[i];  // Constant term, given as input
    }
    h[n] = vec3(0, -1, -EPSI); // -v <= 0 (but c = 0 is not allowed, so we use EPSI)

    // I assume we have strong duality.
    auto q = halfplane_intersection(h);

    std::vector<long double> profits;
    std::transform(std::begin(q), std::end(q), std::back_inserter(profits),
                   [&](const vec3 &v) { return (v.z == 0) ? INF : profit(v.x, v.y); });

    std::cout << std::fixed << std::setprecision(8)
              << *std::min_element(profits.begin(), profits.end()) << std::endl;

    // SECOND
    // The objective function to be maximized (which in this case is the profit) can be
    // represented as:
    // maximize Z = p^T * x
    // subject to:
    // ∑(xi) == s
    // ∑(ti * xi) == 86400 * m
    // xi >= 0

    // This is equivalent to the dual problem:
    // minimize Z = s * u + 86400 * m * v
    // subject to:
    // u + ti * v >= pi

    // This is equivalent to the following system of inequalities:
    // minimize W = s * u + 86400 * m * v
    // subject to:
    // -u - ti * v + pi <= 0
    h.resize(n);

    for (int i = 0; i < n; i++) {
        h[i].x = -1;    // Coefficient of u
        h[i].y = -t[i]; // Coefficient of v, given as input
        h[i].z = p[i];  // Constant term, given as input
    }

    // I assume we have strong duality.
    q = halfplane_intersection(h);

    profits.clear();
    std::transform(std::begin(q), std::end(q), std::back_inserter(profits),
                   [&](const vec3 &v) { return (v.z == 0) ? INF : profit(v.x, v.y); });

    std::cout << std::fixed << std::setprecision(8)
              << *std::min_element(profits.begin(), profits.end()) << std::endl;
}
