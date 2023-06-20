#include <bits/stdc++.h>
using namespace std;
typedef long double lf;

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

lf dot(vec3 a, vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
vec3 cross(vec3 a, vec3 b) {
    return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

vector<vector<int>> make_graph(const vector<int> &trigs) {
    int n = trigs.size() / 3;
    vector<vector<int>> edges(n);
    map<pair<const int &, const int &>, int> t;
    for (int i = 0; i < n; i++) {
        for (int v = 0; v < 3; v++) {
            auto e = minmax(trigs[3 * i + v], trigs[3 * i + (v + 1) % 3]);
            if (t.count(e)) {
                int j = t[e];
                edges[i].push_back(j);
                edges[j].push_back(i);
            } else {
                t[e] = i;
            }
        }
    }
    return edges;
}

void orient(int *i, int *j) {
    for (int k1 = 0; k1 < 2; k1++)
        for (int l1 = 0; l1 < 3; l1++)
            if (i[k1] == j[l1])
                for (int k2 = k1 + 1; k2 < 3; k2++)
                    for (int l2 = 0; l2 < 3; l2++)
                        if (i[k2] == j[l2]) {
                            bool r1 = k2 - k1 < 2;
                            bool r2 = (abs(l2 - l1) < 2) ^ (l1 < l2);
                            if (r1 ^ r2)
                                swap(j[l1], j[l2]);
                        }
}

void reorder_trigs(vector<int> &trigs) {
    int n = trigs.size() / 3, v;
    auto edges = make_graph(trigs);
    vector<bool> used(n, 0);
    stack<int> s;
    s.push(0);
    used[0] = 1;
    while (!s.empty()) {
        v = s.top();
        s.pop();
        for (int w : edges[v]) {
            if (!used[w]) {
                used[w] = 1;
                orient(&trigs[3 * v], &trigs[3 * w]);
                s.push(w);
            }
        }
    }
}

lf volume(vector<vec3> verts, vector<int> trigs) {
    reorder_trigs(trigs);
    lf res = 0;
    int n = trigs.size() / 3;
    vec3 o = verts[trigs[0]];
    for (int i = 0; i < n; i++) {
        vec3 a = verts[trigs[3 * i]];
        vec3 b = verts[trigs[3 * i + 1]];
        vec3 c = verts[trigs[3 * i + 2]];
        vec3 nrm = cross(b - a, c - a);
        res += dot(nrm, c - o);
    }
    return abs(res) / 6.0;
}
