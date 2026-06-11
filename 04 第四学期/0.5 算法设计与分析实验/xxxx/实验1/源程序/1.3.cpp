#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[1000010],w[1000010];
int merge(int l,int r)// 合并函数，计算逆序对数
{
    if(l>=r) return 0;// 如果左边界大于或等于右边界，返回 0（没有逆序对）
    int mid=l+r>>1; // 计算中间点
    int res=merge(l,mid)+merge(mid+1,r);// 递归计算左右部分的逆序对数，并求和
    
	int k=1,i=l,j=mid+1;// 初始化指针和临时数组的索引
    while(i<=mid&&j<=r)// 合并两个有序子数组
    {
        if(a[i]<=a[j]) w[k++]=a[i++]; // 如果左边的元素小于等于右边的元素,将左边的元素加入临时数组
        else w[k++]=a[j++],res=res+mid-i+1;// 否则，将右边的元素加入临时数组，计算逆序对数 
    }
    while(i<=mid) w[k++]=a[i++];// 将剩余的左边元素加入临时数组
    while(j<=r) w[k++]=a[j++];// 将剩余的右边元素加入临时数组
    for(int i=1,j=l;i<k;i++) a[j++]=w[i];// 将临时数组中的元素复制回原数组
    return res;// 返回逆序对数
}

signed main()
{
	cin>>n;// 读取数组大小
	for(int i=1;i<=n;i++) cin>>a[i];// 读取数组元素
	int res=merge(1,n);// 计算逆序对数
	cout<<res;// 输出结果
}
/*
5
3 1 4 5 2
*/
