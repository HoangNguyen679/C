/* Nguyen Duc Hoang - 9A */
// Date Create:
#include<stdio.h>
#include<string.h>
#define 
void clear_buffer() {
	int ch;
	while ((ch=getchar()) != '\n' && ch != EOF);
}
main() {
	int chon;
	int i,j;
	do {
		printf("MENU\n");
		printf("1.\n");
		printf("2.\n");
		printf("3.\n");
		printf("4.\n");
		printf("5.\n");
		do {
			printf("Nhap lua chon: ");
			scanf("%d",&chon);
			if (chon < 1 || chon >5) printf("Nhap lai!\n");
		} while (chon < 1 || chon >5);
		switch(chon){
		case 1: {}break;
		case 2: {}break;
		case 3: {}break;
		case 4: {}break;
		}
		if (chon == 5) break;
	} while (1);
}
