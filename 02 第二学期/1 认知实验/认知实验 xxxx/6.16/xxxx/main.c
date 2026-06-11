//
//[ANONYMIZED] [ANONYMIZED] [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬24.4.27 
//

#include "bigint.h"
int main()
{
	int op;//功能选择 
	do
	{
		show_menu();//展示菜单 
		while(scanf("%d",&op)!=1||op<1||op>8) {puts("输入错误\n请输入您想要选择的功能或退出(1-8):");getchar();}//输入合法判断 
		switch(op)//正确输入、功能选择 
		{
			case 1:
				puts("请输入长整数1");
				Input(num1);
				break;
			case 2:
				puts("请输入长整数2");
				Input(num2);
				break;
			case 3:
				puts("选择你要输出的整数:");
				puts("1:输出长整数1");
			    puts("2:输出长整数2");
				while(scanf("%d",&op)!=1||op<1||op>2) {puts("输入错误\n请输入您想要输出的整数(1-2):");getchar();} 
				if(op==1) Output(num1);
				else Output(num2); 
				break;
			case 4:
				puts("请输入被加数：");
				Input(num1);
				puts("请输入加数：");
				Input(num2);
				puts("被加数：");
				Output(num1);
			    puts("加数：");
				Output(num2);
				puts("和");
				Add(num1,num2,num3);
				Output(num3);
				break;
			case 5:
				puts("请输入被减数：");
				Input(num1);
				puts("请输入减数：");
				Input(num2);
				puts("被减数：");
				Output(num1);
			    puts("减数：");
				Output(num2);
				puts("差");
				if(Sub(num1,num2,num3)) putchar('-');
				Output(num3);
				break;
			case 6:
				puts("请输入被除数：");
				Input(num1);
				puts("请输入除数：");
				int d,y;
				scanf("%d",&d);
				y=Did(num1,d,num2);
				puts("商和余数");
				Output(num2);
				printf("%d\n",y);
				break;
			case 7:
				puts("请输入十进制数：");
				Input(num1);
				Con(num1,2,num2);
				Con(num1,8,num3);
				Con(num1,16,num4);
				puts("二进制、八进制和十六进制:");
				Output(num2);
				Output(num3);
				Output16(num4);
				break;
			default:
				break;
		}
	}
	while(op!=8);
}
