#include <string>
#include <iostream>

// Fenwick 3D template.
const int MAXN = 505, MAXT = 1005;
int fenwick[MAXN][MAXN][MAXT]; // 1 GB!
int sum(int x, int y, int z) {
    int result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1)
                result += fenwick[i][j][k];
    return result;
}
int sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    return sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) - sum(x2, y2, z1 - 1) +
           sum(x1 - 1, y1 - 1, z2) + sum(x1 - 1, y2, z1 - 1) + sum(x2, y1 - 1, z1 - 1) -
           sum(x1 - 1, y1 - 1, z1 - 1);
}
void inc(int x, int y, int z, int delta) {
    for (int i = x; i < MAXN; i = (i | (i + 1)))
        for (int j = y; j < MAXN; j = (j | (j + 1)))
            for (int k = z; k < MAXT; k = (k | (k + 1)))
                fenwick[i][j][k] += delta;
}

int main() {
    int t, n, x, y, r, p, x1, x2, y1, y2;
    std::string type;

    // Main loop.
    while (std::cin >> t >> type) {
        if (t == -1) // End of input.
            break;

        if (type == "SIGHTING") {
            // signaling a sighting of n enemy ships in sector (x, y) on day t
            std::cin >> n >> x >> y;

            inc(x, y, t, n);

        } else if (type == "TRAVEL") {
            // signaling that on day t a trade ship requests whether sector (x, y) is
            // safe enough for it to go there – specifically, whether in the past p days
            // less than n enemy ships were sighted in the r-cube of sectors around (x, y).
            // the output should be YES if it is safe and NO otherwise
            std::cin >> p >> n >> x >> y >> r;

            // Use the Fenwick 3D implementation to request cells with range r in the time range ]t-p, t].
            int s = sum(x - r, y - r, t - p + 1, x + r, y + r, t);
            std::cout << (s < n ? "YES" : "NO") << std::endl;

        } else if (type == "COUNTER") {
            // signaling that on day t a part of the Milky Way’s defense troops is
            // want to know exactly how many enemy ships have been sighted in area
            // [x1, x2] × [y1, y2] in the past p days.
            std::cin >> p >> x1 >> y1 >> x2 >> y2;

            // Use the Fenwick 3D implementation to request cells in the time range ]t-p, t].
            int s = sum(x1, y1, t - p + 1, x2, y2, t);
            std::cout << s << std::endl;
        }
    }
}