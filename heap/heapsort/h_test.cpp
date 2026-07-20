#include <iostream>
#include "heap.h"
#include <ctime>
#include <cstdlib>

using namespace std;

struct User {
    int key;
    int s;

    bool operator>(const User &t) const {
        return key > t.key;
    }

    bool operator<(const User &t) const {
        return key < t.key;
    }
};

int main() {

    freopen("../a1.in", "r", stdin);
//    freopen("../a1.out", "w", stdout);

    int n;
    string a[100];

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    User u[10];
    for (int i = 0; i < 10; ++i) {
        u[i].key = i;
        u[i].s = i;
    }

    Heap<User> myHeap(100, MAX_HEAP);
//    myHeap.BuildHeap(u, n);

    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        User user;
        user.key = rand() % 100;
        user.s = i;
        myHeap.Push(user);
    }
//    myHeap.Push("aa");
//
//    myHeap.Pop();
//    myHeap.Push("fadsfe");
//    myHeap.Push("b");
//    myHeap.Push("c");
//    myHeap.Push("d");
//    myHeap.Push("e");
//    myHeap.Pop();

    while (!myHeap.IsEmpty()) {
        Node<User> *u1 = myHeap.Pop();
        printf("%d,%d\n", u1->value.key, u1->value.s);
    }


    // 堆排
//    myHeap.HeapSort();
//    for (int i = 0; i < myHeap.Size(); ++i) {
//        User u = myHeap.Get(i);
//        printf("%d,%d\n", u.key, u.s);
//    }

    return 0;
}