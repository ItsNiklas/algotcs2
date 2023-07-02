#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct vec3 {
    double x, y, z;
    vec3() : x(0), y(0), z(0) {}
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

double sphere_angle(vec3 a, vec3 b, vec3 c) {
    double y = norm(b) * det(a, b, c);
    double x = dot(cross(b, a), cross(b, c));
    double t = atan2(y, x);
    return t < 0 ? t + 2 * M_PI : t;
}

double sphere_area(std::vector<vec3> p) {
    int n = p.size();
    double res = -(n - 2) * M_PI;
    for (int i = 0; i < n; i++) {
        int q = i ? i - 1 : n - 1;
        int s = i + 1 < n ? i + 1 : 0;
        res += sphere_angle(p[s], p[i], p[q]);
    }
    return std::min(res, 4 * M_PI - res);
}

int main() {
    vec3 star;
    std::cin >> star.x >> star.y >> star.z;

    int n;
    std::cin >> n;
    std::vector<vec3> vertices(n);

    for (int i = 0; i < n; ++i)
        std::cin >> vertices[i].x >> vertices[i].y >> vertices[i].z;

    // Idea: Map the star to the origin, and project the vertices to the unit sphere.
    vec3 origin = -star;
    for (int i = 0; i < n; ++i)
        vertices[i] += origin;

    double ratio = sphere_area(vertices) / (4 * M_PI);

    std::cout << std::fixed << std::setprecision(8) << ratio << std::endl;

    return 0;
}