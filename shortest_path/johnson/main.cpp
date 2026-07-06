#include <iostream>
#include <queue>
#include <cstring>
#define LOCAL
using namespace std;
using ll = long long;
using pli = pair<ll, int>;
constexpr ll INF = 1e9;
constexpr int N = 3e3 + 1;
constexpr int M = 1e4 + 1;

struct Edge {
    int to, nxt;
    ll w;
};

Edge edge[M];
int n, m, u, v, edge_num = 0, head[N], cnt[N], vis[N];
ll w, h[N], dis[N];


void addEdge(int u, int v, ll w) {
    edge_num++;
    edge[edge_num] = {v, head[u], w};
    head[u] = edge_num;
}

bool spfa(int s) {
    memset(h, 0x3f, sizeof h);
    memset(vis, 0, sizeof vis);
    h[s] = cnt[s] = 0, vis[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = edge[i].nxt) {
            v = edge[i].to, w = edge[i].w;
            if (h[v] > h[u] + w) {
                h[v] = h[u] + w;
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

void dijkstra(int s) {
    for (int i = 1; i <= n; i++) dis[i] = INF;
    dis[s] = 0;
    priority_queue<pli, vector<pli>, greater<> > q;
    q.emplace(0, s);
    while (!q.empty()) {
        w = q.top().first, u = q.top().second;
        q.pop();
        if (w > dis[u]) continue;
        for (int e = head[u]; e; e = edge[e].nxt) {
            v = edge[e].to;
            if (dis[v] > dis[u] + edge[e].w) {
                dis[v] = dis[u] + edge[e].w;
                q.emplace(dis[v], v);
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }
    for (int i = 1; i <= n; i++) addEdge(0, i, 0);
    if (spfa(0)) {
        cout << -1;
        return;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = head[i]; j; j = edge[j].nxt) edge[j].w += h[i] - h[edge[j].to];
    }
    for (int i = 1; i <= n; i++) {
        dijkstra(i);
        ll ans = 0;
        for (int j = 1; j <= n; j++) {
            if (dis[j] == INF) ans += INF * j;
            else ans += (dis[j] + h[j] - h[i]) * j;
        }
        cout << ans << '\n';
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
