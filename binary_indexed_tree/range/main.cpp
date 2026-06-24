#include <iostream>

using namespace std;
#define MAX_NUM 100001
#define LL long long

LL sum1[MAX_NUM] = {0}, sum2[MAX_NUM] = {0}, n;

LL lowbit(LL x) {
    return x & -x;
}

// 单个修改
void add(LL *sum, LL index, LL x) {
    while (index <= n) {
        sum[index] += x;
        index += lowbit(index);
    }
}

// 单个查询
LL query(const LL *sum, LL index) {
    LL ret = 0;
    while (index > 0) {
        ret += sum[index];
        index -= lowbit(index);
    }
    return ret;
}

// 区间修改
void range_add(LL left, LL right, LL x) {
    right++;
    add(sum1, left, x);
    add(sum1, right, -x);

    add(sum2, left, x * left);
    add(sum2, right, -x * right);
}

// 区间查询
LL range_query(LL left, LL right) {
    left--;
    LL sumA = (left + 1) * query(sum1, left) - query(sum2, left);
    LL sumB = (right + 1) * query(sum1, right) - query(sum2, right);

    return sumB - sumA;
}

int main() {
    freopen("a.in", "r", stdin);
    LL i, q, current = 0, last = 0;

    scanf("%lld%lld", &n, &q);
    for (i = 1; i <= n; ++i) {
        scanf("%lld", &current);
        add(sum1, i, current - last);
        add(sum2, i, (current - last) * i);
        last = current;
    }
    char type[2];
    LL left, right, x;
    for (i = 1; i <= q; ++i) {
        scanf("%s", &type);
        if (type[0] == 'Q') {
            scanf("%lld%lld", &left, &right);
            printf("%lld\n", range_query(left, right));
        } else {
            scanf("%lld%lld%lld", &left, &right, &x);
            range_add(left, right, x);
        }
    }

    return 0;
}
