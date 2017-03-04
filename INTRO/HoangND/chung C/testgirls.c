/* Nguyen Duc Hoang - 9A */
// Date Create: 15/3/2015
#include<stdio.h>
int main()
{
	int h0,a0,h1,a1,h2,a2,ta1,ta2,th1,th2,t1,t2;
	char n0[20],n1[20],n2[20];
	printf("Enter your name: ");
	gets(n0);
	printf("Enter your age: ");
	scanf("%d",&a0);
	printf("Enter your height: ");
	scanf("%d",&h0);
	printf("\n\n");
	printf("Enter your first's girl's name: ");
	getchar();
	gets(n1);
	printf("Hi %s\n",n1);
	printf("How old are you :");
	scanf("%d",&a1);
	(a1<=16)?(ta1=0):((16<a1 && a1<21)?(ta1=5):(ta1=2));
	printf("What's your height:");
	scanf("%d",&h1);
	(h1>=h0)?(th1=-1):((h1<(h0-30))?(th1=-2):(th1=3));
	printf("\n\n");
	printf("Enter your second girl's name: ");
	getchar();
	gets(n2);
	printf("Hi %s\n",n2);
	printf("How old are you :");
	scanf("%d",&a2);
	(a2<=26)?(ta2=0):((26<a2 && a2<22)?(ta2=5):(ta2=2));
	printf("What's your height:");
	scanf("%d",&h2);
	(h2>=h0)?(th2=-2):((h2<(h0-30))?(th2=-2):(th2=3));
	t1=ta1+th1;t2=ta2+th2;
	printf("My decision: \n")
	(t1=t2)?(printf("%s free on saturday?\n%s free on sunday?\n",n1,n2)):
		((t1>t2)?(printf("%s free on saturday?\n",n1)):
		 (printf("%s free on saturday?\n",n2)));
	return 0;
}
