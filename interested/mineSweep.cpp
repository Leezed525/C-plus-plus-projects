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
// 地图大小
const int MAP_SIZE = 20;
// 总共有多少雷
const int MINE_COUNT = 30;
// 当前找到了多少雷
int find_count = 0;
// 展示地图
char map[MAP_SIZE][MAP_SIZE];
// 雷图
int mine_map[MAP_SIZE][MAP_SIZE];
// 判断当前点是否已经被检查过
bool check_map[MAP_SIZE][MAP_SIZE];
// 上下左右左上右上左下右下
int pos[] = {-1, 0, 1, 0, 0, -1, 0, 1, -1, -1, 1, -1, -1, 1, 1, 1};
// 控制台指针
HANDLE console_handle;
// 当前光标位置
COORD current_cur_pos;

bool check_pos_valid(int row, int col) {
    if (row < 0 || row >= MAP_SIZE || col < 0 || col >= MAP_SIZE) {
        return false;
    }
    return true;
}

int get_surround_mine_count(int row, int col) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int r = row + pos[i * 2];
        int c = col + pos[i * 2 + 1];
        if (!check_pos_valid(r, c)) continue;
        if (mine_map[r][c] == -1) {
            count += 1;
        }
    }
    return count;
}

// 输出地雷图
void print_mine_map() {
    for (int i = 0; i < MAP_SIZE; i += 1) {
        for (int j = 0; j < MAP_SIZE; j += 1) {
            if (mine_map[i][j] == -1)
                printf("X");
            else if (mine_map[i][j] == 0)
                printf(" ");
            else
                printf("%d", mine_map[i][j]);
        }
        printf("\n");
    }
}

void print_all_map() {
    for (int i = 0; i < MAP_SIZE; i += 1) {
        for (int j = 0; j < MAP_SIZE; j += 1) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void move_cur_pos(int row, int col) {
    current_cur_pos.X = col;
    current_cur_pos.Y = row;
}

void set_cur_pos(int row, int col, char ch) {
    Sleep(1);
    SetConsoleCursorPosition(console_handle, {(short)col, (short)row});
    map[row][col] = ch;
    cout << (map[row][col] == '0' ? ' ' : map[row][col]);
}

// 初始化地图
void initMap() {
    // 生成地图
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            map[i][j] = '#';
        }
    }
    print_all_map();
    // 随机生成地雷
    for (int i = 0; i < MINE_COUNT; i += 1) {
        int x = rand() % MAP_SIZE;
        int y = rand() % MAP_SIZE;
        if (mine_map[x][y] || (x == 0 && y == 0)) {
            i -= 1;
            continue;
        }
        mine_map[x][y] = -1;
    }
    // 生成数字地图
    for (int i = 0; i < MAP_SIZE; i += 1) {
        for (int j = 0; j < MAP_SIZE; j += 1) {
            if (mine_map[i][j] == -1) continue;
            mine_map[i][j] = get_surround_mine_count(i, j);
        }
    }
}

// 在 100,0的位置输出 位置
void debug_pos_log() { SetConsoleCursorPosition(console_handle, {0, 60}); }

// 广度搜索展开地图
void discovery_map(int x, int y) {
    queue<pair<int, int>> q;
    q.push({x, y});
    while (!q.empty()) {
        // Sleep(10);
        pair<int, int> cursor = q.front();
        q.pop();
        int row = cursor.first;
        int col = cursor.second;
        set_cur_pos(row, col, mine_map[row][col] == 0 ? ' ' : mine_map[row][col] + '0');
        for (int i = 0; i < 8; i++) {
            int r = cursor.first + pos[i * 2];
            int c = cursor.second + pos[i * 2 + 1];
            if (!check_pos_valid(r, c)) continue;
            if (mine_map[r][c] == 0 && map[r][c] == '#') {
                map[r][c] = ' ';
                q.push({r, c});
            } else if (mine_map[r][c] > 0 && map[r][c] == '#') {
                map[r][c] = mine_map[r][c] + '0';
                set_cur_pos(r, c, mine_map[r][c] + '0');
            }
        }
    }
}

// 点击当前位置
void click_current_pos() {
    int row = current_cur_pos.Y;
    int col = current_cur_pos.X;
    if (mine_map[row][col] == 0) {
        discovery_map(row, col);
    } else {
        set_cur_pos(row, col, mine_map[row][col] + '0');
    }
}

// 检查数字的位置
void check_pos(int row, int col) {
    int discoveried_mine = 0;
    int hide_node = 0;
    for (int i = 0; i < 8; i++) {
        int r = row + pos[i * 2];
        int c = col + pos[i * 2 + 1];
        if (!check_pos_valid(r, c)) continue;
        if (map[r][c] == '#') {
            hide_node += 1;
        } else if (map[r][c] == 'X') {
            discoveried_mine += 1;
        }
    }
    if (discoveried_mine == mine_map[row][col]) {
        for (int i = 0; i < 8; i++) {
            int r = row + pos[i * 2];
            int c = col + pos[i * 2 + 1];
            if (!check_pos_valid(r, c)) continue;
            if (map[r][c] == '#') {
                move_cur_pos(r, c);
                click_current_pos();
                // map[r][c] = ' ';
                // set_cur_pos(r, c, ' ');
            }
        }
        // 当前位置标记上检查完毕
        check_map[row][col] = true;
    }
    if (hide_node + discoveried_mine == mine_map[row][col]) {
        for (int i = 0; i < 8; i++) {
            int r = row + pos[i * 2];
            int c = col + pos[i * 2 + 1];
            if (!check_pos_valid(r, c)) continue;
            if (map[r][c] == '#') {
                map[r][c] = 'X';
                find_count += 1;
                set_cur_pos(r, c, 'X');
            }
        }
        // 当前位置标记上检查完毕
        check_map[row][col] = true;
    }
}

// 解决扫雷问题
void resolve_mine_map() {
    current_cur_pos = {0, 0};
    // 先点开地图
    discovery_map(0, 0);
    while (find_count < MINE_COUNT) {
        // 点击当前位置
        // click_current_pos();
        // queue<pair<int, int>> q;
        int flag_count = 0;
        for (int i = 0; i < MAP_SIZE; i += 1) {
            for (int j = 0; j < MAP_SIZE; j += 1) {
                // 如果地图中的是数字并且该点没有被扫描完毕
                if (map[i][j] != ' ' && map[i][j] != '#' && !check_map[i][j]) {
                    check_pos(i, j);
                    flag_count += 1;
                }
            }
        }
        if (flag_count == 0) {
            cout << "无法继续扫雷" << endl;
            break;
        }
        debug_pos_log();
        cout << "已找到: " << find_count << "个雷" << endl;
    }
    debug_pos_log();
    cout << "扫雷完毕" << endl;
}

int main() {
    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (console_handle == INVALID_HANDLE_VALUE) {
        cerr << "Failed to get console handle.\n";
        return 1;
    }
    initMap();
    // print_mine_map();
    resolve_mine_map();

    system("pause");
    return 0;
}