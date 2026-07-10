#include <iostream>
#define LOCAL
using namespace std;
constexpr int N = 1e5 + 1;
constexpr int LOG_N = 16;

int logn[N]{}, n, m, f[LOG_N + 1][N];

void pre() {
    logn[1] = 0;
    for (int i = 2; i < N; ++i) logn[i] = logn[i >> 1] + 1;
}

void solve() {
    pre();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> f[0][i];
    for (int i = 1; i <= LOG_N; ++i) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
            f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
        }
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        int k = logn[r - l + 1];
        cout << max(f[k][l], f[k][r - (1 << k) + 1]) << '\n';
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
