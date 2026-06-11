#include "bigint.h"


void show_menu(void)//功能菜单函数
{
    puts("=======================================");
    puts("            长整数处理系统");
    puts("=======================================");
    puts("1:长整数1输入");
    puts("2:长整数2输入");
    puts("3:长整数输出");
    puts("4:长整数加法");
	puts("5:长整数减法");
	puts("6:长整数除法");
	puts("7:进制转换");
	puts("8:退出"); 
    puts("请输入您想要选择的功能或退出(1-8):");
}
int max(int x,int y)// 求两个数中的最大值
{
	if(x>y) return x;
	return y;
}
int Input(int *num)// 输入函数，将输入的数字字符串转换为整数数组
{
	char number[N];
	scanf("%s",number);
	num[0]=strlen(number);// 存储数字的长度
	for(int i=1;i<=num[0];i++) 
	{
		num[num[0]-i+1]=number[i-1]-'0';// 将字符转换为整数
		if(num[num[0]-i+1]>9||num[num[0]-i+1]<0)
		{
			puts("非法错误\n");
			puts("请重新输入：");
			Input(num);// 递归调用，直到输入合法
		}
	}
}
void Output(int *num)// 输出函数，将整数数组输出为数字字符串
{
	for(int i=num[0];i>=1;i--) printf("%d",num[i]);
	putchar('\n');
}
void Output16(int *num)// 输出16进制函数，将整数数组输出为16进制字符串
{
	for(int i=num[0];i>=1;i--) 
	{
		if(num[i]<10) printf("%d",num[i]);
		else printf("%c",num[i]-10+'A');
	}
	putchar('\n');
}
void Add(int *num1,int *num2,int *num3)// 加法函数，将两个大整数相加
{
	//高位补0 
	if(num2[0]>num1[0]) for(int i=num1[0]+1;i<=num2[0];i++) num1[i]=0; 
	else if(num2[0]<num1[0]) for(int i=num2[0]+1;i<=num1[0];i++) num2[i]=0;
	int p=0;//进位 
	for(int i=1;i<=max(num2[0],num1[0]);i++)
	{
		num3[i]=num1[i]+num2[i]+p;
		p=num3[i]/10;//下一轮进位 
		num3[i]%=10;//取余 
	}
	if(p==1)//若结果多一位 
	{
		num3[max(num2[0],num1[0])+1]=p;
		num3[0]=max(num2[0],num1[0])+1;
	}
	else num3[0]=max(num2[0],num1[0]);
}
int Sub(int *num1,int *num2,int *num3)// 减法函数，将两个大整数相减
{
	//高位补0
	if(num2[0]>num1[0]) for(int i=num1[0]+1;i<=num2[0];i++) num1[i]=0; 
	else if(num2[0]<num1[0]) for(int i=num2[0]+1;i<=num1[0];i++) num2[i]=0;
	int f=0; 
	for(int i=max(num1[0],num2[0]);i>=1;i--)
	{
		if(num1[i]!=num2[i])
		{
			if(num2[i]>num1[i]) f=1;//结果为负 
			break; 
		}
	}
	
	if(f==1)//结果为负,计算num2-num1 
	{
		for(int i=1;i<=num2[0];i++)//低位开始相减 
		{
			num3[i]=num2[i]-num1[i];
			if(num3[i]<0) //需要借位 
			{
				num3[i]+=10;
				int i1=i+1;//高位借位 
				while(num2[i1]==0&&i1<=num2[0]) num2[i1]=9,i1++;
				num2[i1]--;
			}
		}
		for(int i=num2[0];i>=1;i--)
		{
			if(num3[i]!=0) 
			{
				num3[0]=i;
				break;
			}
		}
		return 1; 
	}
	else//结果为正，计算num1-num2 
	{
		for(int i=1;i<=num1[0];i++)//低位开始相减 
		{
			num3[i]=num1[i]-num2[i];
			if(num3[i]<0) //需要借位 
			{
				num3[i]+=10;
				int i1=i+1;//高位借位 
				while(num1[i1]==0&&i1<=num1[0]) num1[i1]=9,i1++;
				num1[i1]--;
			}
		}
		for(int i=num1[0];i>=1;i--)
		{
			if(num3[i]!=0) 
			{
				num3[0]=i;
				break;
			}
		}
		return 0;	
	}
}
int Did(int *num1,int d,int *num2)// 除法函数，将两个大整数相除，返回余数
{
	int f=0;
	for(int i=num1[0];i>=1;i--)
	{
		num2[i]=num1[i]/d;
		if(!f&&num2[i])//商的最高位代表商的长度 
		{
			num2[0]=i;
			f=1;
		}
		if(i>=2) num1[i-1]+=num1[i]%d*10;
	}
	return num1[1]%d;//余数 
}
void Con(int *num1,int d,int *num2)// 进制转换函数，将十进制数转换为其他进制数
{
	int numt1[N],numt2[N],j=1;
	
	numt1[0]=num1[0];//存储num1的值，防止其被更改 
	for(int i=1;i<=num1[0];i++) numt1[i]=num1[i];
	
	while(1)
	{
		int y=Did(numt1,d,numt2);//余数 
		if(numt2[0]==1&&numt2[1]==0) 
		{
			if(y) num2[j++]=y;//最高位不为0 
			break;
		}
		num2[j++]=y; //得到商的低位到高位 
		
		numt1[0]=numt2[0];//更新被除数 
		for(int i=1;i<=numt2[0];i++) numt1[i]=numt2[i];	
	}
	num2[0]=j-1;//商的位数 
} 
