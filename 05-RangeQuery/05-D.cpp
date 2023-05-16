#include <iostream>
#include <string>

// Fenwick 2D template.
const int MAXN = 1005;
int t[MAXN][MAXN];
int sum(int x, int y) {
    int result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            result += t[i][j];
    return result;
}
int sum(int x_1, int y_1, int x_2, int y_2) {
    return sum(x_2, y_2) - sum(x_1, y_2) - sum(x_2, y_1) + sum(x_1, y_1);
}
void inc(int x, int y, int delta) {
    for (int i = x; i < MAXN; i = (i | (i + 1)))
        for (int j = y; j < MAXN; j = (j | (j + 1)))
            t[i][j] += delta;
}

int main() {
    int N, M, x, y, x1, x2, y1, y2, r;
    std::string type;

    // Read width and height of the grid (unused).
    std::cin >> N >> M;

    while (std::cin >> type) {
        if (type == "RAIN") {
            // Project rainfall r in the area.
            std::cin >> x1 >> y1 >> x2 >> y2 >> r;

            // Abuse the Fenwick 2D structure
            // to increase all cells in the area by r.
            inc(x1, y1, r);
            inc(x2 + 1, y1, -r);
            inc(x1, y2 + 1, -r);
            inc(x2 + 1, y2 + 1, r);
            
        } else {
            // Request rainfall in cell (x, y).
            std::cin >> x >> y;

            if (x == -1 and y == -1) // End of input.
                break;

            // Use the Fenwick 2D implementation above to request cell x,y.
            std::cout << sum(x, y) << std::endl;
        }
    }
}
