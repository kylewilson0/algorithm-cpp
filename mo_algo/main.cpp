#include <iostream>
#include <algorithm>
#include <array>
#include <numeric>
#include <cmath>
#define LOCAL
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

constexpr int N = 5e4 + 1;
int sqn;

struct Node {
    int l, r, id;

    bool operator<(const Node &rhs) const {
        if (l / sqn != rhs.l / sqn) return l < rhs.l;
        return l / sqn & 1 ? r < rhs.r : r > rhs.r;
    }
};

array<int, N> v{}, color{};
array<Node, N> query{};
array<pll, N> ans{};
ll tot = 0;

void add(int i) {
    tot += color[i];
    color[i]++;
}

void del(int i) {
    color[i]--;
    tot -= color[i];
}

void solve() {
    int n, m;
    cin >> n >> m;
    sqn = static_cast<int>(sqrt(n));
    for (int i = 1; i <= n; ++i) cin >> v[i];
    for (int i = 0; i < m; ++i) cin >> query[i].l >> query[i].r, query[i].id = i;
    sort(query.begin(), query.begin() + m);
    for (int i = 0, l = 1, r = 0; i < m; ++i) {
        if (query[i].l == query[i].r) {
            ans[query[i].id] = {0, 1};
            continue;
        }
        while (l > query[i].l) add(v[--l]);
        while (r < query[i].r) add(v[++r]);
        while (l < query[i].l) del(v[l++]);
        while (r > query[i].r) del(v[r--]);
        ans[query[i].id] = {tot, static_cast<ll>(r - l + 1) * (r - l) / 2};
    }
    for (int i = 0; i < m; ++i) {
        if (ans[i].first != 0) {
            ll g = gcd(ans[i].first, ans[i].second);
            ans[i].first /= g, ans[i].second /= g;
        } else ans[i].second = 1;
        cout << ans[i].first << "/" << ans[i].second << "\n";
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
