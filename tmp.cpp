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

#include "tmp1.cpp"
#define ms(x, n) memset(x, n, sizeof(x));
using namespace std;
//*(int(*)[10])arr_name
typedef long long LL;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1);
inline int lowbit(int x) { return x & -x; }
const int MAP_SIZE = 10;

int main() {
    const int* p;
    int a = 10000;
    p = &a;
    int b = 10;
    p = &b;
    int num = 0;
    int* const p1 = &num;
    *p1 += 1;
    cout << *p1 << endl;
    Apple apple = Apple(10, 20);
    cout << apple.getWeight() << endl;
    cout << apple.getPrice() << endl;

    // system("pause");
    return 0;
}