#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#define fixed(x) fixed<<setprecision(x)
#define LOCAL
using namespace std;
constexpr double EPS = 1e-9;
constexpr int N = 1e2 + 10;
double ma[N][N]{};
int n;

pair<bool, vector<double> > gauss() {
    for (int i = 0; i < n; i++) {
        int r = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(ma[j][i]) > fabs(ma[r][i])) r = j;
        }
        if (fabs(ma[r][i]) < EPS) return {false, vector<double>{}};
        if (r != i) swap(ma[i], ma[r]);
        double div = ma[i][i];
        for (int j = i; j <= n; j++) ma[i][j] /= div;
        for (int j = i + 1; j < n; j++) {
            double p = ma[j][i];
            for (int k = i; k <= n; k++) {
                ma[j][k] -= ma[i][k] * p;
            }
        }
    }
    vector<double> ans(n, 0);
    ans[n - 1] = ma[n - 1][n];
    for (int i = n - 2; i >= 0; i--) {
        ans[i] = ma[i][n];
        for (int j = i + 1; j < n; j++) {
            ans[i] -= ans[j] * ma[i][j];
        }
    }
    return {true, ans};
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            cin >> ma[i][j];
        }
    }
    auto [fi,se] = gauss();
    if (!fi) cout << "No Solution";
    else {
        for (auto i: se) cout << fixed(2) << i << '\n';
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
