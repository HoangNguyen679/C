#include<stdio.h>
main()
{
	int i=1,j=1,k;
    float sin,n0,n,t;
    const float s=0.0001;
    printf("Nhap n: ");
    scanf("%f",&n);
    sin=t=n;
    do {
        i=i+2;
        j=-j;
        t*=n*n/(i*(i-1));
        sin+=j*t;
		}
	while (t>s);
    printf("sin %g = %g\n",n,sin);
}