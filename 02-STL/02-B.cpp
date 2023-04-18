#include <iostream>
#include <map>
#include <unordered_set>

int main() {
    int N, M, B, n;
    std::cin >> N >> M >> B;

    // Dictionary of buckets.
    std::map<int, std::unordered_set<int>> buckets;

    // Read all rolls along with index.
    for (int i = 0; i < M; i++) {
        std::cin >> n;
        buckets[n].insert(i + 1);
    }

    while (B--) {
        int b, a, i;
        std::cin >> b >> a;

        // Read bet numbers.
        std::unordered_set<int> bet;
        while (a-- and std::cin >> i)
            bet.insert(i);

        // STL comparing the unordered set to check the bet.
        if (bet != buckets[b])
            std::cout << "INCORRECT" << std::endl;
        else
            std::cout << "CORRECT" << std::endl;
    }
}