#include <iostream>
#include <vector>
#include <algorithm>
#include <ctgmath>
#define LOCAL
using namespace std;

class IntroSort {
    static constexpr int INSERTION_THRESHOLD = 16;

    static void insertionSort(vector<int> &a, int l, int r) {
        for (int i = l + 1; i <= r; i++) {
            int j = i - 1, key = a[i];
            while (j >= l && a[j] > key) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = key;
        }
    }

    static int medianOfThree(vector<int> &a, int l, int r) {
        int m = l + (r - l) / 2;
        if (a[l] > a[m]) swap(a[l], a[m]);
        if (a[l] > a[r]) swap(a[l], a[r]);
        if (a[m] > a[r]) swap(a[m], a[r]);
        return m;
    }

    static int partition(vector<int> &a, int l, int r) {
        int pivotIndex = medianOfThree(a, l, r);
        swap(a[pivotIndex], a[r]);
        int pivot = a[r];
        int i = l;
        for (int j = l; j < r; ++j) {
            if (a[j] < pivot) {
                swap(a[i++], a[j]);
            }
        }
        swap(a[i], a[r]);
        return i;
    }

    static void heapify(vector<int> &a, int k, int n) {
        int x = a[k], parent = k, son = 2 * k + 1;
        while (son <= n) {
            if (son + 1 <= n && a[son + 1] > a[son]) son++;
            if (a[son] < x) break;
            a[parent] = a[son];
            parent = son;
            son = 2 * parent + 1;
        }
        a[parent] = x;
    }

    static void make_heap(vector<int> &a) {
        for (int i = (a.size() - 1) / 2; i >= 0; --i) {
            heapify(a, i, a.size() - 1);
        }
    }

    static void sort_heap(vector<int> &a) {
        for (int i = a.size() - 1; i > 0; --i) {
            swap(a[0], a[i]);
            heapify(a, 0, i - 1);
        }
    }

    static void heapSort(vector<int> &a, int l, int r) {
        vector b(a.begin() + l, a.begin() + r + 1);
        make_heap(b);
        sort_heap(b);
        for (int i = 0; i < b.size(); i++) a[l + i] = b[i];
    }

    static void introSort(vector<int> &a, int l, int r, int depthLimit) {
        while (r - l > INSERTION_THRESHOLD) {
            if (depthLimit == 0) {
                heapSort(a, l, r);
                return;
            }
            depthLimit--;
            int p = partition(a, l, r);
            if (p - l < r - p) {
                introSort(a, l, p - 1, depthLimit);
                l = p + 1;
            } else {
                introSort(a, p + 1, r, depthLimit);
                r = p - 1;
            }
        }
    }

public:
    static void sort(vector<int> &a) {
        if (a.empty()) return;
        int depthLimit = 2 * log2(a.size());
        introSort(a, 0, a.size() - 1, depthLimit);
        insertionSort(a, 0, a.size() - 1);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    IntroSort::sort(a);
    for (auto &i: a) cout << i << " ";
}

int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
