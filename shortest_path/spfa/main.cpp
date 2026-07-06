#include <iostream>
#include <cstring>
#include <queue>
#define LOCAL
using namespace std;
constexpr int INF = 0x3f3f3f3f;
constexpr int N = 2e3 + 1;
constexpr int M = 6e3 + 1;

struct Edge {
    int to, nxt, w;
};

Edge edge[M];
int n, m, u, v, w, edge_num = 0, head[N], cnt[N], vis[N], dis[N];

void addEdge(int u, int v, int w) {
    edge_num++;
    edge[edge_num] = {v, head[u], w};
    head[u] = edge_num;
}

bool spfa(int s) {
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[s] = cnt[s] = 0, vis[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = edge[i].nxt) {
            v = edge[i].to, w = edge[i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return true;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return false;
}

void solve() {
    edge_num = 0;
    memset(head, 0, sizeof head);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        if (w >= 0) {
            addEdge(u, v, w);
            addEdge(v, u, w);
        } else {
            addEdge(u, v, w);
        }
    }
    cout << (spfa(1) ? "YES" : "NO") << '\n';
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
