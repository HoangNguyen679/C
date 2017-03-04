#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "luong.h"

typedef struct{
  char number[12];
  char name[80];
}PhoneEntry;

#define BOOK_LENGTH 1000
#define EXIT '3'

typedef struct{
  PhoneEntry entries[BOOK_LENGTH];
  int total;
} PhoneBook;

int getPhoneNumber(char *number, PhoneBook *book)
{
  PhoneEntry *p = book->entries;
  int len = book->total;
  int i;

  for(i = 0; i < len; i++){
    if(strcmp(number, p[i].number) == 0) return i;
  }

  return -1;
}

PhoneEntry createEntry(char *number, char *name)
{
  PhoneEntry tmp;
  strcpy(tmp.number, number);
  strcpy(tmp.name, name);
  return tmp;
}

void addPhoneNumber(char *number, char *name, PhoneBook *book)
{
  PhoneEntry tmp;
  int total = book->total;
  PhoneEntry *p = book->entries;
  int exist;
  if(total == 0){
    tmp = createEntry(number, name);
    p[0] = tmp;
    book->total += 1;
  }else{
    /* search for the existing entry */
    exist = getPhoneNumber(number, book);
    if(exist == -1){
      /* if not exist */
      p[total] = createEntry(number, name);
      book->total += 1;
    }else{
      /* if exist, overwrite the existing one */
      book->entries[exist] = createEntry(number, name);
    }
  }
}

char getMenu()
{
  char choice;
  printf("+===============================================+\n");
  printf("| 1. Add new phone entry                        |\n");
  printf("| 2. Search for a number                        |\n");
  printf("| 3. Exit                                       |\n");
  printf("+===============================================+\n");
  printf("Your choice: ");
  scanf("%c", &choice);
  myfflush();
  return choice;
}

void displayTitle()
{
  printf("%-30s%-15s\n", "Name", "Number");
}

void displayEntry(PhoneEntry e)
{
  printf("%-30s%-15s\n", e.name, e.number);
}

int main()
{
  char choice;
  char name[80];
  char number[12];
  int found;
  PhoneBook book;
  /* initialize phone book */
  book.total = 0;

  do{
    choice = getMenu();
    switch(choice){
    case '1':
      printf("Enter the name: ");
      scanf("%[^\n]", name);
      myfflush();
      printf("Enter the number: ");
      scanf("%[^\n]", number);
      myfflush();
      addPhoneNumber(number, name, &book);
      printf("%d\n", book.total);
      break;

    case '2':
      printf("Enter the number you want to find: ");
      scanf("%[^\n]", number);
      myfflush();
      found = getPhoneNumber(number, &book);
      if(found == -1) printf("Not found\n");
      else{
	displayTitle();
	displayEntry(book.entries[found]);
      }      
      break;

    case '3':
      break;
      
    default: printf("Invalid choice\n");
    }
  }while(choice != EXIT);
}
