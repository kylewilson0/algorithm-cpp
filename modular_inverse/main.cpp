#include <iostream>
#include <vector>

#define LOCAL

using namespace std;
using ll = long long;

struct ModularInverseLinear {
    vector<ll> inv{};
    int sz, p;

    ModularInverseLinear(const int n, const int p) : sz(n + 1), p(p) {
        inv.resize(n + 1);
        inv[1] = 1;
        for (int i = 2; i <= n; i++) {
            inv[i] = (p - p / i) * inv[p % i] % p;
        }
    }
};

void solve() {
    int n, p;
    cin >> n >> p;
    ModularInverseLinear modular(n, p);
    for (int i = 1; i <= n; i++) cout << modular.inv[i] << endl;
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
