#include <iostream>
#include <string>
#include <ctime>

using namespace std;

//采用分治法求序列A中逆序对的个数
int count(int A[], int left, int right) {
    // 在数组A中，求出[left, right]区间内的逆序对个数
    if (left == right) return 0;
    int mid = (left + right) / 2;
    int leftCount = count(A, left, mid);
    int rightCount = count(A, mid + 1, right);
    int crossCount = 0;
    int* temp = new int[right - left + 1];
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (A[i] <= A[j]) {
            temp[k++] = A[i++];
        }
        else {
            temp[k++] = A[j++];
            crossCount += mid - i + 1;
        }
    }
    while (i <= mid) {
        temp[k++] = A[i++];
    }
    while (j <= right) {
        temp[k++] = A[j++];
    }
    for (int i = 0; i < k; i++) {
        A[left + i] = temp[i];
    }
    return leftCount + rightCount + crossCount;
}

// 方法二：两层循环，时间复杂度O(n^2)
int count2(int A[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i; j < n; j++) {
            if (A[i] > A[j]) {
                count++;
            }
        }
    }
    return count;
}

void generate(int A[]) {
    // 随机生成数组
    for (int i = 0; i < 10000; i++) {
        A[i] = rand() % 10000;
    }
}

void solve(int A[], int n) {
    int B[10000];
    for (int i = 0; i < 10000; i++) {
        B[i] = A[i];
    }

    clock_t start, end;
    start = clock();
    cout << count(A, 0, 10000) << endl;
    end = clock();
    cout << "分治法耗时：" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    start = clock();
    cout << count2(B, 10000) << endl;
    end = clock();
    cout << "两层循环耗时：" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    // 第一种方法显然更快
}

int main() {
    int A[10000];
    generate(A);
    solve(A, 10000);
    return 0;
}