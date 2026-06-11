#include <bits/stdc++.h>// 引入所有标准C++库
using namespace std;
pair<int,int>findmoderec(vector<int>&a,int l,int r)
{
	if(l==r) return {a[l],1};// 基本情况：如果区间内只有一个元素，返回该元素和出现次数1
	int m=l+r>>1;// 找到中点
	pair<int,int>lr=findmoderec(a,l,m);// 递归处理左半部分
	pair<int,int>rr=findmoderec(a,m+1,r); // 递归处理右半部分
	if(lr.first==rr.first) return {lr.first,lr.second+rr.second};// 如果左右部分的众数相同，返回合并后的众数和出现次数
	else
	{
		int lc=lr.second;// 左部分众数的计数
		int rc=rr.second;// 右部分众数的计数
		for(int i=m+1;i<=r&&a[i]==lr.first;i++) lc++;// 扩展左部分众数的计数到右半部分
		for(int i=m;i>=l&&a[i]==rr.first;i--) rc++;// 扩展右部分众数的计数到左半部分
		if(lc>rc) return {lr.first,lc};// 返回较大计数的众数
		else return {rr.first,rc};// 返回较大计数的众数
	}	
}


pair<int,int>findmode(vector<int>&a)// 查找数组众数的主函数
{
	if(a.empty()) return {-1,0};// 如果数组为空，返回-1和计数0
	return findmoderec(a,0,a.size()-1);// 调用递归函数处理整个数组
}
int main()
{
	vector<int>a={1,2,2,3,5};// 示例输入数组
	pair<int,int>res=findmode(a);// 查找众数
	cout<<"众数是 "<<res.first<<",重数为 "<<res.second<<"\n";// 输出众数和出现次数
} 
