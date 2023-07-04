#include <iostream>
#include <random>
#include <vector>

// 3D std::std::vector class template.
struct vec3 {
    long double x, y, z;
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
long double dot(vec3 a, vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
vec3 cross(vec3 a, vec3 b) {
    return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
long double det(vec3 a, vec3 b, vec3 c) { return dot(a, cross(b, c)); }
long double norm(vec3 a) { return sqrt(dot(a, a)); }
long double angle(vec3 a, vec3 b) { return acos(dot(a, b) / (norm(a) * norm(b))); }

/*
You just stumbled upon a strange device that generates three-dimensional
data points. At first you thought they were entirely random, but by now you
are sensing a pattern – at least a certain fraction p ≥ 10% of them appear
to lie on a plane. Naturally, you now want to analyze the data and find the
plane-model that is optimal in that it fits as many of the generated points
as possible.
*/

const long double EPSI = 1e-12;

int main() {
    int N;
    std::cin >> N;
    std::vector<vec3> a;
    for (int i = 0; i < N; i++) {
        long double x, y, z;
        std::cin >> x >> y >> z;
        a.push_back(vec3(x, y, z));
    }

    int k = 3000; // Attempts at RANSAC

    // Mersene Twister engine seeded with random_device
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, N - 1);

    // Store optimal plane here
    int best_m = 0;
    std::vector<int> best_inliers;

    while (k--) {
        // Select three unique points at random
        int i = dis(gen);
        int j = dis(gen);
        while (j == i) {
            j = dis(gen);
        }
        int l = dis(gen);
        while (l == i || l == j) {
            l = dis(gen);
        }

        // Compute plane through these points
        vec3 p = a[i], q = a[j], r = a[l];
        vec3 normal = cross(q - p, r - p);

        // Lets see how many points lie on this plane...
        int m = 0;
        std::vector<int> inliers;
        for (int i = 0; i < N; i++) {
            if (std::abs(dot(normal, a[i] - p)) < EPSI) {
                m++;
                inliers.push_back(i);
            }
        }

        // If this plane is better than the best so far, update it
        if (m > best_m) {
            best_m = m;
            best_inliers = inliers;
        }
    }

    // Print the optimal plane
    std::cout << best_m << std::endl;
    for (int i : best_inliers) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}