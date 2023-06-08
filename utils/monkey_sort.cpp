#include <bits/stdc++.h>
using namespace std;
void monkeySort(vector<int> &arr);
bool isSorted(vector<int> &arr);
void shuffle(vector<int> &arr);
// 猴子排序
// 猴子排序是一个无限循环的排序算法，它每次都会检查数组是否已经排好序，如果没有就会重新打乱数组。
// 猴子排序的时间复杂度是O(∞)，因为它的运行时间是不确定的。
// 猴子排序的空间复杂度是O(1)，因为它只需要一个额外的变量来保存数组是否已经排好序。
// 猴子排序是不稳定的，因为它会打乱数组中相等元素的相对顺序。
// 猴子排序是原地排序，因为它不需要额外的空间。
// 猴子排序是一种不可取的排序算法，因为它的时间复杂度是不确定的，而且它的运行时间非常长。
// 猴子排序的代码如下所示：
void monkeySort(vector<int> &arr) {
    while (!isSorted(arr)) {
        shuffle(arr);
    }
}
// 猴子排序的代码非常简单，它只需要一个while循环，循环条件是数组没有排好序。
// 在循环体中，我们调用了isSorted函数来检查数组是否已经排好序，如果没有就调用shuffle函数来打乱数组。
// isSorted函数的代码如下所示：
bool isSorted(vector<int> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}
// isSorted函数的代码非常简单，它只需要一个for循环，循环条件是数组中的每个元素都要比前一个元素大。
// shuffle函数的代码如下所示：
void shuffle(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        // 下面的rand不用加随机数种子吗?
        swap(arr[i], arr[rand() % arr.size()]);
    }
}
// shuffle函数的代码也非常简单，它只需要一个for循环，循环条件是遍历数组中的每个元素，然后将当前元素与随机位置的元素交换。

int main() {
    // 计时
    clock_t startTime, endTime;
    startTime = clock();
    vector<int> arr = {1, 3, 2, 5, 4, 7, 4, 5, 2,100};
    cout << arr.size() << endl;
    monkeySort(arr);
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    endTime = clock();
    cout << endl << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    // system("pause");
    return 0;
}