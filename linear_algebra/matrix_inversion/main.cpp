#include <iostream>
#define LOCAL
using namespace std;
using ll = long long;
constexpr int MOD = 1e9 + 7;
constexpr int N = 4e2;
ll ma[N][2 * N]{};
int n;

ll binpow(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}

bool gauss() {
    for (int i = 0; i < n; i++) {
        int r = i;
        for (int j = i + 1; j < n; j++) {
            if (ma[j][i] > ma[r][i]) r = j;
        }
        if (ma[r][i] == 0) return false;
        if (r != i) swap(ma[i], ma[r]);
        ll p = binpow(ma[i][i], MOD - 2);
        for (int j = i; j < 2 * n; j++) ma[i][j] = ma[i][j] * p % MOD;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            ll p = ma[j][i];
            for (int k = i; k < 2 * n; k++) {
                ma[j][k] = (ma[j][k] - ma[i][k] * p % MOD + MOD) % MOD;
            }
        }
    }
    return true;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cin >> ma[i][j];
    }
    for (int i = 0; i < n; ++i) ma[i][n + i] = 1;
    if (!gauss()) {
        cout << "No Solution";
        return;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = n; j < 2 * n; ++j) cout << ma[i][j] << " ";
        cout << '\n';
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
