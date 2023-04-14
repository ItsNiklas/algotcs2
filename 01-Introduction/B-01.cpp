#include <iostream>

int main() {
    unsigned long long p;
    std::cin >> p;

    // Use GCC intrinsics to calculate set bits in p.
    std::cout << __builtin_popcountll(p);
}