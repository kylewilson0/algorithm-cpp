#include <iostream>
#include <vector>

#define LOCAL

using namespace std;
using ll = long long;

struct SegmentTree {
    struct Node {
        int l, r, color;
        ll d, delta;
    };

    vector<Node> tree{};
    int idx = 0, sz = 0, root = 0;

    SegmentTree(int n) : sz(n + 1) {
        tree.resize(sz << 1);
        build(root, 1, n);
    }

    void build(int &p, ll s, ll t) {
        if (!p) p = ++idx;
        if (s == t) {
            tree[p].color = s;
            return;
        }
        int m = s + ((t - s) >> 1);
        build(tree[p].l, s, m);
        build(tree[p].r, m + 1, t);
    }

    void push_up(int p) {
        int ls = tree[p].l, rs = tree[p].r;
        if (tree[ls].color == tree[rs].color) tree[p].color = tree[ls].color;
    }

    void push_down(int p, int s, int t) {
        if (!tree[p].color) return;
        int ls = tree[p].l, rs = tree[p].r;
        int m = s + ((t - s) >> 1);
        tree[ls].d += tree[p].delta * (m - s + 1);
        tree[ls].delta += tree[p].delta;
        tree[rs].d += tree[p].delta * (t - m);
        tree[rs].delta += tree[p].delta;
        tree[ls].color = tree[rs].color = tree[p].color;
        tree[p].color = 0, tree[p].delta = 0;
    }

    void update(int p, int s, int t, int x, int l, int r) {
        if (l <= s && t <= r && tree[p].color) {
            tree[p].delta += abs(tree[p].color - x);
            tree[p].d += abs(tree[p].color - x) * static_cast<ll>(t - s + 1);
            tree[p].color = x;
            return;
        }
        push_down(p, s, t);
        int m = s + ((t - s) >> 1), ls = tree[p].l, rs = tree[p].r;
        if (l <= m) update(ls, s, m, x, l, r);
        if (r > m) update(rs, m + 1, t, x, l, r);
        tree[p].d = tree[ls].d + tree[rs].d;
        push_up(p);
    }

    ll query(int p, int s, int t, int l, int r) {
        if (l <= s && t <= r) return tree[p].d;
        int m = s + ((t - s) >> 1), ls = tree[p].l, rs = tree[p].r;
        ll ret = 0;
        push_down(p, s, t);
        if (l <= m) ret += query(ls, s, m, l, r);
        if (r > m) ret += query(rs, m + 1, t, l, r);
        return ret;
    }
};

void solve() {
    int n, m, type, l, r, x;
    cin >> n >> m;
    SegmentTree seg(n);
    for (int i = 0; i < m; i++) {
        cin >> type >> l >> r;
        if (type == 1) {
            cin >> x;
            seg.update(seg.root, 1, n, x, l, r);
        } else {
            cout << seg.query(seg.root, 1, n, l, r) << '\n';
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
