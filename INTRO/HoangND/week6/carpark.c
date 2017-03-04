/* Nguyen Duc Hoang - 9A */
// Date Create: 23/3.2015
#include<stdio.h>
int main()
{
	char t;
	float f1,f2,h;
	const float c1=0.7,c2=2.5,b1=1.5,b2=2.0,t1=2.5,t2=3.25;
	printf("Enter the type of vehicle: \n");
	printf("(C for Car, B for Bus and T for Truck)\n");
	t=getchar();
	printf("Enter the time: ");
       	scanf("%f",&h);printf("\n\n");
	printf("PARKING FEE\n");
        if (t=='C') { printf("VEHICLE - TYPE: CAR\n");f1=c1;f2=c2; }
	else if (t=='B') { printf("VEHICLE -TYPE: BUS\n");f1=b1;f2=b2; }
	else { printf("VEHICLE -TYPE: TRUCK\n");f1=t1;f2=t2; };
	if (h<=2)
	{
		printf("REGULAR FEE: %g x %g $ = %g $\n",h,f1,h*f1);
		printf("OVERTIME FEE: 0\n\n");
		printf("TOTAL: %g $\n",h*f1);
	}
	else
	{
		printf("REGULAR FEE:%g x %g $ = %g $\n",2.0,f1,2*f1);
		printf("OVERTIME FEE: %g x %g $ = %g $\n\n",h-2.0,f2,(h-2.0)*f2);
		printf("TOATAL: %g $\n",2*f1+(h-2.0)*f2);
	};
	printf("Thank you!\n");
	return 0;


}
