#ifndef	_UTIL_H_
#define	_UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

enum bool {false, true};
typedef int bool;

int GetMenu(void);

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
char* IntToChar(int num)
{
	int nDigits;
	if (num == 0) nDigits = 1;
	else nDigits = floor(log10(abs(num))) + 1;
	char *t = (char*)malloc(nDigits);
	sprintf(t, "%d", num);
	//itoa(num);
	//char c_i = (char)(((int)'0')+i);
	return t;
}
//---------------------------------------------------------
int CharToInt(const char *num)
{
	return atoi(num);
}
//---------------------------------------------------------
int GetMenu(void)
{
	int menuOption = 0;
	do 
	{
		printf("\n\n---SORT MENU---\n");
		printf("1. Doc va in ma tran\n");
		printf("2. Thong tin ma tran\n");
		printf("3. Tim diem lien thong\n");
		printf("4. Danh sach cac nut co lien thong lon nhat\n");
		printf("5. Danh sach nut dao\n");
		printf("6. Duong di ngan nhat\n");
		printf("7. Tong so cach di giua 2 diem\n");
		printf("0. Exit\n");
		printf("Your Choice: ");
		scanf("%d", &menuOption);
	} while(menuOption < 0 || menuOption > 7);
	return menuOption;
}
#endif