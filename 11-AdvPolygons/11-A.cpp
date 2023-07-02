#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct vec3 {
    double x, y, z;
    vec3(double x, double y, double z) : x(x), y(y), z(z) {}
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
    vec3 &operator*=(const double &o) {
        x *= o;
        y *= o;
        z *= o;
        return *this;
    }
    vec3 &operator/=(const double &o) {
        x /= o;
        y /= o;
        z /= o;
        return *this;
    }
    friend vec3 operator+(vec3 a, const vec3 &b) { return a += b; }
    friend vec3 operator-(vec3 a, const vec3 &b) { return a -= b; }
    friend vec3 operator-(const vec3 &a) { return vec3(-a.x, -a.y, -a.z); }
    friend vec3 operator*(vec3 a, const double &b) { return a *= b; }
    friend vec3 operator*(const double &b, vec3 a) { return a *= b; }
    friend vec3 operator/(vec3 a, const double &b) { return a /= b; }
    friend std::ostream &operator<<(std::ostream &out, const vec3 v) {
        return out << "(" << v.x << "," << v.y << "," << v.z << ")";
    }
};
double dot(vec3 a, vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
vec3 cross(vec3 a, vec3 b) {
    return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
double det(vec3 a, vec3 b, vec3 c) { return dot(a, cross(b, c)); }
double norm(vec3 a) { return sqrt(dot(a, a)); }
double angle(vec3 a, vec3 b) { return acos(dot(a, b) / (norm(a) * norm(b))); }

/*
Output the surface area of the space ship (polyhedron).
*/

double area_triangle(vec3 a, vec3 b, vec3 c) { return norm(cross(b - a, c - a)) / 2; }

std::vector<vec3> vertices;

int main() {
    // V: numbers of vertices.
    // F: numbers of faces.
    int V, F, x, y, z, j, k, l;

    std::cin >> V >> F;

    // V lines giving the vertex coordinates.
    for (int i = 0; i < V; i++) {
        // the i-th vertex has coordinates (x_i, y_i, z_i)^T.
        std::cin >> x >> y >> z;
        vertices.push_back(vec3(x, y, z));
    }

    double area = 0;

    // F lines giving the faces.
    for (int i = 0; i < F; i++) {
        // j_i, k_i and l_i – the indices of the vertices making up the i-th face
        std::cin >> j >> k >> l;
        area += area_triangle(vertices[j], vertices[k], vertices[l]);
    }

    std::cout << std::fixed << std::setprecision(8) << area << std::endl;
}