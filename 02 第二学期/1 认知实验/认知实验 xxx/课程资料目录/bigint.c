#include "bigint.h"

int max(int a,int b){
	if(a>=b){
		return a;
	}else{
		return b;
	}
}

int cmp(int a[],int b[]){
	int i;
	for(i=0;i<count1;i++){
		if(a[i]>=b[i]){
			continue;
		}else{
			return -1;
		}
	}
	return 1;
}

void input(){
	char s[110];
//	getchar();
	scanf("%s",&s);
	getchar();
	count1=strlen(s);
	int i;
	for(i=0;i<count1;i++){
		a[i]=s[count1-1-i]-'0';
	}
	scanf("%s",&s);
	count2=strlen(s);
	for(i=0;i<count2;i++){
		b[i]=s[count2-1-i]-'0';
	}
}

void output(){
	int i;
	for(i=count1-1;i>=0;i--){
		printf("%d",a[i]);
	}
	printf("\n");
	for(i=count2-1;i>=0;i--){
		printf("%d",b[i]);
	}
	printf("\n");
}

void plus(){
	int i,carry=0;
	int z[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬0];
	for(i=0;i<max(count1,count2);i++){
		if(i<count1&&i<count2){
			z[i]=(a[i]+b[i]+carry)%10;
			carry=(a[i]+b[i]+carry)/10;
		}else if(i<count1){
			z[i]=(a[i]+carry)%10;
			carry=(a[i]+carry)/10;
		}else{
			z[i]=(b[i]+carry)%10;
			carry=(b[i]+carry)/10;
		}
	}
	for(i=max(count1,count2)-1;i>=0;i--){
		printf("%d",z[i]);
	}
	printf("\n");
}

void subtraction(){
	int c[1[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];
	int i;
//	clear(c);

	c[0]=0;
	int flag=0;
	for (i = 0; i < max(count1,count2); i++) {
    	// 逐位相减
    	if(count1>count2||count1==count2&&cmp(a,b)==1){
    		c[i] += a[i] - b[i];
    	}else{
    		c[i] += b[i]-a[i];
    		flag=1;
		}
    	if (c[i] < 0) {
      		// 借位
      		c[i + 1] -= 1;
     		c[i] += 10;
   		}
  	}
  	if(flag==1){
			printf("-");
		}
	for(i=max(count1,count2)-1;i>=0;i--){
		printf("%d",c[i]);
	}
	printf("\n");
}


void division(){
	int b,rm,ans[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬0],i;
	printf("输入整数（int类型）\n");
	scanf("%d",&b);
	for(i=count1-1;i>=0;i--)
    {
        ans[count1-i]=(rm*10+a[i])/b;    //注意这里是都是对第i位操作 
        rm=(rm*10+a[i])%b;        //每次算的余数都是这个rm，直接用"%"符号就可以了 
    }
    int lenans=1;
    while(ans[lenans]==0&&lenans!=count1)
    {
        lenans++;
    }
    printf("结果=");
    for(i=lenans;i<=count1;i++){
    	printf("%d",ans[i]);
	}
	printf("\n");
	printf("余数=%d\n",rm);
}



char str[1000];//输入字符串
int start[1000],ans[1000],res[1000]; //被除数，商，余数

//转换前后的进制
const int oldBase = 10;
int newBase = 2;

void system_switch(){
	scanf("%s",str);
	printf("转化为几进制？\n");
	scanf("%d",&newBase);
    change();
    solve();
    output_s();
}

void change()
{//各个数位还原为数字形式
    int i,len = strlen(str);
    start[0] = len;
    for(i=1;i<= len;i++)
    {
        if(str[i-1] >= '0' && str[i-1] <= '9')
        {
            start[i] = str[i-1] - '0';
        }
    } 
}

void solve()
{
    memset(res,0,sizeof(res));//余数初始化为空
    int y,i,j;
    //模n取余法，(总体规律是先余为低位，后余为高位)
    while(start[0] >= 1)
    {//只要被除数仍然大于等于1，那就继续“模2取余”
        y=0;
        i=1;
        ans[0]=start[0];
        //
        while(i <= start[0])
        {
            y = y * oldBase + start[i];
            ans[i++] = y/newBase;
            y %= newBase; 
        }
        res[++res[0]] = y;//这一轮运算得到的余数
        i = 1;
        //找到下一轮商的起始处
        while((i<=ans[0]) && (ans[i]==0)) i++;
        //清除这一轮使用的被除数
        memset(start,0,sizeof(start));
        //本轮得到的商变为下一轮的被除数
        for(j = i;j <= ans[0];j++)
            start[++start[0]] = ans[j]; 
        memset(ans,0,sizeof(ans)); //清除这一轮的商，为下一轮运算做准备
    } 
}

void output_s()
{//从高位到低位逆序输出
    int i;
    for(i = res[0];i >= 1;--i)
    {  
    	if(res[i]<10){
        	printf("%d",res[i]);
    	}else{
    		printf("%c",res[i]-10+'A');
		}
    }
    printf("\n"); 
}

