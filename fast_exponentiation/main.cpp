#include <iostream>
#define LOCAL
using namespace std;
using ll = long long;

int binpow(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % m;
        b >>= 1;
        a = a * a % m;
    }
    return res;
}

void solve() {
    ll a, b, p;
    cin >> a >> b >> p;
    printf("%d^%d mod %d=%d", a, b, p, binpow(a, b, p));
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
