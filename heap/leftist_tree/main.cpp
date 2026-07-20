#include <iostream>
#define fr(i, a, b) for (int i = (a); i <= (b); ++i)
#define LOCAL

using namespace std;
constexpr int N = 1e5 + 1;

struct Node {
    int l, r, v, d;

    Node() : l(0), r(0), v(0), d(-1) {
    }

    Node(int x) : l(0), r(0), v(x), d(0) {
    }
};

int fa[N];
bool deleted[N];
Node tr[N];

int find(const int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int merge(int x, int y) {
    if (!x | !y) return x | y;
    if (tr[x].v > tr[y].v || tr[x].v == tr[y].v && x > y) swap(x, y);
    tr[x].r = merge(tr[x].r, y);
    if (tr[tr[x].r].d > tr[tr[x].l].d) swap(tr[x].l, tr[x].r);
    tr[x].d = tr[tr[x].r].d + 1;
    return x;
}

void solve() {
    int n, m, op, x, y, v;
    cin >> n >> m;
    fr(i, 1, n) cin >> v, tr[i] = Node(v), fa[i] = i;
    fr(i, 1, m) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y;
            if (deleted[x] || deleted[y]) continue;
            x = find(x), y = find(y);
            if (x != y) fa[x] = fa[y] = merge(x, y);
        } else {
            cin >> x;
            if (deleted[x]) cout << -1 << '\n';
            else {
                x = find(x);
                deleted[x] = true;
                fa[x] = fa[tr[x].l] = fa[tr[x].r] = merge(tr[x].l, tr[x].r);
                cout << tr[x].v << '\n';
            }
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
