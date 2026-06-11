#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

void generate(int a[]) {
    // 随机生成数组
    for (int i = 0; i < 100000; i++) {
        a[i] = rand() % 10000;
    }
    sort(a, a + 100000);
}

void solve(int a[], int n) {
    sort(a, a + n);
    int max = a[0], maxCount = 0;   // max：整个数组的众数，maxCount：整个数组的众数出现的次数
    int temp = a[0], tempCount = 0; // temp：当前元素，tempCount：当前元素出现的次数
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
    cout << max << "，出现次数：" << maxCount << endl;
}

int main() {
    // 给定n个正整数，编写程序找出它们中出现次数最多的数，如果这样的数有多个，输出其中最小的数。
    int a[100000];
    generate(a);
    solve(a, 100000);
}