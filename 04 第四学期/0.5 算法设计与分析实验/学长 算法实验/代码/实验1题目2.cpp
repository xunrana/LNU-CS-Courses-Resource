#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

int count(int a[], int left, int right, int x) {
    // 在数组a中，求出[left, right]区间内x出现的次数
    if (left > right) return 0;
    int num = 0;
    for (int i = left; i <= right; i++)
        if (a[i] == x) num++;
    return num;
}

// 给定一个整数序列，每个元素出现的次数称为重数，重数最大的数据元素称为众数。设计算法对递增有序序列a求众数。
int findMax(int a[], int left, int right) {
    // 在递增数组a中，求出[left, right]区间内的众数
    // 如果某一边的众数出现次数大于另一边，则该边的众数一定是整个数组的众数
    if (left == right) return a[left];
    int mid = (left + right) / 2;
    int leftMax = findMax(a, left, mid);
    int rightMax = findMax(a, mid + 1, right);
    if (count(a, left, right, leftMax) > count(a, left, right, rightMax))
        return leftMax;
    else
        return rightMax;
}

// 换一种，遍历的方法
int findMax2(int a[], int n, int &count) {
    // 在递增数组a中，求出众数
    sort(a, a + n);
    int max = a[0], maxCount = 0;
    int temp = a[0], tempCount = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == temp) {
            tempCount++;
        }
        else {
            temp = a[i];
            tempCount = 1;
        }
        if (tempCount > maxCount) {
            max = temp;
            maxCount = tempCount;
        }
    }
    count = maxCount;
    return max;
}

void generate(int a[]) {
    // 随机生成数组
    for (int i = 0; i < 100000; i++) {
        a[i] = rand() % 10000;
    }
    sort(a, a + 100000);
}

void solve(int a[], int n) {
    clock_t start, end;
    
    start = clock();
    int max = findMax(a, 0, n - 1);
    cout << "众数为：" << max << "，出现次数为：" << count(a, 0, n - 1, max) << endl;
    end = clock();
    cout << "递归算法用时：" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    start = clock();
    int count2 = 0;
    int max2 = findMax2(a, n, count2);
    cout << "众数为：" << max2 << "，出现次数为：" << count2 << endl;
    end = clock();
    cout << "遍历算法用时：" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    
    // 第一种方法不仅慢，而且需要有序数组，所以第二种方法更好
}

int main() {
    int a[100000];
    generate(a);
    solve(a, sizeof(a) / sizeof(int));
    return 0;
}