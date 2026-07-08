#include <iostream>
#include "quicksort.h"
#include <random>

int partition(vector<int> &a, int low, int high) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution dist(low, high);
    int pivotIndex = dist(gen);
    swap(a[pivotIndex], a[high]);

    int pivot = a[high];
    int i = low;

    for (int j = low; j < high; ++j) {
        if (a[j] < pivot) {
            swap(a[i++], a[j]);
        }
    }
    swap(a[i], a[high]);
    return i;
}

void quickSort(vector<int> &a, int low, int high) {
    if (low >= high) return;
    int p = partition(a, low, high);
    quickSort(a, low, p - 1);
    quickSort(a, p + 1, high);
}

int main() {
    vector a = {25, 4, 1, 9, 10, 3, 1, 2, 7, 8};
    quickSort(a, 0, a.size() - 1);
    for (auto &i: a) {
        cout << i << " ";
    }
}
