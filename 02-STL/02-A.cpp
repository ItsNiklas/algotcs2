#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

int main() {
    int N, M, a;
    double d;
    std::cin >> N >> M;

    std::vector<int> num;
    std::vector<int> den;

    // Read all numerators and denomiators.
    while (N-- and std::cin >> a)
        num.emplace_back(a);

    while (M-- and std::cin >> a)
        den.emplace_back(a);

    // Decimal representation d, num, den.
    std::vector<std::tuple<double, int, int>> fractions;

    // Double for loop to create all possible fractions,
    // along with their real value d.
    for (const int &i : num) {
        for (const int &k : den) {
            d = (double)i / k;
            fractions.emplace_back(std::make_tuple(d, i, k));
        }
    }

    // Sort tuple.
    std::sort(fractions.begin(), fractions.end());

    // Print.
    for (auto tup : fractions)
        std::cout << std::get<1>(tup) << "/" << std::get<2>(tup) << std::endl;
}