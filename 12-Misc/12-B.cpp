#include <algorithm>
#include <complex>
#include <iomanip>
#include <iostream>
#include <vector>

// Convolution/Folding template.
unsigned bitreverse(unsigned v) {
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    return (v >> 16) | (v << 16);
}

std::vector<std::complex<double>> fft(const std::vector<std::complex<double>> &a) {
    int m = __builtin_clz(a.size()) + 1;
    std::vector<std::complex<double>> res(a.size());
    for (int i = 0; i < a.size(); i++)
        res[bitreverse(i) >> m] = a[i];
    for (int m = 2; m <= a.size(); m *= 2) {
        std::complex<double> ru = std::polar(1.0, -2 * M_PI / m);
        for (int k = 0; k < a.size(); k += m) {
            std::complex<double> r = 1;
            for (int i = 0; i < m / 2; i++) {
                std::complex<double> ep = res[k + i];
                std::complex<double> op = r * res[k + i + m / 2];
                res[k + i] = ep + op;
                res[k + i + m / 2] = ep - op;
                r *= ru;
            }
        }
    }
    return res;
}
std::vector<std::complex<double>> ifft(const std::vector<std::complex<double>> &a) {
    double n = 1. / a.size();
    std::vector<std::complex<double>> res = fft(a);
    transform(res.begin(), res.end(), res.begin(),
              [&n](std::complex<double> x) { return n * x; });
    reverse(++res.begin(), res.end());
    return res;
}
std::vector<std::complex<double>> conv(std::vector<std::complex<double>> a,
                                       std::vector<std::complex<double>> b) {
    int n = a.size(), m = b.size();
    a.resize(1 << (32 - __builtin_clz(n + m - 2)), 0);
    b.resize(1 << (32 - __builtin_clz(n + m - 2)), 0);
    a = fft(a);
    b = fft(b);
    std::vector<std::complex<double>> c(a.size());
    transform(a.begin(), a.end(), b.begin(), c.begin(),
              [](std::complex<double> x, std::complex<double> y) { return x * y; });
    c = ifft(c);
    c.resize(n + m - 1);
    return c;
}

int main() {
    /*
    n: number of friends
    m: number of cookies per batch
    k: number of batches
    */
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::complex<double>> p(m + 1);
    for (int i = 0; i <= m; i++) {
        std::cin >> p[i];
    }

    // Only care about values in range 0 to n - 1 as we are interested in values
    // divisible by n. Apply modulo n to reduce the size of vectors we need to convolve.
    std::vector<std::complex<double>> new_p(n, 0);
    for (int i = 0; i <= m; i++) {
        new_p[i % n] += p[i];
    }

    // Convolute/Fold new_p with itself k times
    std::vector<std::complex<double>> res = new_p;
    for (int i = 1; i < k; i++) {
        res = conv(res, new_p);
        for (int i = n; i < res.size(); i++) {
            res[i % n] += res[i];
        }
        res.resize(n); // keep only the first n elements
        new_p.resize(n);
    }

    // Actually:
    // std::vector<std::complex<double>> base = new_p;
    // while (k > 0) {
    //     if (k % 2 == 1) {
    //         res = conv(res, base);
    //         for (int i = n; i < res.size(); i++) {
    //             res[i % n] += res[i];
    //         }
    //         res.resize(n); // keep only the first n elements
    //     }
    //     base = conv(base, base);
    //     for (int i = n; i < base.size(); i++) {
    //         base[i % n] += base[i];
    //     }
    //     base.resize(n); // keep only the first n elements
    //     k /= 2;
    // }

    // sum up all probabilities for values divisible by n
    // equals only the first element of res
    double ans = res[0].real();

    std::cout << std::fixed << std::setprecision(8) << ans << std::endl;
}
