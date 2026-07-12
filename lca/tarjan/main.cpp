#include <iostream>
#include <cstring>
#define LOCAL
using namespace std;
constexpr int N = 5e5 + 1;

struct Edge {
    int from, to, next, lca;

    Edge() : from(-1), to(-1), next(-1), lca(-1) {
    }
};

Edge edge[N << 1], queryEdge[N << 1];
int n, m, s, cnt = 0, queryCnt = 0, head[N], queryHead[N], parent[N];
bool vis[N]{};

void addEdge(int u, int v) {
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
    cnt++;
}

void addQueryEdge(int u, int v) {
    queryEdge[queryCnt].from = u;
    queryEdge[queryCnt].to = v;
    queryEdge[queryCnt].next = queryHead[u];
    queryHead[u] = queryCnt;
    queryCnt++;
}

int find(int u) {
    if (parent[u] == u) return u;
    return parent[u] = find(parent[u]);
}

void tarjan(int u) {
    parent[u] = u;
    vis[u] = true;
    for (int i = head[u]; ~i; i = edge[i].next) {
        Edge &e = edge[i];
        if (!vis[e.to]) {
            tarjan(e.to);
            parent[e.to] = u;
        }
    }
    for (int i = queryHead[u]; ~i; i = queryEdge[i].next) {
        Edge &e = queryEdge[i];
        if (vis[e.to]) {
            queryEdge[i ^ 1].lca = e.lca = find(e.to);
        }
    }
}

void solve() {
    cin >> n >> m >> s;
    int a, b;
    memset(head, 0xff, sizeof(head));
    memset(queryHead, 0xff, sizeof(queryHead));
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        addEdge(a, b), addEdge(b, a);
    }
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        addQueryEdge(a, b), addQueryEdge(b, a);
    }
    tarjan(s);
    for (int i = 0; i < m; i++) cout << queryEdge[i << 1].lca << '\n';
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
