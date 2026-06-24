#include <iostream>
#include <array>
#include <vector>

using namespace std;
constexpr int N = 1e2 + 1;
int n, q;

struct BIT_SINGLE {
    vector<int> sum{};

    BIT_SINGLE(int &n) {
        sum.resize(n + 1);
    }

    void build(const std::vector<int> &a) {
        for (int i = 0; i < a.size(); ++i) {
            int j = i + 1;
            sum[j] += a[i];
            int parent = j + lowbit(j);
            if (parent <= N) sum[j + lowbit(j)] += sum[j];
        }
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int i, int x) {
        for (; i <= n; i += lowbit(i)) sum[i] += x;
    }

    int query(int i) {
        int ret = 0;
        for (; i; i -= lowbit(i)) ret += sum[i];
        return ret;
    }
};

int main() {
    n = 10;
    BIT_SINGLE bit(n);
    vector<int> a(10);
    for (int i = 0; i < 10; ++i) {
        a[i] = i + 1;
    }
    bit.build(a);
    for (int i = 1; i <= n; ++i) {
        cout << bit.query(i) << " ";
    }

    return 0;
}
