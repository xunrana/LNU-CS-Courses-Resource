	#include<stdio.h>
#include<windows.h>
#include<time.h>
#define N 4 //种群数量
#define M N //假设群体规模也是4 
#define T 3 //最大迭代次数 
void init();
void selectAndCopy();
void crossover();
void mutation();
double fitness(int i);
void prt1();
void sort();
int d[N][N]={{0,3,6,7},{5,0,2,3},{6,4,0,2},{3,7,5,0}};
int s[M][N]={0};	
int main(){
	int k;
	for(k=0;k<T;k++){
		init(); //第一步，初始化，初始化种群等 
		prt1();
		selectAndCopy(); //第二步，从初始化种群中选择个体进行复制，保证种群个数不变 
		prt1();
		crossover();//第三步交叉 
		prt1();
		mutation();	//变异
		prt1();	 
	}
	printf("最优解是:%d行\n",M);
	return 0;
} 
void init(){//初始化种群 
	int i,j;
	for(i=0;i<M;i++){//初始化s每一行(每个个体)都是0123 
		for(j=0;j<N;j++){
			s[i][j]=j;
		}
	}
	for(i=1;i<M;i++){
		int t;
		t=s[i][0];
		s[i][0]=s[i][i];
		s[i][i]=t;
	} 
	sort();
}
void selectAndCopy(){
	int i,k,j;
	int ss[M][N]={0}; //用于复制选择后的个体 
	double totalFitness=0.0;
	for(i=0;i<M;i++){
		totalFitness+=fitness(i); //所有个体的适应度总和，用于求概率 
	}
	//也可以进行改进，保证最后一行一定被复制，因为这一行适应度最大 
	for(k=0;k<M;k++){ //选择迭代，每次迭代都需要选择一个个体，一共选择M个体，保持种群规模不变 
		double rd,totalSum=0.0;
		Sleep(1000);
		srand((unsigned)time(NULL));
		rd=rand()%1001/1000;
		for(i=0;i<M;i++){
			double lower=0,upper=0,p;
			lower=totalSum;
			p=fitness(i)/totalFitness; //个体i被选择的概率 
			upper=totalSum+p;
			if(rd>=lower && rd<=upper){
				for(j=0;j<N;j++){
					ss[k][j]=s[i][j];
				}
				break;
			}
			totalSum+=p;
		}	
	}
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			s[i][j]=ss[i][j];
		}
	}
	sort();
}
void crossover(){ //交叉操作 
	int rd,t,m,n,j;
	Sleep(1000);
	srand((unsigned)time(NULL));
	rd=rand()%N; //要生成一个随机整数，rd处于区间[0,N-1] 
	t=s[0][rd];
	s[0][rd]=s[1][rd];
	s[1][rd]=t;
	for(j=0;j<N;j++){//找到与交换后的数值一样的位置，然后让两个个体对应位置交互 
		if(s[0][j]==s[0][rd] && j!=rd){//交换j这个位置两个个体的数 
			m=j;//记录一下s[0]重复数据的位置j，用m标记 
		}
	}
	for(j=0;j<N;j++){//找到与交换后的数值一样的位置，然后让两个个体对应位置交互 
		if(s[1][j]==s[1][rd] && j!=rd){//交换j这个位置两个个体的数 
			n=j;//记录一下s[2]重复数据的位置j，用n标记 
		}
	}
	t=s[0][m];
	s[0][m]=s[1][n];
	s[1][n]=t;
	sort();
}
void mutation(){//变异操作 
	int rd1,rd2,i,t;
	for(i=0;i<2;i++){//假设只变异前两个个体 
		Sleep(1000);
		srand((unsigned)time(NULL));
		rd1=rand()%N;
		Sleep(1000);
		srand((unsigned)time(NULL));
		rd2=rand()%N;
		t=s[i][rd1];
		s[i][rd1]=s[i][rd2];
		s[i][rd2]=t; 
	}
	sort();
}
double fitness(int i){
	int j,m,n;
	double result=0.0;
	for(j=0;j<N-1;j++){
		m=s[i][j];
		n=s[i][j+1];
		if(d[m][n]==0&&m!=n){ //如果d[m][n]==0，说明城市m到n没有路径 
			return 0;
		}
		result+=d[m][n];
	}
	m=s[i][N-1]; 
	n=s[i][0];
	result+=d[m][n];
	return 1/result;
}
void prt1(){
	printf("---------------------------------------\n");
	int i,j;
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			printf("%d\t",s[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<M;i++){
		printf("个体%d适应度%.4f\n",i,fitness(i));
	} 
	printf("---------------------------------------\n");
}
void sort(){//按照适应度大小对种群的个体进行有小到大排序 
	int i,j,k;
	for(i=0;i<M-1;i++){
		for(j=0;j<M-1-i;j++){
			if(fitness(j)>fitness(j+1)){
				for(k=0;k<N;k++){
					double t;
					t=s[j][k];
					s[j][k]=s[j+1][k];
					s[j+1][k]=t;
				}
			}
		}
	}
}
