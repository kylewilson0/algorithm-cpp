#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct BIT_SINGLE {
    vector<ll> bit{};
    int size;

    BIT_SINGLE(int &n) : size(n + 1) {
        bit.resize(size);
    }

    void build(const vector<ll> &a) {
        for (int i = 0; i < a.size(); i++) {
            int j = i + 1;
            bit[j] += a[i];
            int parent = j + lowbit(j);
            if (parent < size) bit[parent] += bit[j];
        }
    }

    static int lowbit(int i) {
        return i & -i;
    }

    void update(int i, ll x) {
        for (; i < size; i += lowbit(i)) bit[i] += x;
    }

    ll query(int i) const {
        ll ret = 0;
        for (; i; i -= lowbit(i)) ret += bit[i];
        return ret;
    }
};

int main() {
    freopen("a.in", "r", stdin);
    int n, q, l, r, type;;
    cin >> n >> q;
    BIT_SINGLE bit(n);
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    bit.build(a);
    for (int i = 0; i < q; ++i) {
        cin >> type >> l >> r;
        if (type == 1) {
            bit.update(l, r);
        } else {
            cout << bit.query(r) - bit.query(l - 1) << endl;
        }
    }
    return 0;
}
