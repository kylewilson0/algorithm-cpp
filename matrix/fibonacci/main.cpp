#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

constexpr int MOD = 1e9 + 7;

#define LOCAL

struct Matrix {
    vector<vector<ll> > a{};
    int sz;

    Matrix(const int n) : sz(n) {
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i].resize(n, 0);
    }

    Matrix(const vector<vector<ll> > &b) : sz(b.size()) {
        a.resize(sz);
        for (int i = 0; i < sz; ++i) {
            a[i].resize(sz);
            for (int j = 0; j < sz; ++j) a[i][j] = b[i][j];
        }
    }

    Matrix operator-(const Matrix &T) const {
        Matrix res(sz);
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j) {
                res.a[i][j] = (a[i][j] - T.a[i][j] + MOD) % MOD;
            }
        return res;
    }

    Matrix operator+(const Matrix &T) const {
        Matrix res(sz);
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j) {
                res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
            }
        return res;
    }

    Matrix operator*(const Matrix &T) const {
        Matrix res(sz);
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j) {
                ll r = 0;
                for (int k = 0; k < sz; ++k) r += a[i][k] * T.a[k][j], r %= MOD;
                res.a[i][j] = r;
            }
        return res;
    }

    Matrix operator^(ll x) const {
        Matrix res(sz), bas(sz);
        for (int i = 0; i < sz; ++i) res.a[i][i] = 1;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j) bas.a[i][j] = a[i][j] % MOD;
        while (x) {
            if (x & 1) res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }
};

void solve(const ll n) {
    auto start = chrono::high_resolution_clock::now();
    vector<vector<ll> > a = {
        {1, 1},
        {1, 0}
    };
    Matrix A(a);
    Matrix B = A ^ n - 1;
    cout << B.a[0][0] << '\n';
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start);
    std::cout << "Elapsed time: " << elapsed.count() << " ns\n";
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ll n = 0;
    cin >> n;
    solve(n);
    return 0;
}
