#include <iostream>
#include <map>
#include <string>

/*
bonus should be awarded
for each contiguous subsequence of a player’s move sequence that has the
same length as the pattern P and contains each move exactly as often as
P contains it.
*/

int main() {
    // N: the number of moves in the pattern P
    // P: a string consisting of N uppercase letters
    // M: the number of player sequences you need to check

    int N, M, n;
    std::string P, s;

    std::cin >> N >> P >> M;

    std::map<char, int> m;
    for (char c : P)
        m[c]++;

    while (M--) {
        int res = 0;
        std::cin >> n >> s;

        std::map<char, int> m2; // Sliding window
        for (int i = 0; i < n; i++) {
            m2[s[i]]++; // add new char to window

            if (i >= N)
                m2[s[i - N]]--; // remove old char from window

            // Check if counts in window match counts in pattern
            if (i >= N - 1) {
                bool ok = true;
                for (auto it : m) {
                    if (m2[it.first] != it.second) {
                        ok = false;
                        break;
                    }
                }

                if (ok)
                    res++;
            }
        }

        std::cout << res << std::endl;
    }
}