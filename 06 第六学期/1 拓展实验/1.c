#include <stdio.h>
float f(float a1);
void exchange(float *a1, float *a2);
int main(){
	float a1,a2,a3,f1,f2,f3,h;
	printf("请输入初始点和步长\n");
	scanf("%f",&a1);
	scanf("%f",&h);
	a2=a1+h;//求出a2
	f1=f(a1);
	f2=f(a2);
	if(f1>f2){//呈现出大-小的趋势，找a3 
		while(1){
			h=2*h; 
			a3=a2+h;
			f3=f(a3);
			if(f3>f2){//呈现大-小-大的趋势，找到单峰区间 
				printf("单峰区间是[%.2f,%.2f]\n",a1,a3);
				return 0;	
			}
			else{//去掉[a1,a2]无效区间，继续寻找 
				a1=a2;
				a2=a3;
				f1=f2;
				f2=f3;
			}
		}	
	} 
	else{//呈现出小-大的趋势，需要调整方向 
		h=-h;
		exchange(&a1,&a2);
		exchange(&a1,&a2);
		while(1){
			h=2*h;
			a3=a2+h;
			f3=f(a3);
			if(f3>f2){//呈现出大-小-大趋势，得到单峰区间 
				printf("单峰区间是[%.2f,%.2f]\n",a3,a1);
				return 0;
			}
			else{
				a1=a2;
				a2=a3;
				f1=f2;
				f2=f3;
			}
		}		
	}
	return 0;
}
float f(float a1){
	return a1*a1;
}
void exchange(float *a1, float *a2){
	float temp;
	temp=*a1;
	*a1=*a2;
	*a2=temp;
}
