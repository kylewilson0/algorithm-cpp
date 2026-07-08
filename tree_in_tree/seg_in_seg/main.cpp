#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#define LOCAL
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
constexpr int N = 5e4 + 1;

struct operation {
    int op, l, r;
    ll c;
};

struct Node1 {
    int root = 0, l, r;
};

struct Node2 {
    int l, r;
    ll sum, delta;
};

array<operation, N> opt;
array<ll, N> b{};
int n, m, cnt = 0, len;

struct SegmentTree {
    vector<Node1> tree{};
    vector<Node2> vec{};
    int tree_idx = 0, vec_idx = 0, root = 0;

    SegmentTree() {
        tree.resize(N);
        vec.resize(N * 400);
    }

    void pushdown(int p, int s, int t) {
        if (!vec[p].l) vec[p].l = ++vec_idx;
        if (!vec[p].r) vec[p].r = ++vec_idx;
        int ls = vec[p].l, rs = vec[p].r;
        int m = s + ((t - s) >> 1);
        vec[ls].delta += vec[p].delta;
        vec[ls].sum += (m - s + 1) * vec[p].delta;
        vec[rs].delta += vec[p].delta;
        vec[rs].sum += (t - m) * vec[p].delta;
        vec[p].delta = 0;
    }

    void vec_update(int &p, int s, int t, int l, int r, int x) {
        if (!p) p = ++vec_idx;
        if (l <= s && t <= r) {
            vec[p].delta += x;
            vec[p].sum += (t - s + 1) * x;
            return;
        }
        pushdown(p, s, t);
        int m = s + ((t - s) >> 1);
        if (l <= m) vec_update(vec[p].l, s, m, l, r, x);
        if (r > m) vec_update(vec[p].r, m + 1, t, l, r, x);
        vec[p].delta = 0;
        vec[p].sum = vec[vec[p].l].sum + vec[vec[p].r].sum;
    }

    ll vec_query(int p, int s, int t, int l, int r) {
        if (!p) return 0;
        if (l <= s && t <= r) return vec[p].sum;
        pushdown(p, s, t);
        int m = s + ((t - s) >> 1);
        ll ret = 0;
        if (l <= m) ret += vec_query(vec[p].l, s, m, l, r);
        if (r > m) ret += vec_query(vec[p].r, m + 1, t, l, r);
        return ret;
    }

    void tree_update(int &p, int s, int t, int l, int r, int x) {
        if (!p) p = ++tree_idx;
        vec_update(tree[p].root, 1, n, l, r, 1);
        if (s == t) return;
        int m = s + ((t - s) >> 1);
        if (x <= m) {
            tree_update(tree[p].l, s, m, l, r, x);
        } else {
            tree_update(tree[p].r, m + 1, t, l, r, x);
        }
    }

    int tree_query(int p, int s, int t, int l, int r, ll k) {
        if (!p) p = ++tree_idx;
        if (s == t) return s;
        int rs = tree[p].r;
        ll tot = vec_query(tree[rs].root, 1, n, l, r);
        int m = s + ((t - s) >> 1);
        if (tot < k) {
            return tree_query(tree[p].l, s, m, l, r, k - tot);
        }
        return tree_query(tree[p].r, m + 1, t, l, r, k);
    }
};

int get_id(int x) {
    return lower_bound(b.begin(), b.begin() + len, x) - b.begin() + 1;
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> opt[i].op >> opt[i].l >> opt[i].r >> opt[i].c;
        if (opt[i].op == 1) {
            b[cnt++] = opt[i].c;
        }
    }
    sort(b.begin(), b.begin() + cnt);
    len = unique(b.begin(), b.begin() + cnt) - b.begin();
}

// seg in seg luogu3332
void solve() {
    init();
    SegmentTree seg;
    for (int i = 0; i < m; i++) {
        if (opt[i].op == 1) {
            seg.tree_update(seg.root, 1, len, opt[i].l, opt[i].r, get_id(opt[i].c));
        } else {
            int pos = seg.tree_query(seg.root, 1, len, opt[i].l, opt[i].r, opt[i].c);
            cout << b[pos - 1] << '\n';
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
