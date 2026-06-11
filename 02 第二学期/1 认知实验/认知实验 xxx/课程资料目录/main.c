#include "bigint.h"


int main(){
	
	while(1){
		printf("选择功能：1.输入、2.输出、3.加法、4.减法、5.除法、6.退出系统、7.进制转换");
		int choose;
		scanf("%d",&choose);
		getchar();
		if(choose==6){
			break;
		} 
		switch (choose){
			case 1:
				input();
				break;
			case 2:
				output();
				break;
			case 3:
				plus();
				break;
			case 4:
				subtraction();
				break;
			case 5:
				division();
				break;
			case 7:
				system_switch();
				break;
			default:
				break;
		}
	}
	
	return 0;
}
