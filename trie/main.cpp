#include <iostream>

#define fr(i, a, b) for (int i = (a); i <= (b); ++i)
#define rp(i, a, b) for (int i = (a); i >= (b); --i)
#define LOCAL

using namespace std;
constexpr int N = 3e6 + 1;

struct Node {
    int ch[112]{}, cnt = 0;
};

int getNum(char x) {
    if (x >= 'A' && x <= 'Z') return x - 'A';
    if (x >= 'a' && x <= 'z') return x - 'a' + 26;
    return x - '0' + 52;
}

struct Trie {
    int idx = 0;
    Node tree[N];

    int insert(string &st) {
        int p = 0;
        for (char c: st) {
            int x = getNum(c);
            if (!tree[p].ch[x]) tree[p].ch[x] = ++idx;
            p = tree[p].ch[x];
            tree[p].cnt++;
        }
        return p;
    }

    int find(string &st) {
        int p = 0;
        for (char c: st) {
            int x = getNum(c);
            if (!tree[p].ch[x]) return 0;
            p = tree[p].ch[x];
        }
        return tree[p].cnt;
    }
} trie;

void solve() {
    int n, q;
    string st;
    cin >> n >> q;
    fr(i, 0, n-1) {
        cin >> st;
        trie.insert(st);
    }
    fr(i, 0, q-1) {
        cin >> st;
        cout << trie.find(st) << '\n';
    }
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        for (int i = 0; i <= trie.idx; i++) {
            trie.tree[i].cnt = 0;
            for (int &j: trie.tree[i].ch) j = 0;
        }
        trie.idx = 0;
        solve();
    }
    return 0;
}
