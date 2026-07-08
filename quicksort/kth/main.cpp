#include <iostream>
#include <vector>
#define LOCAL

using namespace std;
constexpr int N = 5e6 + 1;

int partition(vector<int> &a, int low, int high) {
    int pivot = a[high];
    int i = low;
    for (int j = low; j < high; ++j) {
        if (a[j] < pivot) {
            swap(a[i], a[j]);
            i++;
        }
    }
    swap(a[i], a[high]);
    return i;
}

int quickSelect(vector<int> &a, int low, int high, int k) {
    if (low == high) return a[low];
    int pivot = partition(a, low, high);
    if (k == pivot) return a[pivot];
    if (k < pivot) return quickSelect(a, low, pivot - 1, k);
    return quickSelect(a, pivot + 1, high, k);
}

int findKth(vector<int> &a, int k) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int p = partition(a, l, r);
        if (p == k) return a[p];
        if (k < p) r = p - 1;
        else l = p + 1;
    }
    return -1;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // cout << quickSelect(a, 0, n - 1, k);
    cout << findKth(a, k);
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
