#include <iostream>

// Fenwick template. Note that this is unsigned long long.
const int MAXN = 1e6 + 5;
unsigned long long n, a[MAXN], t[MAXN];
void inc(unsigned int i, int delta) {
    for (; i < n; i = (i | (i + 1)))
        t[i] += delta;
}
void init() {
    for (size_t i = 0; i < n; i++)
        inc(i, a[i]);
}
long long sum(int r) {
    long long res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
        res += t[r];
    return res;
}
long long sum(int l, int r) { return sum(r) - sum(l - 1); }

int main() {
    // Input.
    long long N, M, s = 0;
    char t;

    std::cin >> N >> M;
    n = N;

    for (int j = 0; j < N; j++) {
        unsigned long long ai;
        std::cin >> ai;

        // Sum and store in array.
        s += ai;
        a[j] = ai;
    }

    init();

    // Offset for the query, as we fake-rotate the queue.
    // Queue is also not a queue, but the indices are manipulated as if it were.
    int i = 0;

    while (std::cin >> t) {
        // Distinguish between query (q) and action (r)
        if (t == 'q') {
            // Query.
            int l, r;
            std::cin >> l >> r;

            // Fake-rotate the queue.
            l = (l + i - 1) % N;
            r = (r + i - 1) % N;

            if (l <= r) {
                // If l > r, we need to add the sum of the elements between r and l.
                std::cout << sum(l, r) << std::endl;
            } else {
                // Otherwise, we need to subtract the sum of the elements between r and l.
                std::cout << s - sum(r + 1, l - 1) << std::endl;
            }

        } else {
            // Action.
            // We increase the rotation offset by 1.
            i++;
        }
    }
}