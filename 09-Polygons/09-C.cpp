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
poly hull(vector<vec2> points) {
    sort(points.begin(), points.end(), cmp_lex);
    vector<vec2> lo, hi;
    vector<vec2> on_boundary;
    for (vec2 p : points) {
        if (!cw(p, points[0], points[points.size() - 1])) {
            while (hi.size() > 1 && !cw(hi[hi.size() - 2], hi[hi.size() - 1], p)) {
                on_boundary.push_back(hi.back());
                hi.pop_back();
            }
            hi.push_back(p);
        }
        if (!ccw(p, points[0], points[points.size() - 1])) {
            while (lo.size() > 1 && !ccw(lo[lo.size() - 2], lo[lo.size() - 1], p)) {
                on_boundary.push_back(lo.back());
                lo.pop_back();
            }
            lo.push_back(p);
        }
    }
    poly res(lo.begin(), lo.end());
    for (int i = hi.size() - 2; i > 0; i--)
        res.push_back(hi[i]);

    for (vec2 p : on_boundary) {
        for (size_t i = 0; i < res.size(); i++) {
            vec2 v1 = res[i] - p;
            vec2 v2 = res[(i + 1) % res.size()] - p;
            if (cross(v1, v2) == 0 && dot(v1, v2) <= 0) {
                // insert between
                res.insert(res.begin() + i + 1, p);
                break;
            }
        }
    }

    return res;
}

lf area_raw(const poly &p) {
    lf res = 0;
    for (size_t i = 0; i < p.size(); i++) {
        int j = i ? i - 1 : p.size() - 1;
        res += (p[i].y + p[j].y) * (p[i].x - p[j].x);
    }
    return 0.5 * res;
}

lf area(const poly &p) { return abs(area_raw(p)); }

/*
Thus you decided to modify it by attaching a bunch of smaller polygons to
it in such a way that no two of them have the same color, no two share a side
with one another and the new polygon’s shape exactly matches the convex
hull of the current polygon (note that for technical reasons the polygons you
attach cannot have width 0 anywhere (except at their corners of course), so
you can’t just print one large polygon that slings around the entire old one
and completes it to its convex hull). However, you’re not sure whether you
still have enough of the colored filaments to do this. So let’s find out!
*/

// This function calculates the areas added by the convex hull
vector<lf> calculate_added_areas(const vector<vec2> &points, const poly &hull) {
    vector<lf> addedAreas;
    for (size_t i = 0; i < hull.size(); i++) {
        int j = (i + 1) % hull.size();

        // Find all points in the original polygon between hull[i] and hull[j]
        vector<vec2> p;
        auto start = find(points.begin(), points.end(), hull[i]);
        auto end = find(points.begin(), points.end(), hull[j]);
        if (start < end) {
            p.insert(p.end(), start, end + 1);
        } else {
            p.insert(p.end(), start, points.end());
            p.insert(p.end(), points.begin(), end + 1);
        }

        // Ignore if there are only two points (not a polygon)
        if (p.size() <= 2)
            continue;

        // Calculate and add the area of the polygon segment
        addedAreas.push_back(area(p));
    }
    return addedAreas;
}

// This function determines if the areas can be filled with the available colors
bool can_fill_areas(const vector<lf> &areas, const vector<int> &colorAmounts,
                    int colorCount) {
    // Sort areas and color amounts in descending order
    vector<lf> sortedAreas = areas;
    vector<int> sortedColors = colorAmounts;
    sort(sortedAreas.begin(), sortedAreas.end(), greater<lf>());
    sort(sortedColors.begin(), sortedColors.end(), greater<int>());

    // Check if each area can be filled by a color
    for (size_t i = 0; i < sortedAreas.size(); i++) {
        // If there are no more colors or if the largest color is smaller than the area,
        // return false
        if ((int)i >= colorCount || sortedColors[i] < sortedAreas[i]) {
            return false;
        }
    }

    // If all areas can be filled, return true
    return true;
}

int main() {
    int pointCount, colorCount, x, y;

    // Read number of points
    cin >> pointCount;

    // Read the points
    vector<vec2> points;
    for (int i = 0; i < pointCount; i++) {
        cin >> x >> y;
        points.push_back(vec2(x, y));
    }

    // Ensure the points are in counter-clockwise order
    if (area_raw(points) > 0) {
        reverse(points.begin(), points.end());
    }

    // Read number of colors
    cin >> colorCount;

    // Read the amounts of each color
    vector<int> colorAmounts;
    for (int i = 0; i < colorCount; i++) {
        cin >> x;
        colorAmounts.push_back(x);
    }

    // Compute the convex hull
    poly h = hull(points);

    // Calculate the areas added by the convex hull
    vector<lf> addedAreas = calculate_added_areas(points, h);

    // Determine if the areas can be filled with the available colors
    bool canFill = can_fill_areas(addedAreas, colorAmounts, colorCount);

    cout << (canFill ? "YES" : "NO") << endl;
}
