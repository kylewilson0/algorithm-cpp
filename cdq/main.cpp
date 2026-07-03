#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#define LOCAL
using namespace std;

struct BIT {
    vector<int> bit;
    int size;

    BIT(int n) : size(n + 1) {
        bit.resize(size);
    }

    void update(int i, int x) {
        for (; i < size; i += i & -i) bit[i] += x;
    }

    int query(int i) {
        int ret = 0;
        for (; i; i -= i & -i) ret += bit[i];
        return ret;
    }
};

struct Node {
    int a, b, c, cnt, res;

    bool operator!=(const Node &other) const {
        if (a != other.a || b != other.b || c != other.c) return true;
        return false;
    }
};

bool compA(const Node &x, const Node &y) {
    if (x.a != y.a)return x.a < y.a;
    if (x.b != y.b)return x.b < y.b;
    return x.c < y.c;
}

bool compB(const Node &x, const Node &y) {
    if (x.b != y.b)return x.b < y.b;
    return x.c < y.c;
}

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 2e5 + 10;

int n, tot = 0;
array<Node, MAXN> v{}, uv{};
array<int, MAXN> ans{};
BIT bit(MAXM);

void cdq(int l, int r) {
    if (l == r) return;
    int m = l + ((r - l) >> 1);
    cdq(l, m);
    cdq(m + 1, r);
    sort(uv.begin() + l, uv.begin() + m + 1, compB);
    sort(uv.begin() + m + 1, uv.begin() + r + 1, compB);
    int j = l, i = m + 1;
    while (i <= r) {
        while (j <= m && uv[j].b <= uv[i].b) {
            bit.update(uv[j].c, uv[j].cnt);
            ++j;
        }
        uv[i].res += bit.query(uv[i].c);
        ++i;
    }
    for (int k = l; k < j; ++k) bit.update(uv[k].c, -uv[k].cnt);
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int k, t = 0;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> v[i].a >> v[i].b >> v[i].c;
    sort(v.begin() + 1, v.begin() + n + 1, compA);
    for (int i = 1; i <= n; ++i) {
        ++t;
        if (v[i] != v[i + 1]) {
            ++tot;
            uv[tot] = v[i];
            uv[tot].cnt = t;
            t = 0;
        }
    }
    cdq(1, tot);
    for (int i = 1; i <= tot; ++i) ans[uv[i].res + uv[i].cnt - 1] += uv[i].cnt;
    for (int i = 0; i < n; ++i) cout << ans[i] << '\n';
    return 0;
}
