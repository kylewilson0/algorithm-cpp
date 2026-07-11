#include <iostream>
#define LOCAL
using namespace std;
using ll = long long;
constexpr int N = 1e7 + 1;

int ls[N], rs[N], w[N], stk[N], n;

void cartesian() {
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int k = top;
        while (k > 0 && w[stk[k]] > w[i]) k--;
        if (k) rs[stk[k]] = i;
        if (k < top) ls[i] = stk[k + 1];
        stk[++k] = i;
        top = k;
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    cartesian();
    ll l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        l ^= 1ll * i * (ls[i] + 1);
        r ^= 1ll * i * (rs[i] + 1);
    }
    cout << l << " " << r;
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
