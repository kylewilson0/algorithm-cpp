#include <iostream>
#include <cstring>
#define LOCAL
using namespace std;
constexpr int INF = 0x3f3f3f3f;
constexpr int N = 2e3 + 1;
constexpr int M = 6e3 + 1;

struct Edge {
    int u, v, w;
};

Edge edge[M];
int n, m, u, v, w, edge_num = 0, dis[N];

void addEdge(int u, int v, int w) {
    edge_num++;
    edge[edge_num] = {u, v, w};
}

bool bellman_ford(int s) {
    memset(dis, 0x3f, sizeof dis);
    bool flag = false;
    dis[s] = 0;
    for (int i = 1; i <= n; ++i) {
        flag = false;
        for (int j = 1; j <= edge_num; ++j) {
            u = edge[j].u, v = edge[j].v, w = edge[j].w;
            if (dis[u] == INF) continue;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                flag = true;
            }
        }
        if (!flag) break;
    }
    return flag;
}

void solve() {
    edge_num = 0;
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
    cout << (bellman_ford(1) ? "YES" : "NO") << '\n';
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
