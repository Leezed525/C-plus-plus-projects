#include <iostream>
using namespace std;

const int N = 9;    // 数独的大小
const int NN = N*N; // 数独内所有位置的数量
const int S = 3;    // 子数独的大小
const int SS = S*S; // 每个子数独内的位置数量

// 存储数独的二维数组，0表示未填数
int grid[N][N];

int count = 0;

// 判断填入的数字是否合法
bool check(int row, int col, int num) {
    count += 1;
    // 检查行和列是否含有num
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) return false;
    }
    // 检查所属子数独是否含有num
    int r = row - row%S;
    int c = col - col%S;
    for (int i = r; i < r+S; i++) {
        for (int j = c; j < c+S; j++) {
            if (grid[i][j] == num) return false;
        }
    }
    return true;
}

// 开始填写数字，返回值为填写是否成功
bool fill(int row, int col) {
    // 数独填写完成，返回true
    if (row == N) return true;
    // 在当前行填写完成，转入下一行
    if (col == N) return fill(row+1, 0);
    // 当前位置有数字，跳过
    if (grid[row][col] > 0) return fill(row, col+1);
    // 尝试填写数字
    for (int num = 1; num <= N; num++) {
        if (check(row, col, num)) {
            grid[row][col] = num;
            if (fill(row, col+1)) return true; // 填写成功
            grid[row][col] = 0; // 回溯
        }
    }
    return false; // 所有数字都不行，返回false
}

// 输出数独的解
void output() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // 读入数独
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }
    cout << endl;
    // 填写数独
    // if (fill(0, 0)) {
    //     // 数独填写成功，输出结果
    //     output();
    // } else {
    //     // 数独无解
    //     cout << "No solution" << endl;
    // }
    while(fill(0,0)){
        output();
    }
    cout<< "运算了 " << count << " 次" << endl;
    return 0;
}