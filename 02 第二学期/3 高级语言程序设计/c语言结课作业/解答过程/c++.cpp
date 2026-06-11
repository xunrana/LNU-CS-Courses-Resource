#include<bits/stdc++.h>
using namespace std;
int t,a,b;
bool ok(int a,int b){
	if(b>a)swap(a,b);
	if(a==b||a>=b*2)return true;
	return !ok(b,a-b);
}
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%d%d",&a,&b);
		if(ok(a,b))puts("Stan wins");
		else puts("Ollie wins");
	}
	return 0;
}

