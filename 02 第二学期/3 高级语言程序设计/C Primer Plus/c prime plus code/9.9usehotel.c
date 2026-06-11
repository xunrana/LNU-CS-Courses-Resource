#include <stdio.h>
#include "hotel.h"
int main(void)
{
	int nights;
	double hotel_rate;
	int code;
	while((code=menu())!=QUIT)
	{
		switch(code)
		{
			case 1:hotel_rate=HOTEL1;break;
			case 2:hotel_rate=HOTEL2;break;
			case 3:hotel_rate=HOTEL3;break;
			case 4:hotel_rate=HOTEL4;break;
			default:hotel_rate=0.0;printf("Oops!\n");break;
		}
		nights=getnights();
		showprice(hotel_rate,nights);
	}
	printf("Thank you and goodbye.\n");
	return 0;
}








#include <stdio.h>
#include "hotel.h"
int menu(void)
{
	int code,status;
	printf("\n%s%s\n",STARS,STARS);
	printf("Enter the number of the desired hotel:\n");
	printf("1) Fairfield Arms          2) Hotel Olympic\n");
	printf("3) Chertworthy Plaza       4) The Stockton\n");
	printf("5) quit\n");
	printf("%s%s\n",STARS,STARS);
	while((status=scanf("%d",&code))!=1||(code<1||code>5))
	{
		if(status!=1) scanf("%*s");
		printf("Enter an integer from 1 to 5, Please.\n");
	}
	return code;
}
int getnights(void)
{
	int nights;
	printf("How many nights are needed? ");
	while(scanf("%d",&nights)!=1)
	{
		scanf("%*s");
		printf("Please enter an integer, such as 2.\n");
	}
	return nights;
}
void showprice(double rate,int nights)
{
	int n;
	double total=0.0;
	double factor=1.0;
	for(n=1;n<=nights;n++,factor*=DISCOUNT) total+=rate*factor;
	printf("The total cost will be $%0.2f.\n",total);
}

#define QUIT 5
#define HOTEL1 180.00
#define HOTEL2 225.00
#define HOTEL3 255.00
#define HOTEL4 355.00
#define DISCOUNT 0.95
#define STARS "************************************"





























