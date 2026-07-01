#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#define LOCAL

using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int N = 2e5 + 1;

struct SegmentTree {
    struct Node {
        int l, r, d;
    };

    vector<Node> tree{};
    int idx = 0, root = 0;

    SegmentTree(int len, int n) {
        tree.resize(n << 5);
        root = build(1, len);
    }

    int build(ll s, ll t) {
        int cur = ++idx;
        if (s == t) return cur;
        int m = s + ((t - s) >> 1);
        tree[cur].l = build(s, m);
        tree[cur].r = build(m + 1, t);
        return cur;
    }

    int update(int last, int s, int t, int id) {
        int cur = ++idx;
        tree[cur] = {tree[last].l, tree[last].r, tree[last].d + 1};
        if (s == t) return cur;
        int m = s + ((t - s) >> 1);
        if (id <= m) {
            tree[cur].l = update(tree[last].l, s, m, id);
        } else {
            tree[cur].r = update(tree[last].r, m + 1, t, id);
        }
        return cur;
    }

    int query(int lt, int rt, int s, int t, int k) {
        if (s == t) return s;
        int l_cnt = tree[tree[rt].l].d - tree[tree[lt].l].d;
        int m = s + ((t - s) >> 1);
        if (k <= l_cnt) {
            return query(tree[lt].l, tree[rt].l, s, m, k);
        }
        return query(tree[lt].r, tree[rt].r, m + 1, t, k - l_cnt);
    }
};

array<int, N> a{}, b{}, root{};

int get_id(int x, int len) {
    return lower_bound(b.begin(), b.begin() + len, x) - b.begin() + 1;
}

int init(int n) {
    for (int i = 0; i < n; ++i) {
        cin >> a[i], b[i] = a[i];
    }
    sort(b.begin(), b.begin() + n);
    int len = unique(b.begin(), b.begin() + n) - b.begin();
    return len;
}

// persistent segment tree luogu3834
void solve() {
    int n, m, l, r, x;
    cin >> n >> m;
    int len = init(n);
    SegmentTree seg(len, n);
    root[0] = seg.root;
    for (int i = 1; i <= n; ++i) {
        int id = get_id(a[i - 1], len);
        root[i] = seg.update(root[i - 1], 1, len, id);
    }
    for (int i = 0; i < m; i++) {
        cin >> l >> r >> x;
        int pos = seg.query(root[l - 1], root[r], 1, len, x);
        cout << b[pos - 1] << endl;
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
