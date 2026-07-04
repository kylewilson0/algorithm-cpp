#include <iostream>
#include <cstring>
#define LOCAL
using namespace std;
using ll = long long;
constexpr int N = 1e2 + 1;
int d[N][N];

void solve() {
    int n, m, x, y, w;
    memset(d, 0x3f, sizeof(d));
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> w;
        d[x][y] = min(d[x][y], w);
        d[y][x] = d[x][y];
    }
    for (int k = 1; k <= n; ++k) {
        d[k][k] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << d[i][j] << " ";
        }
        cout << endl;
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
