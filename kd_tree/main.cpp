#include <iostream>
#include <algorithm>
#define LOCAL
using namespace std;
constexpr int N(2e5 + 1), LOG{18};

struct Node {
    int l = 0, r = 0, v = 0, sum = 0, x[2]{}, L[2]{}, H[2]{};
};

Node tr[N], l, h;
int id[N], cnt = 0, rt[LOG];

void pushUp(int p) {
    tr[p].sum = tr[tr[p].l].sum + tr[tr[p].r].sum + tr[p].v;
    for (int k: {0, 1}) {
        tr[p].L[k] = tr[p].H[k] = tr[p].x[k];
        if (tr[p].l) {
            tr[p].L[k] = min(tr[p].L[k], tr[tr[p].l].L[k]);
            tr[p].H[k] = max(tr[p].H[k], tr[tr[p].l].H[k]);
        }
        if (tr[p].r) {
            tr[p].L[k] = min(tr[p].L[k], tr[tr[p].r].L[k]);
            tr[p].H[k] = max(tr[p].H[k], tr[tr[p].r].H[k]);
        }
    }
}

int build(int l, int r, int dep = 0) {
    int p = (l + r) >> 1;
    auto cmp = [dep](int a, int b) { return tr[a].x[dep] < tr[b].x[dep]; };
    nth_element(id + l, id + p, id + r + 1, cmp);
    int x{id[p]};
    if (l < p) tr[x].l = build(l, p - 1, dep ^ 1);
    if (p < r) tr[x].r = build(p + 1, r, dep ^ 1);
    pushUp(x);
    return x;
}

void append(int &p) {
    if (!p) return;
    id[++cnt] = p;
    append(tr[p].l), append(tr[p].r);
    p = 0;
}

int query(int p) {
    if (!p) return 0;
    bool flag{false};
    for (int k: {0, 1}) flag |= !(l.x[k] <= tr[p].L[k] && tr[p].H[k] <= h.x[k]);
    if (!flag) return tr[p].sum;
    for (int k: {0, 1}) {
        if (tr[p].L[k] > h.x[k] || tr[p].H[k] < l.x[k]) return 0;
    }
    int ret{0};
    flag = false;
    for (int k: {0, 1}) flag |= !(l.x[k] <= tr[p].x[k] && tr[p].x[k] <= h.x[k]);
    if (!flag) ret = tr[p].v;
    ret += query(tr[p].l) + query(tr[p].r);
    return ret;
}

void solve() {
    int n, op, a, b, c, last = 0;
    cin >> n, n = 0;
    cin >> op;
    while (op != 3) {
        if (op == 1) {
            cin >> a >> b >> c;
            a ^= last, b ^= last, c ^= last;
            tr[++n].x[0] = a, tr[n].x[1] = b, tr[n].v = c;
            id[cnt = 1] = n;
            for (int &i: rt) {
                if (!i) {
                    i = build(1, cnt);
                    break;
                }
                append(i);
            }
        } else if (op == 2) {
            cin >> l.x[0] >> l.x[1] >> h.x[0] >> h.x[1];
            l.x[0] ^= last, l.x[1] ^= last, h.x[0] ^= last, h.x[1] ^= last;
            last = 0;
            for (int i: rt) last += query(i);
            cout << last << '\n';
        }
        cin >> op;
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
