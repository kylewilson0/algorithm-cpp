#include <iostream>
#include <array>
#include <vector>

#define LOCAL

using namespace std;
using ll = long long;
constexpr int N = 1e5 + 1;

struct Matrix {
    static constexpr int sz = 3;
    array<array<ll, sz>, sz> a{};

    Matrix() {
        for (int i = 0; i < sz; ++i) a[i][i] = 1;
    }

    Matrix operator*(const Matrix &T) const {
        Matrix res;
        // for (int i = 0; i < sz; ++i)
        //     for (int j = 0; j < sz; ++j) {
        //         // if (i > j) continue;
        //         ll tot = 0;
        //         for (int k = 0; k < sz; ++k) tot += a[i][k] * T.a[k][j];
        //         res.a[i][j] = tot;
        //     }
        res.a[0][1] = T.a[0][1] + a[0][1];
        res.a[0][2] = T.a[0][2] + T.a[1][2] * a[0][1] + a[0][2];
        res.a[1][2] = T.a[1][2] + a[1][2];
        return res;
    }
};

inline void calc(Matrix &ma, Matrix &mb, Matrix &ans) {
    Matrix res;
    for (int i = 0; i < 2; ++i) {
        ll tt = 0;
        for (int j = 0; j < 3; ++j) {
            tt += ma.a[i][j] * mb.a[j][0];
        }
        res.a[i][0] = tt;
    }
    ans.a[0][0] = res.a[0][0], ans.a[1][0] = res.a[1][0];
}

struct SegmentTree {
    struct Node {
        int l, r;
        bool lazy;
    };

    vector<Node> tree{};
    vector<Matrix> delta{}, data{};
    vector<ll> *a;
    int idx = 0, root = 0;

    SegmentTree(int n, vector<ll> &v) {
        tree.resize(N << 2);
        delta.resize(N << 2);
        data.resize(N << 2);
        a = &v;
        build(root, 1, n);
    }

    void build(int &p, int s, int t) {
        if (!p) p = ++idx;
        if (s == t) {
            Matrix m1;
            delta[p] = m1;
            m1.a[0][0] = m1.a[1][0] = (*a)[s];
            m1.a[2][0] = 1;
            data[p] = m1;
            return;
        }
        const int m = s + ((t - s) >> 1);
        build(tree[p].l, s, m);
        build(tree[p].r, m + 1, t);
        pushup(p, 3);
        delta[p] = Matrix();
    }

    void pushup(int p, int len) {
        for (int i = 0; i < len; ++i) {
            data[p].a[i][0] = data[tree[p].l].a[i][0] + data[tree[p].r].a[i][0];
        }
    }

    void pushdown(int p) {
        if (!tree[p].lazy) return;
        const int ls = tree[p].l, rs = tree[p].r;
        if (ls == 0) return;
        tree[ls].lazy = tree[rs].lazy = true;
        delta[ls] = delta[p] * delta[ls];
        delta[rs] = delta[p] * delta[rs];
        // data[ls] = delta[p] * data[ls];
        // data[rs] = delta[p] * data[rs];
        calc(delta[p], data[ls], data[ls]);
        calc(delta[p], data[rs], data[rs]);
        delta[p] = Matrix();
        tree[p].lazy = false;
    }

    void update(int p, int s, int t, Matrix x, int l, int r) {
        if (l <= s && t <= r) {
            delta[p] = x * delta[p];
            // data[p] = x * data[p];
            calc(x, data[p], data[p]);
            tree[p].lazy = true;
            return;
        }
        pushdown(p);
        const int m = s + ((t - s) >> 1), ls = tree[p].l, rs = tree[p].r;
        if (l <= m) update(ls, s, m, x, l, r);
        if (r > m) update(rs, m + 1, t, x, l, r);
        pushup(p, 2);
    }

    ll query(int p, int s, int t, int l, int r) {
        if (l <= s && t <= r) return data[p].a[0][0];
        const int m = s + ((t - s) >> 1), ls = tree[p].l, rs = tree[p].r;
        pushdown(p);
        ll ret = 0;
        if (l <= m) ret = ret + query(ls, s, m, l, r);
        if (r > m) ret = ret + query(rs, m + 1, t, l, r);
        return ret;
    }
};

// segment tree history sum loj 193
void solve() {
    int n, m, type, l, r, x;
    cin >> n >> m;
    vector<ll> v(n + 1);
    for (int i = 1; i <= n; ++i) cin >> v[i];
    SegmentTree seg(n, v);
    for (int i = 1; i <= m; ++i) {
        cin >> type >> l >> r;
        if (type == 1) {
            cin >> x;
            Matrix mt;
            mt.a[0][1] = 0, mt.a[1][2] = x;
            seg.update(seg.root, 1, n, mt, l, r);
            mt.a[0][1] = 1, mt.a[1][2] = 0;
            seg.update(seg.root, 1, n, mt, 1, n);
        } else {
            ll ans = seg.query(seg.root, 1, n, l, r);
            cout << ans << '\n';
            Matrix mt;
            mt.a[0][1] = 1, mt.a[1][2] = 0;
            seg.update(seg.root, 1, n, mt, 1, n);
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
