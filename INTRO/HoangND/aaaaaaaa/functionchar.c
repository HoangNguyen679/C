#include<stdio.h>
void printchars(char ch, int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%c",ch);
}

main()
{
	int n,i;
	char ch,c;
	//printf("Nhap ki tu: ");ch=getchar();
	//printf("So lan lap: ");scanf("%d",&n);
	for(i=1;i<6;i++) {
		printchars('*',i);
		printf("\n");
	}
	for (i=1;i<=9;i++)
		{
			
			if (i==5) {
				printchars('*',4);
				printf(" ");
				printchars('*',4);
				printf("\n");
			}
			printchars('*',9);
			printf("\n");

					}
}