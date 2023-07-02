#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct vec2 {
    double x, y;
    vec2() : x(0), y(0) {}
    vec2(double x, double y) : x(x), y(y) {}
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
    vec2 &operator*=(const double &o) {
        x *= o;
        y *= o;
        return *this;
    }
    vec2 &operator/=(const double &o) {
        x /= o;
        y /= o;
        return *this;
    }
    friend vec2 operator+(vec2 a, const vec2 &b) { return a += b; }
    friend vec2 operator-(vec2 a, const vec2 &b) { return a -= b; }
    friend vec2 operator*(vec2 a, const double &b) { return a *= b; }
    friend vec2 operator*(const double &b, vec2 a) { return a *= b; }
    friend vec2 operator/(vec2 a, const double &b) { return a /= b; }
    friend bool operator==(const vec2 &a, const vec2 &b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator!=(const vec2 &a, const vec2 &b) { return !(a == b); }
    friend std::ostream &operator<<(std::ostream &out, const vec2 v) {
        return out << "(" << v.x << "," << v.y << ")";
    }
};

double cross(vec2 a, vec2 b) { return a.x * b.y - a.y * b.x; }

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

typedef std::vector<vec2> poly;

double area(const poly &p) {
    double res = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = i ? i - 1 : p.size() - 1;
        res += (p[i].y + p[j].y) * (p[i].x - p[j].x);
    }
    return 0.5 * std::abs(res);
}

/*
He needs to know beforehand exactly how
much air will be required. While you do
have a description of the space station as a polyhedron (i.e. via vertices and
polygonal faces), you didn’t find any concrete information about the station’s
volume. It seems you will have to calculate it yourself...
*/
vec3 computeNormal(const std::vector<vec3> &poly) {
    // Compute the cross product of these two vectors
    vec3 normal = vec3(0, 0, 0);

    // Slide window of three points along polygon until normal is not zero
    vec3 first = poly[0];
    for (int i = 2; i < poly.size(); i++) {
        vec3 second = poly[i];
        vec3 third = poly[i - 1];

        normal += cross(second - first, third - first);
    }

    // if (!found_normal) {
    //     for (const auto &p : poly) {
    //         cerr << p << endl;
    //     }
    //     cerr << "no normal :(" << endl;
    //     exit(0);
    // }

    // Normalize the normal vector to ensure it is unit length
    // normal /= norm(normal);

    return normal;
}

double computeArea(const std::vector<vec3> &poly) {
    // vector<vec2> points2D = reduce3Dto2D(poly);
    // double a = area(points2D);
    int n = poly.size();

    // let o be center of gravity
    vec3 o = vec3(0, 0, 0);
    for (const auto &p : poly) {
        o += p;
    }
    o /= n;

    vec3 av = vec3(0, 0, 0);

    for (int k = 0; k < n; k++) {
        vec3 base1 = poly[k] - o;
        vec3 base2 = poly[(k + 1) % n] - o;
        av += 0.5 * cross(base1, base2);
    }

    double a = norm(av);

    // cerr << "area: " << a << endl;

    return std::abs(a);
}

std::vector<vec3> vertices;
std::vector<std::vector<vec3>> faces;
vec3 origin;

double volume(std::vector<std::vector<vec3>> polys) {
    double res = 0;

    for (const auto &poly : polys) {
        // arbitrary point on face
        vec3 q = poly[0];

        // Compute area of polygon
        double area = computeArea(poly);

        if (area <= 1e-13) {
            continue;
        }

        // Compute normal of polygon
        vec3 normal = computeNormal(poly);

        // Add signed volume of pyramid to running total
        res += dot(normal, q - origin);
    }

    return std::abs(res) / 6.0;
}

int main() {
    // V: numbers of vertices.
    // F: numbers of faces.
    int V, F, n, k;
    double x, y, z;

    std::cin >> V >> F;

    if (V <= 3 or F <= 3) {
        std::cout << std::fixed << std::setprecision(8) << (double)0 << std::endl;
        return 0;
    }

    // V lines giving the vertex coordinates.
    for (int i = 0; i < V; i++) {
        // the i-th vertex has coordinates (x_i, y_i, z_i)^T.
        std::cin >> x >> y >> z;
        vertices.push_back(vec3(x, y, z));
    }

    origin = vertices[0];

    // F lines giving the faces.
    for (int i = 0; i < F; i++) {
        // the i-th face is described by the number of vertices n followed by
        // the n_i indices of the vertices in clockwise order (viewed from the outside)
        std::cin >> n;
        std::vector<vec3> face;
        for (int j = 0; j < n; j++) {
            std::cin >> k;
            face.push_back(vertices[k]);
        }

        faces.push_back(face);
    }

    std::cout << std::fixed << std::setprecision(8) << volume(faces) << std::endl;
}