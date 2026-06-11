#include <stdio.h>
#include <math.h>
#define N 4
#define C	10
#define IT	30
#define DT	10
#define WT	0
#define NT	3
#define e	2
double energy(int s[], int n);
int w[N]={2,3,5,5};
int v[N]={2,4,3,7};
int s[N]={0};
int main(){
	int t,i;
	t=30;
	createRD(s,N);
	prt();
	while(t>0){
		for(i=0;i<NT;i++){
			annealing(t);
		}
		prt();
		t=t-DT;	
	}
	return 0;
} 
void createRD(int s[],int n){
	int i,rd,totalWeight=0;
	for(i=0;i<n;i++){
		Sleep((rand()%2+1)*1000);
		srand((unsigned)time(NULL));
		rd=rand()%2;
		if(totalWeight+rd*w[i]>C){
			s[i]=0;
			continue;
		}
		s[i]=rd;
		totalWeight+=s[i]*w[i];
	}
}
void annealing(int t){
	int ss[N]={0},i;
	double rd,p;
	createRD(ss,N);
	Sleep((rand()%2+1)*1000);
	srand((unsigned)time(NULL));
	rd=rand()%1001/1000;
	p=pow(e,-(energy(ss,N)-energy(s,N))/t);
	if(energy(ss,N)<energy(s,N) || p<=rd){
		for(i=0;i<N;i++){
			s[i]=ss[i];
		}
	}
	
}
void prt(){
	int i;
	int totalValue=0;
	for(i=0;i<N;i++){
		printf("%d ",w[i]);
	}
	printf("\n");
	for(i=0;i<N;i++){
		printf("%d ",v[i]);
	}
	printf("\n");
	for(i=0;i<N;i++){
		printf("%d ",s[i]);
		totalValue+=s[i]*v[i];
	}
	printf("×Ü¼ÛÖµ:%d\n",totalValue);
}
double energy(int s[], int n){
	double result=0.0;
	int totalValue=0;
	int i;
	for(i=0;i<n;i++){
		totalValue+=s[i]*v[i];
	}
	result = 1.0/totalValue;
	return result;
}
