#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::vector<std::vector<int>> c;
std::vector<int> p;

int l, n;
bool cmp(int i, int j) {
    if (c[l][i] != c[l][j])
        return c[l][i] < c[l][j];
    return ((i + (1 << l) < n) ? c[l][i + (1 << l)] : -1) <
           ((j + (1 << l) < n) ? c[l][j + (1 << l)] : -1);
}

void construct_suffix_array(std::string s) {
    n = s.length();
    p.resize(n);
    std::iota(p.begin(), p.end(), 0);
    c.push_back(std::vector<int>(s.begin(), s.end()));
    for (int k = n; k > 0; k /= 2, l++) {
        c.push_back(c.back());
        sort(p.begin(), p.end(), cmp);
        c.back()[p[0]] = 0;
        for (int i = 1, j = 0; i < n; i++)
            c.back()[p[i]] = (j += cmp(p[i - 1], p[i]));
    }
}

std::vector<int> logsize;
void precalc(int n) {
    logsize.resize(n + 1);
    for (int i = 1, l = 0; i <= n; l++)
        while (i <= (2 << l) && i <= n)
            logsize[i++] = l;
}

int compare(int i, int j, int l) {
    int lg = logsize[l];
    std::pair<int, int> a = {c[lg][i], c[lg][i + l - (1 << lg)]};
    std::pair<int, int> b = {c[lg][j], c[lg][j + l - (1 << lg)]};
    return a == b ? 0 : a < b ? -1 : 1;
}

int lcp(int i, int j) {
    int ans = 0;
    for (int k = c.size(); k >= 0; --k)
        if (c[k][i] == c[k][j]) {
            ans += 1 << k;
            i += 1 << k;
            j += 1 << k;
        }
    return ans;
}

const int MAXN = 100005;

int h[MAXN];
int pinv[MAXN];

void kasai(std::string s, int n) {
    for (int i = 0; i < n; i++)
        pinv[p[i]] = i;

    for (int i = 0, k = 0; i < n; i++) {
        if (pinv[i] == n - 1) {
            k = 0;
            continue;
        }

        int j = p[pinv[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            k++;
        h[pinv[i]] = k;
        k = std::max(0, k - 1);
    }
}

int main() {
    std::string s;
    int M, a, b, c, d;

    std::cin >> s >> M;

    construct_suffix_array(s);

    precalc((int)s.size());

    while (M--) {
        std::cin >> a >> b >> c >> d;
        a--;
        b--;
        c--;
        d--;

        // substrings s[a, ..., b] and s[c, ..., d]
        int l1 = b - a + 1;
        int l2 = d - c + 1;

        if (l1 != l2) {
            std::cout << "No" << std::endl;
            continue;
        }

        std::cout << (compare(a, c, l1) == 0 ? "Yes" : "No") << std::endl;
    }
}