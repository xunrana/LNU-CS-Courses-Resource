#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define M 5				//蚂蚁数量m
#define a 1				//信息素因子α
#define b 2				//启发函数因子β
#define r 0.5 			//信息素挥发因子ρ
#define Q 1				//信息素常数Q
#define T 3				//最大迭代次数T等等。
#define N 3				//物品数量
#define C 6				//背包容量

int w[N]={3,4,2};		//背包物品重量 
int v[N]={5,2,7};		//背包物品的价值 
int ant[M][N]={0};		//蚁群的爬行路径 
double t[N] = {6,6,6};	//初始化信息素浓度 
int tc=6;				//剩余背包的容量 
int isSelected(int );
int main(){
	int k,i,j;
	int max = 0;
	for(k=0;k<T;k++){	//需要进行T次迭代
		printf("第%d次迭代开始:\n",k+1);
		int totalValue[M] = {0}; 
		max = 0;
		for(i=0;i<M;i++){
			for(j=0;j<N;j++){
				ant[i][j]=0;
			}
		}
		for(i=0;i<M;i++){
			printf("第%d只蚂蚁开始行动:\n",i+1);
			tc=C; 
			for(j=0;j<N;j++){
				if(tc<w[j]){
					continue;
				}
				if(isSelected(j)==1){//判断是否应该选择该物品 
					tc = tc - w[j]; //背包容量减少 
					ant[i][j]=1; //记录蚂蚁选择该物品 
					totalValue[i] += v[j]; //记录i只蚂蚁总的价值 
					printf("第%d个物品被第%d只蚂蚁选中:\n",j+1,i+1);
				}
				else{
					ant[i][j]=0;
				}
			}
			if(totalValue[max]<totalValue[i]){
				max = i;
			} 
		}
		for(j=0;j<N;j++){
			t[j]=t[j]*(1-r);
		} 
		for(i=0;i<M;i++){
			for(j=0;j<N;j++){
				if(ant[i][j]==1){
					t[j]+=Q*totalValue[i];
				}
			}
		}
	}
	for(j=0;j<N;j++){
		if(ant[max][j]==1){
			printf("w:%d,v:%d\n",w[j],v[j]);
		}
	}
	return 0;
}
int isSelected(int x){
	int j;
	double s=0,p,rd,s1=0;
	for(j=0;j<N;j++){
		s+=pow(t[j],a)*pow(v[j],b);
		if(j<x){
			s1+=pow(t[j],a)*pow(v[j],b);
		}
	}
	s1 = s1/s;
	p =pow(t[x],a)*pow(v[x],b)/s; 
	Sleep(1000);
	srand((unsigned)time(NULL)*10);
	rd=rand()%101/100.0;
	printf("随机数:%.2f,概率:%.2f\n",rd,p); 
	if(rd>=s1 && rd<= s1+p){
		return 1;
	}
	return 0;
}
