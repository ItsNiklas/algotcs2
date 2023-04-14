#include <cmath>
#include <iostream>

int main() {
    int N, a;
    std::cin >> N;

    while (N--) {
        std::cin >> a;
        bool two_f = false, three_f = false;

        // Check if 2^i is a factor.
        for (int i = 1; i < 30 and not two_f; i++) {
            if (!std::fmod(a, std::pow(2, i))) {
                two_f = true;
            }
        }

        // Check if 2^i is a factor.
        for (int i = 1; i < 19 and not three_f; i++) {
            if (!std::fmod(a, std::pow(3, i))) {
                three_f = true;
            }
        }

        // XOR of conditions as the filter.
        if (two_f != three_f) {
            std::cout << a << " ";
        }
    }
    std::cout << std::endl;
}