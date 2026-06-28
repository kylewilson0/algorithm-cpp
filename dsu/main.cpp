#include <iostream>
#include <vector>
#include <numeric>
#define LOCAL

using namespace std;
using ll = long long;
constexpr int MOD = 998244353;

struct DSU {
    vector<int> parent{};
    vector<ll> size{};
    int sz;

    DSU(const int n) : sz(n + 1) {
        parent.resize(sz);
        iota(parent.begin(), parent.end(), 0);
        size.assign(sz, 1);
    }

    int find(const int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }

    bool isConnected(const int x, const int y) {
        return find(x) == find(y);
    }
};

void solve() {
    int n, m, op, u, v;
    cin >> n >> m;
    DSU dsu(n);
    vector<int> ans(m);
    for (int i = 0; i < m; i++) {
        cin >> op >> u >> v;
        if (op == 0) {
            dsu.unite(u, v);
        } else {
            u = dsu.find(u), v = dsu.find(v);
            ans.emplace_back(u == v);
        }
    }
    ll base = 1, ret = 0;
    for (int i = ans.size() - 1; i >= 0; i--) {
        ret += base * ans[i], ret %= MOD;
        base <<= 1;
        base %= MOD;
    }
    cout << ret;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
