#include<stdio.h>
main()
{
	int a,b,c;
	for(a=1;a<20;a++)
		for(b=1;b<((100-5*a)/3);b++)
			for(c=3;c<100;c=c+3)
				if ((a+b+c==100)&&(15*a+9*b+c==300)) printf("Trau lon: %d\tTrau be: %d\tTrau gia: %d\n",a,b,c);
			
}