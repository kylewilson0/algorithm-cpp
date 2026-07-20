#include <iostream>

using namespace std;

#define TOTAL 5

//在tail的位置插入num，然后将num进行向上调整
void HeapUp(int *heap, int tail, int num) {
    int i, j;

    heap[tail] = num;//num插入堆尾
    i = tail;
    j = (i - 1) / 2;//j指向i的父结点

    while (i > 0) {
        //如果父亲结点小于插入的结点则退出，否则将父亲结点下移
        if (heap[j] <= num)
            break;
        heap[i] = heap[j];
        i = j;
        j = (i - 1) / 2;
    }

    heap[i] = num;
}

//将heap[top]的值进行向下调整
void HeapDown(int *heap, int top, int n) {
    int j = 2 * top + 1;    //左孩子结点
    int x = heap[top];

    while (j <= n) {
        //比较左右儿子，选择较小的一个
        if (j + 1 <= n && heap[j + 1] < heap[j])
            j++;    //使j指向左右孩子中较小的结点。

        //如果儿子结点中较小的都大于插入的结点则退出
        if (heap[j] >= x)
            break;
        heap[top] = heap[j];
        top = j;
        j = 2 * top + 1;
    }
    heap[top] = x;
}

//小根堆
int main() {

    freopen("../a.in", "r", stdin);
    freopen("../a.out", "w", stdout);

    int num;
    int heap[TOTAL], total = 0;
    cin >> num;

    int temp;
    for (int i = 0; i < num; i++) {
        cin >> temp;
        //如果堆中元素还没有达到最大值，则插入到堆尾并向上调整，否则替换根元素并向下进行调整
        if (total < TOTAL) {
            HeapUp(heap, total++, temp);
        } else {
            if (temp > heap[0]) {
                heap[0] = temp;
                HeapDown(heap, 0, TOTAL - 1);
            }
        }

    }

    for (int i = 0; i < TOTAL; i++) {
        cout << heap[i] << endl;
    }

    return 0;
}