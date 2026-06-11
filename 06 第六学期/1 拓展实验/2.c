#include <stdio.h>
#define L 0.618
float f(float x);
int main(){
	float a=-3,b=5,e=0.3,x1,x2,f1,f2;
	int t=0;
	x1=b-L*(b-a);
	x2=a+L*(b-a);
	f1=f(x1);
	f2=f(x2);
	while(1){
		printf("第%d次迭代：",++t);
		printf("a=%.3f,b=%.3f,x1=%.3f,x2=%.3f,f1=%.3f,f2=%.3f,b-a=%.3f\n",a,b,x1,x2,f1,f2,b-a);
		if(b-a<e){
			printf("极值点是%.3f\n",0.5*(b+a));
			return 0; 
		}
		if(f1>f2){//消去a到x1的区间 
			printf("f1>f2，消去a到x1的区间\n");
			a=x1;
			x1=x2;
			x2=a+L*(b-a);
			f1=f2;
			f2=f(x2);
		}
		else{//消去x2到b的区间
			printf("f1<f2，消去x2到b的区间\n");
			b=x2;
			x2=x1;
			x1=b-L*(b-a);
			f2=f1;
			f1=f(x1);
		}
	}	
	return 0; 
}
float f(float x){
	return x*(x+2); 
} 
