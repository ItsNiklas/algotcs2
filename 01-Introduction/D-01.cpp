#include <iostream>
#include <map>
#include <vector>

int main() {
    int N, M, a;
    std::cin >> N >> M;

    std::map<int, std::vector<int>> int_map;

    // Preprocess by storing indices in a vector, accessible by a map.
    for (int i = 0; i < N; i++) {
        std::cin >> a;
        int_map[a].push_back(i);
    }

    // Query indices.
    while (M--) {
        std::cin >> a;
        if (int_map[a].empty()) {
            std::cout << "None!" << std::endl;
            continue;
        }
        for (const auto &i : int_map[a]) {
            std::cout << i + 1 << ' ';
        }
        std::cout << std::endl;
    }
}