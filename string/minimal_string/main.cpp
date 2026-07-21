#include <iostream>
#define LOCAL
using namespace std;

void solve() {
    int n;
    string st;
    cin >> n >> st;
    int i = 0, j = 1, k = 0;
    while (k < n && i < n && j < n) {
        if (st[(i + k) % n] == st[(j + k) % n]) {
            k++;
        } else {
            if (st[(i + k) % n] > st[(j + k) % n]) i = i + k + 1;
            else j = j + k + 1;
            if (i == j) ++j;
            k = 0;
        }
    }
    int p = min(i, j);
    cout << st.substr(p) << st.substr(0, p);
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
