#include <iostream>

long long ipow(long long base, long long exp) {
    long long result = 1;
    while (true) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

int main() {
    long long T, a, n;
    std::cin >> T;

    // Use custom ipow.
    while (T--) {
        std::cin >> a >> n;
        std::cout << ipow(a, n) << std::endl;
    }
}
