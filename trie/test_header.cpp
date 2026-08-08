#include <iostream>
#include <cstring>
#include "trie.h"

int main() {
    freopen("b.in", "r", stdin);

    Trie my_trie;

    char st[100];
    while (~scanf("%s", st)) {
        my_trie.Insert(st, strlen(st));
    }

    for (int i = 0; i < my_trie.Size(); ++i) {
        printf("%-2d, word = %-10s, cnt = %d\n", i, my_trie.GetWord(i), my_trie.WordCnt(i));
    }

    char t[5][10] = {"blue", "re1d", "red", "magent", "cyan1"};
    for (int i = 0; i < 5; ++i) {
        printf("%d\n", my_trie.Find(t[i], strlen(t[i])));
    }

    return 0;
}
