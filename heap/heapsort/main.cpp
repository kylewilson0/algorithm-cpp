#include <iostream>

using namespace std;

#define TOTAL 100

//将heap[k]向上调整
void heapUp(int *heap, int k) {
    int parent, son, x;
    x = heap[k];
    son = k;
    parent = (son - 1) / 2;

    while (son > 0) {
        //如果父结点大于等于heap[k]则退出，否则将父结点下移
        if (heap[parent] >= x)
            break;
        heap[son] = heap[parent];
        son = parent;
        parent = (son - 1) / 2;
    }
    heap[son] = x;
}

//将heap[k]向下调整
void heapDown(int *heap, int k, int n) {
    int parent, son, x;
    x = heap[k];
    parent = k;
    son = 2 * k + 1;    //左孩子结点

    while (son <= n) {
        //比较左右儿子，选择较大的一个
        if (son + 1 <= n && heap[son + 1] > heap[son])
            son++;    //使son指向左右孩子中较大的结点。

        //如果儿子结点中较大的都小于等于待调整结点则退出，否则将子结点上移
        if (heap[son] <= x)
            break;
        heap[parent] = heap[son];
        parent = son;
        son = 2 * parent + 1;
    }
    heap[parent] = x;
}

void buildHeap(int *heap, int n) {

    for (int i = (n - 1) / 2; i >= 0; --i) {
        heapDown(heap, i, n);
    }
}

void swap(int *heap, int a, int b) {
    int temp;
    temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

void heapsort(int *heap, int n) {

    for (int i = n; i > 0; --i) {
        swap(heap, 0, i);
        heapDown(heap, 0, i - 1);
    }

}

//大根堆
int main() {

    freopen("../a1.in", "r", stdin);
//    freopen("../a1.out", "w", stdout);

    int n;
    int heap[TOTAL];
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> heap[i];
    }

    buildHeap(heap, --n);

    heap[++n] = 1;

    heapUp(heap, n);

    heapsort(heap, n);
    for (int i = 0; i <= n; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
    return 0;
}

