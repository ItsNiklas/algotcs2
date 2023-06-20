#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

/*
He intends to dig out the
minimum number of posts that suffices to create a large enough gap (between
two posts, between a post and an edge of the field or between both edges of
the field). To find out how many that is, he asked you for help.
*/

int main() {
    // We identify the front side of the meadow with a segment of a coordinate axis.
    int N, W, L, R, p;
    std::vector<int> posts;

    // N: the number of posts already dug in
    // W: the width a gap must have to be able to accommodate the gate
    // L, R: the coordinates of the meadows’ boundaries
    std::cin >> N >> W >> L >> R;

    if (N == 0 and R - L >= W) {
        std::cout << 0 << std::endl;
        return 0;
    }

    // If there is no solution output -1.
    if (R - L < W) {
        std::cout << -1 << std::endl;
        return 0;
    }

    for (int i = 0; i < N; i++) {
        std::cin >> p;
        posts.push_back(p);
    }
    posts.push_back(L);
    posts.push_back(R);

    sort(posts.begin(), posts.end());

    // Output the minimum number of posts he needs to dig out,
    // Using a sweep line algorithm.
    int res = N;
    std::set<int> e;
    for (size_t i = 0; i < posts.size(); i++) {
        e.insert(posts[i]);
        while (*e.rbegin() - *e.begin() >= W) {
            res = std::min(res, (int)e.size() - 2);
            e.erase(e.begin());
        }
    }

    std::cout << res << std::endl;
}