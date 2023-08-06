#include <bits/stdc++.h>
using namespace std;

const int K = 26;       // alphabet size
const int NMAX = 10000; // max. number of vertices

struct vertex {
    int next[K]; // child links
    bool leaf;   // marker that a word ends here
    int p;       // parent link
    char pch;    // next[pch] = current node
    int link;    // suffix link
    int go[K];   // node to go to for given character in DFA
};

vertex t[NMAX + 1]; // array nodes are stored in
int sz;             // index of next free space for node

void init() {
    t[0].p = t[0].link = -1;
    memset(t[0].next, 255, sizeof t[0].next);
    memset(t[0].go, 255, sizeof t[0].go);
    sz = 1;
}

void add_string(const string &s) {
    int v = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i] - 'a';
        if (t[v].next[c] == -1) {
            memset(t[sz].next, 255, sizeof t[sz].next);
            memset(t[sz].go, 255, sizeof t[sz].go);
            t[sz].link = -1;
            t[sz].p = v;
            t[sz].pch = c;
            t[v].next[c] = sz++;
        }
        v = t[v].next[c];
    }
    t[v].leaf = true;
}

bool contains_string(const string &s) {
    int v = 0;
    for (char c : s)
        if ((v = t[v].next[c - 'a']) == -1)
            return 0;
    return t[v].leaf;
}

int go(int v, char c);

int get_link(int v) {
    if (t[v].link == -1)
        if (v == 0 || t[v].p == 0)
            t[v].link = 0;
        else
            t[v].link = go(get_link(t[v].p), t[v].pch);
    return t[v].link;
}

int go(int v, char c) {
    if (t[v].go[c] == -1)
        if (t[v].next[c] != -1)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = (v == 0) ? 0 : go(get_link(v), c);
    return t[v].go[c];
}
