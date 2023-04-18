#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <set>

int main() {
    int N, M;
    std::cin >> N >> M;
    std::string key;

    // Dictionary with first and last character as key.
    // Set has the advantage of being sorted and removing duplicates.
    std::map<std::string, std::set<std::string>> words;

    std::string in, a, b;
    while (N--) {
        // Extract key from read word and store.
        // std::cin reads until whitespace (words).
        std::cin >> in;
        key = in.substr(0, 1) + in.substr(in.length() - 1);

        words[key].insert(in);
    }

    while (M--) {
        std::cin >> a >> b;
        key = a + b;

        // Extract list of words based on key.
        auto res = words[key];

        // Check if category is empty.
        if (res.size() == 0) {
            std::cout << "Empty category!" << std::endl;
            continue;
        }

        // Print words.
        for (auto w : res)
            std::cout << w << " ";
        std::cout << std::endl;
    }
}