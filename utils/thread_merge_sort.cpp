#include <iostream>
#include <vector>
#include <thread>

// 归并操作
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // 创建临时数组
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);
    
    // 拷贝数据到临时数组
    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArr[j] = arr[mid + 1 + j];
    
    // 归并临时数组到原数组
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }
    
    // 处理剩余的元素
    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

// 归并排序
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // 创建两个线程递归地排序左半部分和右半部分
        std::thread leftThread(mergeSort, std::ref(arr), left, mid);
        std::thread rightThread(mergeSort, std::ref(arr), mid + 1, right);
        
        // 等待两个线程排序完成
        leftThread.join();
        rightThread.join();
        
        // 归并已排序的两个部分
        merge(arr, left, mid, right);
    }
}

int main() {
    std::vector<int> arr = {9, 4, 7, 2, 1, 5, 8, 3, 6};
    
    std::cout << "原始数组: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;
    
    mergeSort(arr, 0, arr.size() - 1);
    
    std::cout << "排序后数组: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;
    
    return 0;
}
