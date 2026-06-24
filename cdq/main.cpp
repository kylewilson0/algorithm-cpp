#include <iostream>

#define MAX_N 200001
#define MAX_M 3001

struct Line {
    int l, r, v;
};

struct Node {
    int op, l, r, v;
};
Line line[MAX_N];
int n, m, last_ans = 0;

void init() {
    scanf("%d %m", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &line[i].l, &line[i].r, &line[i].v);
    }

    for (int i = n; i < n + m; ++i) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %d", &line[i].l, &line[i].r, &line[i].v);
        } else {
            scanf("%d %d", &line[i].l, &line[i].r);
        }
    }
}

void cdq(int l, int r) {

    if (l == r) return;

    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);

}

int main() {

    freopen("../a.in", "r", stdin);

    return 0;
}
