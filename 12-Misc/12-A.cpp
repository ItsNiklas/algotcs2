#include <algorithm>
#include <iostream>
#include <limits>

int main() {
    // Idea: The maximum value must lie at the corners.
    long long a, b, x, y;
    std::cin >> a >> b;

    int N;
    std::cin >> N;

    // Compute the maximum value of a * x + b * y
    // for all x, y in the input.
    long long res = std::numeric_limits<long long>::min();
    for (int i = 0; i < N; i++) {
        std::cin >> x >> y;
        res = std::max(res, a * x + b * y);
    }

    std::cout << res << std::endl;
}