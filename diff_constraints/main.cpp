#include <iostream>
#include <cstring>
#include <queue>
#define LOCAL
using namespace std;
constexpr int INF = 0x3f3f3f3f;
constexpr int N = 5e3 + 10;
constexpr int M = 1e4 + 10;

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
        u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = edge[i].nxt) {
            v = edge[i].to, w = edge[i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n + 1) return true;
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
        addEdge(v, u, w);
    }
    for (int i = 1; i <= n; i++) addEdge(0, i, 0);
    if (spfa(0)) {
        cout << "NO";
        return;
    }
    for (int i = 1; i <= n; i++) cout << dis[i] << " ";
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
