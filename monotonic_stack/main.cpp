#include <iostream>
#include <stack>
#define LOCAL
using namespace std;
constexpr int N = 3e6 + 1;

int a[N], f[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    stack<int> s;
    for (int i = n; i > 0; --i) {
        while (!s.empty() && a[s.top()] <= a[i]) s.pop();
        if (!s.empty()) f[i] = s.top();
        s.push(i);
    }
    for (int i = 1; i <= n; ++i) cout << f[i] << " ";
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
