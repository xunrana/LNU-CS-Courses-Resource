#include <bits/stdc++.h>
using namespace std;
// 定义最大数组大小
const int MAX_SIZE=10;
int n,a[MAX_SIZE],dp[MAX_SIZE];
int main()
{	
/*
6
5 1 2 10 6 2
*/
    // 读取输入的整数n，表示数组的大小
    cin >> n;
    // 读取数组a的值并初始化dp数组
    for(int i = 1; i <= n; i++) {
        cin >> a[i]; // 输入数组a的值
        dp[i] = 0;   // 初始化dp数组为0
    }
    // 动态规划的初始状态
    dp[1] = a[1]; // 第一个元素直接赋值给dp[1]
    // 动态规划递推
    for(int i = 2; i <= n; i++) {
        // 计算第i个位置的最大值，要么是前一个位置的最大值，要么是前两个位置的最大值加上当前值
        dp[i] = max(dp[i-1], dp[i-2] + a[i]);
    }
    // 输出dp数组
    for(int i=1;i<=n;i++) cout<<dp[i]<<" "; 
}

