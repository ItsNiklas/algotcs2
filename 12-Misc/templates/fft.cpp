#include <bits/stdc++.h>
using namespace std;
typedef double lf;
typedef complex<lf> cp;

unsigned bitreverse(unsigned v) {
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    return (v >> 16) | (v << 16);
}
vector<cp> fft(const vector<cp> &a) {
    int m = __builtin_clz(a.size()) + 1;
    vector<cp> res(a.size());
    for (int i = 0; i < a.size(); i++)
        res[bitreverse(i) >> m] = a[i];
    for (int m = 2; m <= a.size(); m *= 2) {
        cp ru = polar(1.0, -2 * M_PI / m);
        for (int k = 0; k < a.size(); k += m) {
            cp r = 1;
            for (int i = 0; i < m / 2; i++) {
                cp ep = res[k + i];
                cp op = r * res[k + i + m / 2];
                res[k + i] = ep + op;
                res[k + i + m / 2] = ep - op;
                r *= ru;
            }
        }
    }
    return res;
}
vector<cp> ifft(const vector<cp> &a) {
    lf n = 1. / a.size();
    vector<cp> res = fft(a);
    transform(res.begin(), res.end(), res.begin(), [&n](cp x) { return n * x; });
    reverse(++res.begin(), res.end());
    return res;
}
vector<cp> conv(vector<cp> a, vector<cp> b) {
    int n = a.size(), m = b.size();
    a.resize(1 << (32 - __builtin_clz(n + m - 2)), 0);
    b.resize(1 << (32 - __builtin_clz(n + m - 2)), 0);
    a = fft(a);
    b = fft(b);
    vector<cp> c(a.size());
    transform(a.begin(), a.end(), b.begin(), c.begin(),
              [](cp x, cp y) { return x * y; });
    c = ifft(c);
    c.resize(n + m - 1);
    return c;
}

int main() {
    vector<cp> a({2, -1, 5, -3, 0, 7});
    vector<cp> b({-1, 0, 1});

    vector<cp> c = conv(a, b);

    cout << fixed << setprecision(3);

    for (int i = 0; i < c.size(); i++)
        cout << c[i].real() << " ";
    cout << "\n";

    /*int n; cin >> n;
    vector<cp> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << fixed;

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";

    vector<cp> b = fft(a);
    for (int i = 0; i < n; i++)
        cout << b[i] << " ";
    cout << "\n";

    vector<cp> c = ifft(b);
    for (int i = 0; i < n; i++)
        cout << c[i] << " ";
    cout << "\n";
    */
}
