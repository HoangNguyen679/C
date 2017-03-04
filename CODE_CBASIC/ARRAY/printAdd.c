#include<stdio.h>
#include<conio.h>

int main(){
	
	int one[] = {0, 1, 2, 3, 4};
	int i, *ptr = NULL, rows = 5;

	ptr = one;
	for(i = 0 ; i < rows ; i++)
		printf("%8u%5d\n",ptr+i,*(ptr+i));
	printf("\n");
	getch();
}