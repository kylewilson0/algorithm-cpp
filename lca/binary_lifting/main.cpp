#include <iostream>
#include <cstring>
#define LOCAL
using namespace std;
constexpr int N = 5e5 + 1;
constexpr int LOG_N = 20;

struct Edge {
    int to, next;

    Edge() : to(-1), next(-1) {
    }
};

Edge edge[N << 1];
int n, m, s, cnt = 0, head[N], fa[N][LOG_N], dep[N];

void addEdge(int u, int v) {
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
    cnt++;
}

void dfs(int u, int parent) {
    fa[u][0] = parent;
    dep[u] = dep[parent] + 1;
    for (int i = 1; i < LOG_N; ++i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (int i = head[u]; ~i; i = edge[i].next) {
        if (edge[i].to == parent) continue;
        dfs(edge[i].to, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v], ans = 0;
    for (int i = LOG_N - 1; i >= 0; --i) {
        if (diff & 1 << i) u = fa[u][i];
    }
    if (u == v) return u;
    for (int i = LOG_N - 1; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

void solve() {
    cin >> n >> m >> s;
    int a, b;
    memset(head, 0xff, sizeof(head));
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        addEdge(a, b), addEdge(b, a);
    }
    dep[0] = -1;
    dfs(s, 0);
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        cout << lca(a, b) << '\n';
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
