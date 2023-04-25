#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <map>
#include <string>

int main() {
    int N;
    std::string in;
    std::cin >> N;

    std::map<std::string, int> words;

    // Read words.
    // std::cin reads until whitespace (words).
    while (std::cin >> in) {
        // Erase all non-alpha characters using a lambda.
        in.erase(std::remove_if(in.begin(), in.end(), [](char c) { return !std::isalpha(c); }),
                 in.end());

        // Apply std::tolower using a lambda.
        std::transform(in.begin(), in.end(), in.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        // Increase word count.
        words[in]++;
    }

    // Print result.
    for (auto &p : words) {
        std::cout << p.first << " " << p.second << std::endl;
    }
}