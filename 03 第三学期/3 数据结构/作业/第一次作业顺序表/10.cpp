#include <bits/stdc++.h>
using namespace std; 
int main()
{
	int n;
	cin>>n;
	int a[n],b[n];
	for(int i=0;i<n;i++) cin>>a[i];
	sort(a,a+n);
	for(int i=0;i<n;i++) b[i]=a[i];
	int cnt=0,k;
	for(int i=0;i<n-2;i++)
	for(int j=i+1;j<n-1;j++)
	{
		k=j+1;
		while(k<n&&b[k]<a[i]+a[j]) k++;
		if(k<n&&b[k]==a[i]+a[j]) 
		{
			b[k]=0;
			cnt++;
		}
	}
	cout<<cnt;
} 
