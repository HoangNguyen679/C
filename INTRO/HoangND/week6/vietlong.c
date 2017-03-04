/* Nguyen Duc Hoang - 9A */
// Date Create: 23/3.2015
#include<stdio.h>
int main()
{
	const int fri=8,tele=15,lap=12;
	int a,b,c;
	printf("Enter the amount of Fridge Electrolux: ");
	scanf("%d",&a);
	printf("Enter the amount of Laptop HP: ");
	scanf("%d",&c);
	printf("Enter the amount of LCD Sony Television: ");
	scanf("%d",&b);
	printf("The sales of Fridge Electrolux (trieu VND): %d x %d = %d\n",a,fri,a*fri);
	printf("The sales of LCD Sony Television (trieu VND): %d x %d = %d\n",b,tele,b*tele);
	printf("The sales of Laptop HP (trieu VND): %d x %d = %d\n",c,lap,c*lap);
	printf("The total sales (trieu VND): %d + %d + %d = %d\n",a*fri,b*tele,c*lap,a*fri+b*tele+c*lap);
	if (a>b && a>c) printf("The fastest good is Fridge Electrolux\n");
	else if (b>a && b>c) printf("The fastest good is LCD Sony Television\n");
	else printf("The fastest good is Laptop HP\n");
	if (a*fri>b*tele && a*fri>c*lap) printf("The most sale good is Fridge Electrolux\n");
	else if (b*tele>a*fri && b*tele>c*lap) printf("The most sale good is LCD Sony Television\n");
	else printf("The most sale good is Laptop HP\n");
	return 0;


}
