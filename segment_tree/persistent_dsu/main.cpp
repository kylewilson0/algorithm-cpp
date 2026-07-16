#include <iostream>
#include <vector>
#include <array>
#define LOCAL
#define fr(i, a, b) for (int i = (a); i <= (b); ++i)
#define rp(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
constexpr int N = 1e5 + 1;

struct SegmentTree {
    struct Node {
        int l, r, fa, rnk;

        Node() : l(0), r(0), fa(0), rnk(0) {
        }
    };

    vector<Node> tree{};
    int idx = 0, root = 0, len = 0;

    SegmentTree(int n) {
        len = n;
        tree.resize(N << 7);
        root = build(1, n);
    }

    int build(int s, int t) {
        int cur = ++idx;
        if (s == t) {
            tree[cur].fa = s;
            tree[cur].rnk = 1;
            return cur;
        }
        int m = s + ((t - s) >> 1);
        tree[cur].l = build(s, m);
        tree[cur].r = build(m + 1, t);
        return cur;
    }

    int updateRnk(int pre, int s, int t, int pos, int val) {
        int cur = ++idx;
        tree[cur] = tree[pre];
        if (s == t) {
            tree[cur].rnk = max(tree[cur].rnk, val);
            return cur;
        }
        int m = s + ((t - s) >> 1);
        if (pos <= m) {
            tree[cur].l = updateRnk(tree[pre].l, s, m, pos, val);
        } else {
            tree[cur].r = updateRnk(tree[pre].r, m + 1, t, pos, val);
        }
        return cur;
    }

    int queryRnk(int p, int s, int t, int pos) {
        if (s == t) return tree[p].rnk;
        int m = s + ((t - s) >> 1);
        if (pos <= m) {
            return queryRnk(tree[p].l, s, m, pos);
        }
        return queryRnk(tree[p].r, m + 1, t, pos);
    }

    int update(int pre, int s, int t, int p, int x) {
        int cur = ++idx;
        tree[cur] = tree[pre];
        if (s == t) {
            tree[cur].fa = x;
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

    int query(int pre, int s, int t, int pos) {
        if (s == t) return tree[pre].fa;
        int m = s + ((t - s) >> 1);
        if (pos <= m) return query(tree[pre].l, s, m, pos);
        return query(tree[pre].r, m + 1, t, pos);
    }

    int findRoot(int pre, int pos) {
        int fa = query(pre, 1, len, pos);
        if (pos == fa) return fa;
        return findRoot(pre, fa);
    }

    int unite(int p, int a, int b) {
        int fa = findRoot(p, a), fb = findRoot(p, b);
        if (fa == fb) return p;
        int rnk_a = queryRnk(p, 1, len, fa), rnk_b = queryRnk(p, 1, len, fb);
        if (rnk_a > rnk_b) {
            swap(fa, fb);
            swap(rnk_a, rnk_b);
        }
        int lastRoot = update(p, 1, len, fa, fb);
        return updateRnk(lastRoot, 1, len, fb, rnk_a + 1);
    }
};

array<int, N << 1> root{};

// persistent segment tree luogu3402
void solve() {
    int n, m, op, a, b, v;
    cin >> n >> m;
    SegmentTree seg(n);
    root[0] = seg.root;
    fr(i, 1, m) {
        cin >> op;
        if (op == 1) {
            cin >> a >> b;
            root[i] = seg.unite(root[i - 1], a, b);
        } else if (op == 2) {
            cin >> v;
            root[i] = root[v];
        } else {
            cin >> a >> b;
            root[i] = root[i - 1];
            int fa = seg.findRoot(root[i], a), fb = seg.findRoot(root[i], b);
            cout << (fa == fb) << '\n';
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
