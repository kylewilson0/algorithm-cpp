#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define fr(i, a, b) for (int i = (a); i <= (b); ++i)
#define LOCAL
using namespace std;
using pdi = pair<double, int>;
constexpr double LNF = 1e13;
constexpr int N = 5e3 + 1;
constexpr int M = 2e5 + 1;

struct Edge {
    int u, v;
    double w;

    Edge() : u(0), v(0), w(0) {
    }

    Edge(int u, int v, double w) : u(u), v(v), w(w) {
    }
} edge[M];

double dis[N], E;
int n, m, out[N];
vector<int> gr[N], ig[N];

struct PersistentHeap {
    struct Node {
        int l, r, to, d;
        double v;

        Node(int to, double v) : l(0), r(0), to(to), d(-1), v(v) {
        }

        Node() : l(0), r(0), to(0), d(-1), v(0) {
        }
    } tr[M << 3];

    int idx = 0, rt[N]{};

    int meld(int x, int y) {
        if (!x || !y) return x | y;
        if (tr[x].v > tr[y].v) swap(x, y);
        int p = ++idx;
        tr[p] = tr[x];
        tr[p].r = meld(tr[p].r, y);
        if (tr[tr[p].r].d > tr[tr[p].l].d) swap(tr[p].l, tr[p].r);
        tr[p].d = tr[tr[p].r].d + 1;
        return p;
    }

    void insert(int x, int y, double v) {
        int p = ++idx;
        tr[p] = Node(y, v);
        rt[x] = meld(rt[x], p);
    }

    void merge(int x, int y) {
        rt[x] = meld(rt[x], rt[y]);
    }
} heap;

void dijkstra(int s) {
    fill_n(dis, N, LNF);
    dis[s] = 0;
    priority_queue<pdi, vector<pdi>, greater<> > q;
    q.emplace(0, s);
    while (!q.empty()) {
        double d = q.top().first;
        int u = q.top().second;
        q.pop();
        if (d > dis[u]) continue;
        for (auto i: ig[u]) {
            int to = edge[i].u;
            if (dis[to] > dis[u] + edge[i].w) {
                dis[to] = dis[u] + edge[i].w;
                out[to] = i;
                q.emplace(dis[to], to);
            }
        }
    }
}

void buildSidetrack() {
    fr(i, 1, m) {
        auto e = edge[i];
        if (e.u != n && out[e.u] != i && dis[e.u] < LNF && dis[e.v] < LNF) {
            heap.insert(e.u, e.v, e.w + dis[e.v] - dis[e.u]);
        }
    }
    queue<int> q;
    q.push(n);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto i: ig[cur]) {
            if (out[edge[i].u] == i) {
                heap.merge(edge[i].u, cur);
                q.emplace(edge[i].u);
            }
        }
    }
}

void calc() {
    int ans = 1;
    E -= dis[1];
    priority_queue<pdi, vector<pdi>, greater<> > q;
    auto insert = [&](int x, double cost) {
        if (x) q.emplace(cost + heap.tr[x].v, x);
    };
    insert(heap.rt[1], dis[1]);
    while (!q.empty() && E > 0) {
        double d = q.top().first;
        int cur = q.top().second;
        q.pop();
        E -= d;
        if (E >= 0) ans++;
        insert(heap.tr[cur].l, d - heap.tr[cur].v);
        insert(heap.tr[cur].r, d - heap.tr[cur].v);
        insert(heap.rt[heap.tr[cur].to], d);
    }
    cout << ans;
}

void solve() {
    cin >> n >> m >> E;
    int u, v;
    double w;
    fr(i, 1, m) {
        cin >> u >> v >> w;
        edge[i] = Edge(u, v, w);
        gr[u].push_back(i);
        ig[v].push_back(i);
    }
    dijkstra(n);
    buildSidetrack();
    calc();
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
