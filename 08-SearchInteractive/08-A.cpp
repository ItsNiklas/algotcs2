#include <cmath>
#include <iomanip>
#include <iostream>

// Different velocities and cutpoint.
int vp, vf;
double a;

// Convex function which we want to minimize.
double f(double x) {
    // Chosing x as the cutpoint.
    // Return the total time needed.

    // We start at (0,1) with speed vp.
    // We cross the boundary and change speed to vf at (x,a).
    // We end at (1,0).
    double t1 = std::sqrt(x * x + (1 - a) * (1 - a)) / vp;
    double t2 = std::sqrt((1 - x) * (1 - x) + a * a) / vf;
    return t1 + t2;
}

// Ternary search template.
double minimize(double l, double r, double eps) {
    while (r - l > eps) {
        double x1 = l + (r - l) / 3.0;
        double x2 = l + 2.0 * (r - l) / 3.0;
        if (f(x1) > f(x2))
            l = x1;
        else
            r = x2;
    }
    return l;
}

int main() {
    // Read input.
    std::cin >> vp >> vf >> a;

    // Print answer with fixed precision.
    std::cout << std::fixed << std::setprecision(6) << minimize(0, 1, 1e-6)
              << std::endl;
}
