#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#define LOCAL

using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int N = 1e5 + 1;


struct operation {
    char op;
    int l, r, k, x, y;
};

array<operation, N> opt;
array<int, N> a{}, root{};
array<int, 2 * N> b{};
array<int, N> l_root{}, r_root{};

int n, m, cnt = 0, len, l_cnt, r_cnt;

int get_id(int x) {
    return lower_bound(b.begin(), b.begin() + len, x) - b.begin() + 1;
}

struct Node {
    int l, r, d;
};

struct SegmentTree {
    vector<Node> tree{};
    int idx = 0;

    SegmentTree() {
        tree.resize(N << 7);
        // root = build(1, len);
    }

    int build(ll s, ll t) {
        int cur = ++idx;
        if (s == t) return cur;
        int m = s + ((t - s) >> 1);
        tree[cur].l = build(s, m);
        tree[cur].r = build(m + 1, t);
        return cur;
    }

    void update(int &cur, int s, int t, int pos, int x) {
        if (!cur) cur = ++idx;
        tree[cur].d += x;
        if (s == t) return;
        int m = s + ((t - s) >> 1);
        if (pos <= m) {
            update(tree[cur].l, s, m, pos, x);
        } else {
            update(tree[cur].r, m + 1, t, pos, x);
        }
    }

    void batch_update(int p, int x) {
        int pos = get_id(a[p - 1]);
        for (int i = p; i <= n; i += i & -i) {
            update(root[i], 1, len, pos, x);
        }
    }

    int query(int s, int t, int k) {
        if (s == t) return s;
        int m = s + ((t - s) >> 1), sum = 0;
        for (int i = 0; i < r_cnt; i++) sum += tree[tree[r_root[i]].l].d;
        for (int i = 0; i < l_cnt; i++) sum -= tree[tree[l_root[i]].l].d;
        if (k <= sum) {
            for (int i = 0; i < l_cnt; ++i) l_root[i] = tree[l_root[i]].l;
            for (int i = 0; i < r_cnt; ++i) r_root[i] = tree[r_root[i]].l;
            return query(s, m, k);
        }
        for (int i = 0; i < l_cnt; ++i) l_root[i] = tree[l_root[i]].r;
        for (int i = 0; i < r_cnt; ++i) r_root[i] = tree[r_root[i]].r;
        return query(m + 1, t, k - sum);
    }

    int batch_query(int l, int r, int k) {
        l_cnt = r_cnt = 0;
        for (int i = l - 1; i > 0; i -= i & -i) l_root[l_cnt++] = root[i];
        for (int i = r; i > 0; i -= i & -i) r_root[r_cnt++] = root[i];
        return query(1, len, k);
    }
};

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i], b[i] = a[i];
    }
    cnt = n;
    for (int i = 0; i < m; i++) {
        cin >> opt[i].op;
        if (opt[i].op == 'Q') {
            cin >> opt[i].l >> opt[i].r >> opt[i].k;
        } else {
            cin >> opt[i].x >> opt[i].y;
            b[cnt++] = opt[i].y;
        }
    }
    sort(b.begin(), b.begin() + cnt);
    len = unique(b.begin(), b.begin() + cnt) - b.begin();
}

// persistent segment tree luogu2617
void solve() {
    init();
    SegmentTree seg;
    for (int i = 1; i <= n; i++) {
        seg.batch_update(i, 1);
    }
    for (int i = 0; i < m; i++) {
        if (opt[i].op == 'C') {
            seg.batch_update(opt[i].x, -1);
            a[opt[i].x - 1] = opt[i].y;
            seg.batch_update(opt[i].x, 1);
        } else {
            int pos = seg.batch_query(opt[i].l, opt[i].r, opt[i].k);
            cout << b[pos - 1] << endl;
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
