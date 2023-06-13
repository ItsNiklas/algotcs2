#include <bits/stdc++.h>
using namespace std;
typedef long double lf;

// Convex Hull template.
const lf EPSI = 1e-10, INF = numeric_limits<lf>::infinity();
bool equal(lf x, lf y) { return abs(x - y) < EPSI; }

//---------------------------VECTOR-STUFF---------------------------------
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

// cross product
lf cross(vec2 a, vec2 b) { return a.x * b.y - a.y * b.x; }
// check whether a, b, c lie counter-clockwise
bool cw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) >= EPSI; }
// check whether a, b, c lie clockwise
bool ccw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) <= -EPSI; }
// lexicographical compare
bool cmp_lex(vec2 a, vec2 b) { return tie(a.x, a.y) < tie(b.x, b.y); }

lf dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
lf full_angle(vec2 a, vec2 b) { return atan2(cross(a, b), dot(a, b)); }
vec2 perp(vec2 a) { return vec2(-a.y, a.x); }
lf norm(vec2 a) { return sqrt(dot(a, a)); }
lf dist(vec2 a, vec2 b) { return norm(a - b); }
lf angle(vec2 a, vec2 b) { return acos(dot(a, b) / (norm(a) * norm(b))); }
vec2 normalize(vec2 a) { return a / norm(a); }
poly hull(vector<vec2> points) {
    sort(points.begin(), points.end(), cmp_lex);
    vector<vec2> lo, hi;
    for (vec2 p : points) {
        if (!cw(p, points[0], points[points.size() - 1])) {
            while (hi.size() > 1 && !cw(hi[hi.size() - 2], hi[hi.size() - 1], p))
                hi.pop_back();
            hi.push_back(p);
        }
        if (!ccw(p, points[0], points[points.size() - 1])) {
            while (lo.size() > 1 && !ccw(lo[lo.size() - 2], lo[lo.size() - 1], p))
                lo.pop_back();
            lo.push_back(p);
        }
    }
    poly res(lo.begin(), lo.end());
    for (int i = hi.size() - 2; i > 0; i--)
        res.push_back(hi[i]);
    return res;
}

int main() {
    long long N, C, G = 0;
    long long x, y, g;

    cin >> N >> C;
    vector<vec2> points;

    // Read in the points and calculate the total amount of gold available.
    while (cin >> x >> y >> g) {
        G += g;
        points.push_back(vec2(x, y));
    }

    // Find the convex hull of the points.
    poly border = hull(points);

    // We need to find the circumference of the polygon border.
    // For every segment, we calculate the cost of building a wall along it.
    // If the cost exceeds the amount of gold available, we can't build the wall.
    lf cost = 0;
    for (size_t i = 0; i < border.size(); i++) {
        cost += C * dist(border[i], border[(i + 1) % border.size()]);
        if (cost > G) {
            cout << "Maybe don't!" << endl;
            return 0;
        }
    }

    cout << "Build that wall!" << endl;
}