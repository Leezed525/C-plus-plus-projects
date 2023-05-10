#include <windows.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define ms(x, n) memset(x, n, sizeof(x));
using namespace std;
//*(int(*)[10])arr_name
typedef long long LL;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1);
inline int lowbit(int x) { return x & -x; }
const int MAP_SIZE = 10;

int main() {
    // const int* p;
    // int a = 10000;
    // p = &a;
    // cout << *p << endl;
    // a = 1;
    // cout << *p << endl;
    // int b = 666;
    // p = &b;
    // cout << *p << endl;

    // int j = 0, i = 0;
    // while (j++ < 10) {
    //     printf("这是第%d次输出------", j);
    //     for (i = 0; i < 1000000000; i++)
    //         ;
    //     printf("\r");
    // }

    // HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // if (console_handle == INVALID_HANDLE_VALUE) {
    //     std::cerr << "Failed to get console handle.\n";
    //     return 1;
    // }

    // DWORD bytes_written;
    // if (!WriteConsole(console_handle, "\x1b[A", 3, &bytes_written, nullptr)) {
    //     std::cerr << "Failed to move cursor.\n";
    //     return 1;
    // }

    // std::cout << "Hello";

    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (console_handle == INVALID_HANDLE_VALUE) {
        cerr << "Failed to get console handle.\n";
        return 1;
    }

    // 初始化地图
    char map[MAP_SIZE][MAP_SIZE];
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            map[i][j] = '#';
        }
    }

    // 输出地图
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }

    // 在地图上修改某个点
    int x = 5, y = 5;
    map[x][y] = 'X';
    COORD cur = {y, x};
    SetConsoleCursorPosition(console_handle, cur);
    cout << map[x][y];

    SetConsoleCursorPosition(console_handle, {10,10});
    system("pause");
    return 0;
}