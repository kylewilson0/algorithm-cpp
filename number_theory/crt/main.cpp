#include <iostream>
#include <format>
#define fr(i, a, b) for (int i = (a); i <= (b); ++i)
#define LOCAL

using namespace std;
using ll = __int128;
constexpr int N = 1e5 + 1;

void ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
    } else {
        ex_gcd(b, a % b, y, x);
        y -= a / b * x;
    }
}

ll inverse(ll a, ll b) {
    ll x, y;
    ex_gcd(a, b, x, y);
    return (x % b + b) % b;
}

int a[N], r[N], n;

ll crt() {
    ll p = 1, ans = 0;
    fr(i, 1, n) p *= r[i];
    fr(i, 1, n) {
        ll m = p / r[i];
        ll inv = inverse(m, r[i]);
        ans = (ans + a[i] * m * inv % p) % p;
    }
    return (ans % p + p) % p;
}


void solve() {
    cin >> n;
    fr(i, 1, n) cin >> r[i] >> a[i];
    cout << format("{}", crt());
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
