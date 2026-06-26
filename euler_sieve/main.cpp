#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;
using ll = long long;

// #define LOCAL

struct EulerSieve {
    vector<int> prime{}, least_prime{};
    int sz;

    EulerSieve(int n) : sz(n + 1) {
        least_prime.reserve(sz);
        for (int i = 2; i < sz; i++) {
            if (!least_prime[i]) {
                prime.push_back(i);
                least_prime[i] = i;
            }
            for (auto &pri_j: prime) {
                if (i * pri_j >= sz) break;
                least_prime[i * pri_j] = pri_j;
                if (i % pri_j == 0) break;
            }
        }
    }
};

void solve(const int n) {
    EulerSieve euler_sieve(n);
    for (int i = 2; i < n; i++) {
        cout << "i=" << i << ", divisor=" << euler_sieve.least_prime[i] << endl;
    }
    cout << endl;
    for (auto &i: euler_sieve.prime) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1, n;
    //cin >> t;
    // cin >> n;
    while (t--) {
        solve(10);
    }
    return 0;
}
