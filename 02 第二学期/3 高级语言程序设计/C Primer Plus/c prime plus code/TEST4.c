#include <stdio.h>
double round1(double a)
{
	return round(a*10)/10;
}
int main(void)
{
	struct c{
		double a;
		double b;
	}c1,c2;
	scanf("%lf %lf %lf %lf",&c1.a,&c1.b,&c2.a,&c2.b);  //¼Ó ¼õ ³Ë ³ý add,subtract,multiply,divide; 
	double aa,ab,sa,sb,ma,mb,da,db;
	
	aa=c1.a+c2.a;
    ab=c1.b+c2.b;
	if(round1(aa)==0&&round1(ab)!=0) printf("(%.1f%+.1fi) + (%.1f%+.1fi) = %.1fi\n",c1.a,c1.b,c2.a,c2.b,ab);
	else if(round1(ab)==0) printf("(%.1f%+.1fi) + (%.1f%+.1fi) = %.1f\n",c1.a,c1.b,c2.a,c2.b,aa);
	else printf("(%.1f%+.1fi) + (%.1f%+.1fi) = %.1f%+.1fi\n",c1.a,c1.b,c2.a,c2.b,aa,ab);
	
	sa=c1.a-c2.a;
	sb=c1.b-c2.b;
	if(round1(sa)==0&&round1(sb)!=0) printf("(%.1f%+.1fi) - (%.1f%+.1fi) = %.1fi\n",c1.a,c1.b,c2.a,c2.b,sb);
	else if(round1(sb)==0) printf("(%.1f%+.1fi) - (%.1f%+.1fi) = %.1f\n",c1.a,c1.b,c2.a,c2.b,sa);
	else printf("(%.1f%+.1fi) - (%.1f%+.1fi) = %.1f%+.1fi\n",c1.a,c1.b,c2.a,c2.b,sa,sb);
	
	ma=c1.a*c2.a-c1.b*c2.b;
	mb=c1.a*c2.b+c1.b*c2.a;
	if(round1(ma)==0&&round1(mb)!=0) printf("(%.1f%+.1fi) * (%.1f%+.1fi) = %.1fi\n",c1.a,c1.b,c2.a,c2.b,mb);
	else if(round1(mb)==0) printf("(%.1f%+.1fi) * (%.1f%+.1fi) = %.1f\n",c1.a,c1.b,c2.a,c2.b,ma);
	else printf("(%.1f%+.1fi) * (%.1f%+.1fi) = %.1f%+.1fi\n",c1.a,c1.b,c2.a,c2.b,ma,mb);
	
	if((c2.a*c2.a+c2.b*c2.b)==0) da=db=0;
	else
	{
        da=(c1.a*c2.a+c1.b*c2.b)/(c2.a*c2.a+c2.b*c2.b);
	    db=(c2.a*c1.b-c1.a*c2.b)/(c2.a*c2.a+c2.b*c2.b);
	}
	//printf("%.1f\n",db);
	if(round1(da)==0&&round1(db)!=0) printf("(%.1f%+.1fi) / (%.1f%+.1fi) = %.1fi\n",c1.a,c1.b,c2.a,c2.b,db);
	else if(round1(db)==0) printf("(%.1f%+.1fi) / (%.1f%+.1fi) = %.1f\n",c1.a,c1.b,c2.a,c2.b,da);
	else printf("(%.1f%+.1fi) / (%.1f%+.1fi) = %.1f%+.1fi\n",c1.a,c1.b,c2.a,c2.b,da,db);
}
