#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ARRSIZE     10
#define RANGE       26
#define EPSILON     1E-7
#define MAX_BUFF    512

#define INITIAL_SIZE         5
#define INCREMENTAL_SIZE     5
#define BUFF_SIZE            80

#define NEWLINE     printf("%s", "\n");

#include "btree.h"

#define TEMPFILE "phonedata"


void AddPhoneNumber(BTA *book, char *name, char* number);
char *GetPhoneNumer(BTA *book, char *name);
void SearchPhoneNumer(BTA *book, char *name);
void DeletePhoneNumber(BTA *book, char *name);
void print_bterror(void);

BTA *phoneBook;

int main(int argc, char const *argv[])
{

	btinit();
	if ((phoneBook = (BTA*)btopn(TEMPFILE, 0, TRUE)) != NULL)
	{
		btdups(phoneBook, FALSE);
	}
	else if ((phoneBook = (BTA*)btcrt(TEMPFILE, 0, TRUE)) != NULL)
	{
		btdups(phoneBook, FALSE);
		AddPhoneNumber(phoneBook, "Demo", "123456");
	}
	else
	{
		printf("%s\n", "Unable to open temp btree index.\n");
		return 1;
	}

	AddPhoneNumber(phoneBook, "Demo", "123456");

	SearchPhoneNumer(phoneBook, "Demo");

	DeletePhoneNumber(phoneBook, "Demo");
	btcls(phoneBook);


	return 0;
}

//---------------------------------------------------------
void AddPhoneNumber(BTA *book, char *name, char* number)
{
	if (btins(book, name, number, strlen(number)) != 0)
	{
		print_bterror();
	}
	else
	{
		printf("%s\n", "Added!");
	}
}
//---------------------------------------------------------
char *GetPhoneNumer(BTA *book, char *name)
{
	char *s = (char*)malloc(sizeof(char)*BUFF_SIZE);
	int tmp;
	int re = btsel(book, name, s, BUFF_SIZE, &tmp);
	if (re != 0)
	{
		strcpy(s, "NULL");
	}
	return s;
}
//---------------------------------------------------------
void SearchPhoneNumer(BTA *book, char *name)
{
	char *strRe;
	strRe = GetPhoneNumer(book, name);
	if (strcmp(strRe, "NULL") == 0)
	{
		print_bterror();
	}
	else
	{
		printf("Result: %s\n", strRe);
	}
	free(strRe);
}
//---------------------------------------------------------
void DeletePhoneNumber(BTA *book, char *name)
{
	if (btdel(book, name) != 0)
	{
		print_bterror();
	}
	else
	{
		printf("%s", "Deleted!\n");
	}
}
//---------------------------------------------------------
void print_bterror(void)
{
    int errorcode, ioerr;
    char fname[ZRNAMESZ],msg[ZMSGSZ];

    btcerr(&errorcode,&ioerr,fname,msg);
    fprintf(stderr,"PhoneBook: error (%d) [%s] - %s\n",
            errorcode,fname,msg);
}