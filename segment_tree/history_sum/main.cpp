#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <iomanip>

#define fixed(x) fixed<<setprecision(x)
#define LOCAL

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9 + 7;
constexpr double EPS = 1e-8;
constexpr int N = 1e5 + 1;

struct Node {
    int d, l, r;
};

struct SegmentTree {
    vector<Node> tree{};
    vector<int> lazy{};
    vector<int> *a;
    int idx = 0, sz = 0, root = 0;

    SegmentTree(int n, vector<int> &v) : sz(n) {
        tree.resize(2 * sz);
        lazy.resize(2 * sz);
        a = &v;
        build(root, 1, n);
        cout << "root=" << root << endl;
        // for (int i = 1; i < 2 * sz; ++i) {
        //     printf("%d %d %d\n", tree[i].l, tree[i].r, tree[i].d);
        // }
        // cout << endl;
    }

    void build(int &p, int s, int t) {
        if (!p) p = ++idx;
        if (s == t) {
            // cout << "s=" << s << ", a[s]=" << (*a)[s] << endl;
            tree[p].d = (*a)[s];
            return;
        }
        const int m = s + (t - s) / 2;
        build(tree[p].l, s, m);
        build(tree[p].r, m + 1, t);
        tree[p].d = tree[tree[p].l].d + tree[tree[p].r].d;
    }

    void maintain(int p) {
        if (lazy[p] <= 0) return;
        const int ls = tree[p].l, rs = tree[p].r;
        if (ls == 0) return;
        tree[ls].d += lazy[p] * (tree[ls].r - tree[ls].l + 1);
        tree[rs].d += lazy[p] * (tree[rs].r - tree[rs].l + 1);
        lazy[ls] += lazy[p];
        lazy[rs] += lazy[p];
        lazy[p] = 0;
    }

    void update(int p, int s, int t, int x, int l, int r) {
        if (l <= s && t <= r) {
            lazy[p] += x;
            tree[p].d += x;
            return;
        }
        maintain(p);
        const int m = s + (t - s) / 2, ls = tree[p].l, rs = tree[p].r;
        if (l <= m) update(ls, s, m, x, l, r);
        if (r > m) update(rs, m + 1, t, x, l, r);
        tree[p].d = tree[ls].d + tree[rs].d;
    }

    int query(int p, int s, int t, int l, int r) {
        if (l <= s && t <= r) return tree[p].d;
        const int m = s + (t - s) / 2, ls = tree[p].l, rs = tree[p].r;
        int ret = 0;
        maintain(p);
        if (l <= m) ret += query(ls, s, m, l, r);
        if (r > m) ret += query(rs, m + 1, t, l, r);
        return ret;
    }
};

// TODO
void solve() {
    int n, m, type, l, r, x;
    cin >> n >> m;
    vector<int> v(n + 1), sum(n + 1);
    for (int i = 1; i <= n; ++i) cin >> v[i];
    for (int i = 1; i <= n; ++i) {
        cout << v[i] << " ";
        sum[i] = sum[i - 1] + v[i];
    }
    cout << endl;
    SegmentTree seg(n, v);
    // for (int i = 1; i <= m; ++i) {
    //     cin >> type >> l >> r;
    //     if (type == 1) {
    //         cin >> x;
    //         seg.update(seg.root, 1, n, x, l, r);
    //     } else {
    //         int ans = (sum[r] - sum[l - 1]) * (i - 1);
    //         ans += seg.query(seg.root, 1, n, l, r);
    //         cout << ans << endl;
    //     }
    // }
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
