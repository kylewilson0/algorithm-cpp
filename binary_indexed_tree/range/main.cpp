#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct BIT_RANGE {
    vector<ll> bit1{}, bit2{};
    int size;

    BIT_RANGE(int n) : size(n + 1) {
        bit1.resize(size);
        bit2.resize(size);
    }

    void build(const vector<ll> &a) {
        for (int i = 0; i < a.size(); i++) {
            int j = i + 1;
            bit1[j] += a[i];
            bit2[j] += a[i] * j;
            int parent = j + lowbit(j);
            if (parent < size) bit1[parent] += bit1[j], bit2[parent] += bit2[j];
        }
    }

    static int lowbit(int i) {
        return i & -i;
    }

    void update(vector<ll> &bit, int i, const ll x) const {
        for (; i < size; i += lowbit(i)) bit[i] += x;
    }

    static ll query(const vector<ll> &bit, int i) {
        ll ret = 0;
        for (; i; i -= lowbit(i)) ret += bit[i];
        return ret;
    }

    void updatePoint(const int i, const ll x) {
        update(bit1, i, x);
        update(bit2, i, x * i);
    }

    void updateRange(const int l, const int r, const ll x) {
        update(bit1, l, x), update(bit1, r + 1, -x);
        update(bit2, l, x * l), update(bit2, r + 1, -x * (r + 1));
    }

    ll queryPrefix(const int i) const {
        return query(bit1, i) * (i + 1) - query(bit2, i);
    }

    ll queryRange(const int l, const int r) const {
        return queryPrefix(r) - queryPrefix(l - 1);
    }
};

int main() {
    freopen("a.in", "r", stdin);
    // freopen("a.out", "w", stdout);
    int n, q, cur = 0, last = 0, l, r, x, type;
    cin >> n >> q;
    BIT_RANGE bit(n);
    vector<ll> a(n);
    for (int i = 1; i <= n; ++i) {
        cin >> cur;
        a[i - 1] = cur - last;
        // bit.updatePoint(i, cur - last);
        last = cur;
    }
    bit.build(a);
    for (int i = 1; i <= q; ++i) {
        cin >> type;
        if (type == 2) {
            cin >> l >> r;
            cout << bit.queryRange(l, r) << '\n';
        } else {
            cin >> l >> r >> x;
            bit.updateRange(l, r, x);
        }
    }
    return 0;
}
