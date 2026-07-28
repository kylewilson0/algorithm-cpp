#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

struct Node {
    int key, value, freq;

    Node(int k, int v, int f) : key(k), value(v), freq(f) {
    }
};

class LFUCache {
    int capacity, minFreq;
    unordered_map<int, list<Node> > freqTable;
    unordered_map<int, list<Node>::iterator> keyTable;

    void touch(list<Node>::iterator nodeIt) {
        int key = nodeIt->key;
        int value = nodeIt->value;
        int freq = nodeIt->freq;
        freqTable[freq].erase(nodeIt);
        if (freqTable[freq].empty()) {
            freqTable.erase(freq);
            if (freq == minFreq) minFreq++;
        }
        freqTable[freq + 1].emplace_front(key, value, freq + 1);
        keyTable[key] = freqTable[freq + 1].begin();
    }

public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {
    }

    int get(int key) {
        if (!keyTable.contains(key)) return -1;
        auto nodeIt = keyTable[key];
        int value = nodeIt->value;
        touch(nodeIt);
        return value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        if (keyTable.contains(key)) {
            auto nodeIt = keyTable[key];
            nodeIt->value = value;
            touch(nodeIt);
            return;
        }
        if (keyTable.size() >= capacity) {
            auto &minList = freqTable[minFreq];
            auto deleteNode = minList.back();
            minList.pop_back();
            keyTable.erase(deleteNode.key);
            if (minList.empty()) freqTable.erase(minFreq);
        }
        minFreq = 1;
        freqTable[1].emplace_front(key, value, 1);
        keyTable[key] = freqTable[1].begin();
    }
};

int main() {
    LFUCache lfu(2);

    lfu.put(1, 1); // cache=[1], freq(1)=1
    lfu.put(2, 2); // cache=[2,1], freq(2)=1, freq(1)=1
    cout << lfu.get(1) << endl; // 返回 1, freq(1)=2

    lfu.put(3, 3); // 缓存已满，淘汰 freq 最小且最久未使用的 key 2。cache=[3,1]
    cout << lfu.get(2) << endl; // 返回 -1 (找不到)
    cout << lfu.get(3) << endl; // 返回 3, freq(3)=2

    lfu.put(4, 4); // 缓存已满，key 1 和 key 3 的 freq 都是 2，淘汰最久未使用的 key 1。cache=[4,3]
    cout << lfu.get(1) << endl; // 返回 -1
    cout << lfu.get(3) << endl; // 返回 3
    cout << lfu.get(4) << endl; // 返回 4
    return 0;
}
