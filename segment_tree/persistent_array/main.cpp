#include <iostream>
#include <vector>
#include <array>
#define LOCAL
#define fr(i, a, b) for (int i = (a); i <= (b); ++i)
#define rp(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
constexpr int N = 1e6 + 1;

struct SegmentTree {
    struct Node {
        int l, r, d;

        Node() : l(0), r(0), d(0) {
        }
    };

    vector<Node> tree{};
    int idx = 0, root = 0;

    SegmentTree(array<int, N> &a, int n) {
        tree.resize(n << 5);
        root = build(a, 1, n);
    }

    int build(array<int, N> &a, int s, int t) {
        int cur = ++idx;
        if (s == t) {
            tree[cur].d = a[s];
            return cur;
        }
        int m = s + ((t - s) >> 1);
        tree[cur].l = build(a, s, m);
        tree[cur].r = build(a, m + 1, t);
        return cur;
    }

    int update(int pre, int s, int t, int p, int x) {
        int cur = ++idx;
        tree[cur].l = tree[pre].l, tree[cur].r = tree[pre].r;
        if (s == t) {
            tree[cur].d = x;
            return cur;
        }
        int m = s + ((t - s) >> 1);
        if (p <= m) {
            tree[cur].l = update(tree[pre].l, s, m, p, x);
        } else {
            tree[cur].r = update(tree[pre].r, m + 1, t, p, x);
        }
        return cur;
    }

    int query(int pre, int s, int t, int p) {
        if (s == t) return tree[pre].d;
        int m = s + ((t - s) >> 1);
        if (p <= m) return query(tree[pre].l, s, m, p);
        return query(tree[pre].r, m + 1, t, p);
    }
};

array<int, N> a{}, b{}, root{};

// persistent segment tree luogu3919
void solve() {
    int n, m, v, op, p, c;
    cin >> n >> m;
    fr(i, 1, n) cin >> a[i];
    SegmentTree seg(a, n);
    root[0] = seg.root;
    fr(i, 1, m) {
        cin >> v >> op >> p;
        if (op == 1) {
            cin >> c;
            root[i] = seg.update(root[v], 1, n, p, c);
        } else {
            cout << seg.query(root[v], 1, n, p) << '\n';
            root[i] = root[v];
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
