#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

const int MAXN = 1000;
int n, k;

long ask(std::vector<int> v) {
    std::cout << "? ";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    long s;
    std::cin >> s;
    return s;
}

void finish(std::vector<int> a) {
    std::cout << "! ";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

// LU decomposition template.
long double A[MAXN][MAXN], b[MAXN];
int p[MAXN], dim;
void lu_decomp() {
    std::iota(p, p + dim, 0);
    for (int i = 0; i < dim; i++) {
        std::pair<long double, int> piv = std::make_pair(std::fabs(A[i][i]), i);
        for (int j = i + 1; j < dim; j++)
            piv = std::max(piv, std::make_pair(std::fabs(A[j][i]), j));
        int pivind = piv.second;
        std::swap(p[i], p[pivind]);
        for (int k = 0; k < dim; k++)
            std::swap(A[i][k], A[pivind][k]);
        for (int j = i + 1; j < dim; j++) {
            A[j][i] /= A[i][i];
            for (int k = i + 1; k < dim; k++)
                A[j][k] -= A[j][i] * A[i][k];
        }
    }
}
void solve_lu() {
    std::vector<long double> bp(b, b + dim);
    for (int i = 0; i < dim; i++)
        b[i] = bp[p[i]];
    for (int j = 0; j < dim; j++)
        for (int k = 0; k < j; k++)
            b[j] -= A[j][k] * b[k];
    for (int j = dim - 1; j >= 0; j--) {
        for (int k = dim - 1; k > j; k--)
            b[j] -= A[j][k] * b[k];
        b[j] /= A[j][j];
    }
}

int main() {
    std::cin >> n >> k;

    // STEP 1: Ask for the first k+1 elements!
    dim = k + 1;
    for (int i = 0; i < k + 1; i++) {
        std::vector<int> v(k + 1);

        std::fill(v.begin(), v.end(), 1);

        // Set one element of v to 0.
        v[(i + 1) % (k + 1)] = 0;

        std::vector<int> q;
        for (int j = 0; j < k + 1; j++) {
            if (v[j] == 1) {
                q.push_back(j + 1);
            }
        }
        b[i] = ask(q);

        // Set i-th row of A to v.
        for (int j = 0; j < k + 1; j++) {
            A[i][j] = v[j];
        }
    }

    // Solve the system of linear equations.
    lu_decomp();
    solve_lu();

    // Round all values in b to nearest int into solution
    std::vector<int> solution;
    for (int i = 0; i < k + 1; i++) {
        solution.push_back((int)std::round(b[i]));
    }

    // STEP 2: Ask for the next n-k-1 elements!
    for (int i = k + 1; i < n; i++) {
        // ask for the next element
        std::vector<int> q;

        // we need to find the i+1 element
        q.push_back(i + 1);

        // push_back counting down from i+1 until q has k elements
        for (int j = i; j >= 0 && (int)q.size() < k; j--) {
            q.push_back(j);
        }

        // new number is ask(q) - sum of the (k-1) last elements in solution
        solution.push_back(ask(q) -
                           std::accumulate(solution.end() - k + 1, solution.end(), 0));
    }

    finish(solution);
}
