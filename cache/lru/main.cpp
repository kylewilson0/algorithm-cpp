#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;
using pii = pair<int, int>;

class LRUCache {
    int capacity;
    list<pii> cache;
    unordered_map<int, list<pii>::iterator> keyTable;

public:
    LRUCache(int cap) : capacity(cap) {
    }

    int get(int key) {
        if (!keyTable.contains(key)) return -1;
        auto node = keyTable[key];
        int value = node->second;
        cache.splice(cache.begin(), cache, node);
        return value;
    }

    void put(int key, int value) {
        if (keyTable.contains(key)) {
            auto node = keyTable[key];
            node->second = value;
            cache.splice(cache.begin(), cache, node);
            return;
        }
        if (cache.size() >= capacity) {
            int old_key = cache.back().first;
            cache.pop_back();
            keyTable.erase(old_key);
        }
        cache.emplace_front(key, value);
        keyTable[key] = cache.begin();
    }
};

int main() {
    LRUCache lru(2); // 容量为 2
    lru.put(1, 1); // cache: [1:1]
    lru.put(2, 2); // cache: [2:2, 1:1]
    cout << lru.get(1) << endl; // 返回 1，cache: [1:1, 2:2]

    lru.put(3, 3); // 缓存已满，淘汰最久未使用的 2，cache: [3:3, 1:1]
    cout << lru.get(2) << endl; // 返回 -1 (未找到)

    lru.put(4, 4); // 缓存已满，淘汰最久未使用的 1，cache: [4:4, 3:3]
    cout << lru.get(1) << endl; // 返回 -1 (未找到)
    cout << lru.get(3) << endl; // 返回 3，cache: [3:3, 4:4]
    cout << lru.get(4) << endl; // 返回 4，cache: [4:4, 3:3]
    return 0;
}
