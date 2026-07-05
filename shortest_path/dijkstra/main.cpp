#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define LOCAL
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
constexpr int N = 1e5 + 1;
constexpr int M = 2e5 + 1;

struct Edge {
    int to, nxt, w;
};

Edge edge[M];
int edge_num = 0, head[N]{}, n;
ll dis[N]{};
priority_queue<pll, vector<pll>, greater<> > q;

void addEdge(int u, int v, int w) {
    edge_num++;
    edge[edge_num] = {v, head[u], w};
    head[u] = edge_num;
}

// luogu 4779
void dijkstra(int s) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.emplace(0, s);
    while (!q.empty()) {
        ll d = q.top().first, u = q.top().second;
        q.pop();
        if (d > dis[u]) continue;
        for (int e = head[u]; e; e = edge[e].nxt) {
            int v = edge[e].to;
            if (dis[u] + edge[e].w < dis[v]) {
                dis[v] = dis[u] + edge[e].w;
                q.emplace(dis[v], v);
            }
        }
    }

    for (int i = 1; i <= n; i++) cout << dis[i] << " ";
}

void solve() {
    int m, s, x, y, w;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        addEdge(x, y, w);
    }
    dijkstra(s);
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
