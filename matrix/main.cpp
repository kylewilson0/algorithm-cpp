#include <iostream>
#include <fstream>

using namespace std;
const int N = 3;

int solve(int step) {
    if (step == 0 || step == 1) {
        return 1;
    }
    return solve(step - 1) + solve(step - 2);
}

int pow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) {
            ret *= a;
        }
        a *= a;
        b >>= 1;
    }
    return ret;
}

void multiMatrix(int a[][N], int b[][N]) {
    int tmp[N][N] = {0}, i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (int k = 0; k < N; k++) {
                tmp[i][j] += a[i][k] * b[k][j];
            }
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            a[i][j] = tmp[i][j];
        }
}

void powMatrix(int a[][N], int b, int ret[][N]) {
    memset(ret, 0, sizeof(int) * N * N);
    for (int i = 0; i < N; i++) {
        ret[i][i] = 1;
    }
    while (b) {
        if (b & 1) multiMatrix(ret, a);
        multiMatrix(a, a);
        b >>= 1;
    }
}

int main() {
    freopen("a.in", "r", stdin);
    int i, j, n;
    long digital[101], total = 0;
    cin >> n;
    digital[0] = 1;
    digital[1] = 1;
    for (i = 2; i < n; i++) {
        digital[i] = digital[i - 1] + digital[i - 2];
        //cout << digital[i] << endl;
        //        total += digital[i];
    }
    cout << digital[31] << endl;
    for (i = 0; i < 32; i++) total = total + digital[i];
    cout << "total=" << total << endl;
    cout << "pow=" << pow(2, 10) << endl;
    int a[2][2] = {1, 1, 1, 0}, ret[3][3] = {0};
    int a1[3][3] = {
        1, 1, 0,
        0, 1, 1,
        0, 1, 0
    };
    powMatrix(a1, 31, ret);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) cout << ret[i][j] << " ";
        cout << endl;
    }
    return 0;
}
