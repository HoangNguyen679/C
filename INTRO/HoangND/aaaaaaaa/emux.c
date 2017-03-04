#include<stdio.h>
int main()
{
	float e=1,x,y=1;
    int i=1;
    const float s=0.0001;
    printf("Enter x: ");
    scanf("%f",&x);
    do {
    	y*=x/i;
    	e=e+y;
    	i++;
       }
    while (y>s);
    printf("e^%g = %g\n",x,e);
    return 0;
}