#include <iostream>
#include <vector>
#include <cstring>
#define LOCAL
using namespace std;

vector<int> buildNext(string &s) {
    int n = static_cast<int>(s.size());
    vector<int> next(n, 0);
    for (int i = 1; i < n; i++) {
        int j = next[i - 1];
        while (j > 0 && s[j] != s[i]) j = next[j - 1];
        if (s[j] == s[i]) j++;
        next[i] = j;
    }
    return next;
}

vector<int> find_occurrences(string &text, string &pattern) {
    string cur = pattern + '#' + text;
    vector<int> next = buildNext(cur), ans;
    int sz1 = text.size(), sz2 = pattern.size();
    for (int i = sz2 + 1; i <= sz1 + sz2; ++i) {
        if (next[i] == sz2) ans.push_back(i - 2 * sz2);
    }
    return ans;
}

void solve() {
    string s1, s2;
    cin >> s1 >> s2;
    auto ans = find_occurrences(s1, s2);
    for (auto &i: ans) cout << i + 1 << '\n';
    auto next = buildNext(s2);
    for (auto &i: next) {
        cout << i << " ";
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
