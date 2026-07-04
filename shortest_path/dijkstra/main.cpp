#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define LOCAL
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
constexpr int N = 1e4 + 1;
constexpr int M = 2e4 + 1;

struct Edge {
    int to, nxt, w;
};

Edge edge[M];
int edge_num = 0, head[N]{}, vis[N]{};
ll dis[N]{};
priority_queue<pll, vector<pll>, greater<> > q;

void addEdge(int u, int v, int w) {
    edge[edge_num] = {v, head[u], w};
    head[u] = edge_num++;
}

void dijkstra(int s, int t) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.emplace(0, s);
    while (!q.empty()) {
        ll u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int e = head[u]; e; e = edge[e].nxt) {
            int v = edge[e].to;
            if (dis[u] + edge[e].w < dis[v]) {
                dis[v] = dis[u] + edge[e].w;
                q.emplace(dis[v], v);
            }
        }
    }
    cout << dis[t];
}

void solve() {
    int n, m, s, t, x, y, w;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        addEdge(x, y, w);
        addEdge(y, x, w);
    }
    dijkstra(s, t);
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
