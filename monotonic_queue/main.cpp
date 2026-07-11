#include <iostream>
#include <algorithm>
#include <deque>
#define LOCAL
using namespace std;
constexpr int INF = 0x3f3f3f3f;
constexpr int N = 1e5 + 1;
pair<int, int> a[N];

void solve() {
    int n, d;
    cin >> n >> d;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1);
    int L = 1, ans = INF;
    deque<int> mxq, mnq;
    for (int i = 1; i <= n; i++) {
        while (!mxq.empty() && a[mxq.back()].second <= a[i].second) mxq.pop_back();
        mxq.push_back(i);
        while (!mnq.empty() && a[mnq.back()].second >= a[i].second) mnq.pop_back();
        mnq.push_back(i);
        while (L <= i && a[mxq.front()].second - a[mnq.front()].second >= d) {
            ans = min(ans, a[i].first - a[L].first);
            L++;
            while (mxq.front() < L) mxq.pop_front();
            while (mnq.front() < L) mnq.pop_front();
        }
    }
    if (ans == INF) cout << "-1";
    else cout << ans;
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
