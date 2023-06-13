#include <bits/stdc++.h>
using namespace std;

typedef double lf;
const lf INF = numeric_limits<lf>::infinity(), EPSI = 1e-9;

// Polygon template.
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
bool cw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) >= EPSI; }
bool ccw(vec2 a, vec2 b, vec2 c) { return cross(a - b, c - b) <= -EPSI; }
lf angle(vec2 a) { return atan2(a.y, a.x); }
lf norm(vec2 a) { return sqrt(dot(a, a)); }
lf angle(vec2 a, vec2 b) { return acos(dot(a, b) / (norm(a) * norm(b))); }

/*
In order to call a polygon a star, we require two things:
    • the corners are alternating between pointing into and out of the polygon
in a zig-zag pattern.
    • the angles of the outer corners should be acute (0° < angle < 90°).
Given a polygon as a list of points describing the corners in clockwise order
(neighboring and the last and first point are connected), you are to find out
if it is a star.
*/

int main() {
    int N, x, y;
    cin >> N;

    // Read in points.
    poly p;

    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        p.push_back(vec2(x, y));
    }

    // Initialize.
    int clockwise = !ccw(p[N - 1], p[0], p[1]);

    for (int i = 0; i < N; i++) {
        // We are interested in the angle at b.
        vec2 a = p[(i - 1 + N) % N];
        vec2 b = p[i];
        vec2 c = p[(i + 1) % N];

        // Check if ccw occilates between true and false.
        if (clockwise == ccw(a, b, c)) {
            cout << "NO" << endl;
            return 0;
        } else {
            clockwise ^= 1;
        }

        if (!ccw(a, b, c))
            // We are looking at an outer angle.
            // We check if the angle at b is acute.
            if (angle(a - b, c - b) >= M_PI / 2) {
                cout << "NO" << endl;
                return 0;
            }
    }

    cout << "YES" << endl;
}