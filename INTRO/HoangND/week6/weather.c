/* Nguyen Duc Hoang - 9A */
// Date Create: 23/3.2015
#include<stdio.h>
int main()
{
	float tem,hu;
	int r;
	printf("Enter the temperature: ");
	scanf("%f",&tem);
	printf("Enter the humidity: ");
	scanf("%f",&hu);
	printf("It is rainy or not\nIf yes press 1, if no press 0 : ");
	scanf("%d",&r);
	if (tem>35.0 && hu>67) printf("You should rest at home :v\n");
	else if (tem<30 && tem>20 && 32<hu && hu<40 && r==0) printf("You should go out for photography :D\n");
	else printf("Remember to take umbrella or raincoat\n");
	return 0;
}
