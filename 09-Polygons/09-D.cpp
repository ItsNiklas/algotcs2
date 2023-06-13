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
    bool operator<(const vec2 &b) const {
        return tie(this->x, this->y) < tie(b.x, b.y);
    }
};

typedef vector<vec2> poly;
// cross product
lf cross(vec2 a, vec2 b) { return a.x * b.y - a.y * b.x; }
// check whether a, b, c lie counter-clockwise
bool cw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) > EPSI; }
// check whether a, b, c lie clockwise
bool ccw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) < -EPSI; }
// check whether a, b, c are collinear
bool collinear(vec2 a, vec2 b, vec2 c) { return abs(cross(a - b, c - b)) < EPSI; }
// lexicographical compare
bool cmp_lex(vec2 a, vec2 b) { return tie(a.x, a.y) < tie(b.x, b.y); }

poly hull(vector<vec2> points) {
    sort(points.begin(), points.end(), cmp_lex);
    vector<vec2> lo, hi;
    for (vec2 p : points) {
        while (hi.size() > 1 && !cw(hi[hi.size() - 2], hi[hi.size() - 1], p)) {
            if (collinear(hi[hi.size() - 2], hi[hi.size() - 1], p)) {
                hi.push_back(p);
                break;
            }
            hi.pop_back();
        }
        if (hi.empty() || hi.back() != p)
            hi.push_back(p);

        while (lo.size() > 1 && !ccw(lo[lo.size() - 2], lo[lo.size() - 1], p)) {
            if (collinear(lo[lo.size() - 2], lo[lo.size() - 1], p)) {
                lo.push_back(p);
                break;
            }
            lo.pop_back();
        }
        if (lo.empty() || lo.back() != p)
            lo.push_back(p);
    }

    poly res(lo.begin(), lo.end());
    for (int i = hi.size() - 2; i > 0; i--)
        res.push_back(hi[i]);
    return res;
}

vec2 perp(vec2 a) { return vec2(-a.y, a.x); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;

    cin >> n;

    vector<vec2> points;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        points.push_back(vec2(x, y));
    }

    int res = 0;

    // Cheese the worstcase, only triangles.
    int worstcase = 0;

    // Iterate until all points are removed.
    // Each iteration removes the convex hull of the remaining points.
    while (++res) {

        // Convex hull.
        poly p = hull(points);

        // If the convex hull has less than 3 points, exit.
        if (p.size() < 3)
            break;

        // check if all points p lie on the same line, if yes, also exit.
        bool all_collinear = true;
        for (size_t i = 0; i < p.size() - 2; i++) {
            if (!collinear(p[i], p[i + 1], p[i + 2])) {
                all_collinear = false;
                break;
            }
        }
        if (all_collinear)
            break;

        // Hardcode the case of a triangle (worstcase).
        if (p.size() == 3 and ++worstcase > 10) {
            cout << n / 3 << endl;
            return 0;
        }

        // Remove hull points from points (slow).
        for (auto &pt : p) {
            auto it = find(points.begin(), points.end(), pt);
            if (it != points.end()) {
                points.erase(it);
            }
        }
    }

    cout << res - 1 << endl;
}