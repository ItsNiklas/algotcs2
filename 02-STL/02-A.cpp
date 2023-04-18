#include <algorithm>
#include <iostream>
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

    std::vector<std::pair<double, std::pair<int, int>>> fractions;

    // Double for loop to create all possible fractions,
    // along with their real value d.
    for (const int &i : num) {
        for (const int &k : den) {
            d = (double)i / k;
            fractions.emplace_back(std::make_pair(d, std::make_pair(i, k)));
        }
    }

    // Sort by d. (Then numerator automatically)
    std::sort(fractions.begin(), fractions.end());

    // Print.
    for (size_t i = 0; i < fractions.size(); i++)
        std::cout << fractions[i].second.first << "/" << fractions[i].second.second << std::endl;
}