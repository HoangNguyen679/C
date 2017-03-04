/* Nguyen Duc Hoang - 9A */
// Date Create: 15/3/2015
#include<stdio.h>
int main()
{
	int a,b,t,d;
	printf("So luong IPOD muon mua? ");
	scanf("%d",&a);
	printf("So luong Ipad muon mua? ");
	scanf("%d",&b);
	t=148*a+288*b;
	printf("Sieu thi TOPCARE - Hoa do thanh toan \n");
	printf("Ipod \t %d x 148 = %d\n",a,a*148);
	printf("Ipad \t %d x 288 = %d\n",b,b*288);
	printf("Net  \t            %d\n",t);
	((a>=3&&b>=2)||t>1020) ? (printf("Discount %d x 10%% = %d\n",t,d=t/10)) : (printf("Discout\t %d\n",d=0));
	printf("You pay: %d - %d = %d\n",t,d,t-d);
	return 0;
}
