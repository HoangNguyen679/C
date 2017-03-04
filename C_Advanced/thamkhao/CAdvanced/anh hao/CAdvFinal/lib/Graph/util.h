#ifndef	_UTIL_H_
#define	_UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#define NEWLINE 	printf("%s", "\n");

#define EPSILON 	1E-5

#ifndef BUFF_SIZE
#define BUFF_SIZE	80
#endif


enum bool {false, true};
typedef int bool;

//---------------------------------------------------------
int 	GetMenu(void);
void 	ClrBuf(void);
char* 	IntToChar(int num);
int 	CharToInt(const char *num);

int 	CompareDouble(double d1, double d2);

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
	return menuOption;
}
//---------------------------------------------------------
void ClrBuf(void) 
{
	while(getchar() != '\n');
}


int CompareDouble(double d1, double d2)
{
	if (fabs(d1-d2) < EPSILON)
		return 0;
	if (d1 < d2)
		return -1;
	else return 1;
}
#endif