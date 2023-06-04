#include <iostream>
#include <vector>

int N, K, n;
std::vector<int> stalls;

// Binary search, predicate function check.
bool check(int d) {
    // Check if it is possible to place K cows with minimum distance d.
    int last = stalls[0], cows = 1;
    for (int i = 1; i < N; i++) {
        if (stalls[i] - last >= d) {
            cows++;
            last = stalls[i];
        }
    }
    return cows >= K;
}

int main() {
    std::cin >> N >> K;

    // Read input.
    while (std::cin >> n) {
        stalls.push_back(n);
    }

    // Binary search to find minimal d where check(d) is true.
    // left is 0, right is last element minus first element.
    int l = 0, r = stalls[N - 1] - stalls[0];
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    // Print answer.
    std::cout << l << std::endl;
}
