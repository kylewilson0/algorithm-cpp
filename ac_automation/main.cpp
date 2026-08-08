#include <iostream>
#include <vector>
#include <queue>
#define fr(i, a, b) for (int i = (a); i <= (b); ++i)
#define rp(i, a, b) for (int i = (a); i >= (b); --i)
#define LOCAL
using namespace std;
constexpr int N = 2e5 + 1;

struct Node {
    int ch[26]{}, fail = 0, cnt = 0;
};

int n;
vector<int> order;
int end_node[N];

struct AhoCorasick {
    Node tr[N];
    int idx = 0;

    int insert(string &st) {
        int u = 0;
        for (char c: st) {
            int x = c - 'a';
            if (!tr[u].ch[x]) tr[u].ch[x] = ++idx;
            u = tr[u].ch[x];
        }
        return u;
    }

    void build() {
        queue<int> q;
        fr(i, 0, 25) {
            if (tr[0].ch[i]) q.push(tr[0].ch[i]);
        }
        while (!q.empty()) {
            int u = q.front();
            order.push_back(u);
            q.pop();
            fr(i, 0, 25) {
                if (tr[u].ch[i]) {
                    tr[tr[u].ch[i]].fail = tr[tr[u].fail].ch[i];
                    q.push(tr[u].ch[i]);
                } else {
                    tr[u].ch[i] = tr[tr[u].fail].ch[i];
                }
            }
        }
    }

    void query(string &st) {
        int u = 0;
        for (char c: st) {
            u = tr[u].ch[c - 'a'];
            tr[u].cnt++;
        }
        rp(i, order.size()-1, 0) {
            int j = order[i];
            tr[tr[j].fail].cnt += tr[j].cnt;
        }
        fr(i, 0, n-1) cout << tr[end_node[i]].cnt << '\n';
    }
} ac;

void solve() {
    string st;
    cin >> n;
    fr(i, 0, n-1) {
        cin >> st;
        end_node[i] = ac.insert(st);
    }
    ac.build();
    cin >> st;
    ac.query(st);
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
