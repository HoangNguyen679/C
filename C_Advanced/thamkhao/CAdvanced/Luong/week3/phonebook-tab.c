#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "luong.h"

typedef struct{
  void *key;
  void *value;
}Entry;

#define BOOK_LENGTH 1000
#define EXIT '4'
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct{
  Entry *entries;
  int current, total;
  Entry (*makeNode)(void *, void *);
  int (*compare)(void *, void *);
} SymbolTable;


SymbolTable createSymbolTable(
			      Entry (*makeNode)(void *, void *),
			      int (*compare)(void *, void *)
			      )
{
  SymbolTable stb;
  stb.current = 0;
  stb.total = INITIAL_SIZE;
  stb.entries = (Entry*) malloc(sizeof(Entry)*INITIAL_SIZE);
  stb.makeNode = makeNode;
  stb.compare = compare;
  return stb;
}


Entry makePhoneBook(void* phone, void* name)
{
  Entry res;
  res.key = malloc(sizeof(int));
  memcpy( res.key, phone, sizeof(int) );
  res.value = strdup( (char*)name );
  return res;
}


int comparePhone(void * key1, void* key2) {
  int num1 = *( (int*) key1 );
  int num2 = *( (int*) key2 );
  if (num1==num2) return 0;
  else if (num1 < num2) return -1;
  else return 1;
}


int getEntryValue(void* key, const SymbolTable *book)
{
  int i;
  int current = book->current;
  Entry *p = book->entries;
  int cmp;

  for(i = 0; i < current; i++){
    cmp = (*(book->compare))(key, p[i].key);
    if(cmp == 0) return i;
  }

  return -1;

}


void extendBook(SymbolTable *stb)
{
  Entry *p = stb->entries;
  int original_size = stb->total;
  
  p = (Entry *) realloc(p, (original_size+INCREMENTAL_SIZE)*sizeof(Entry));
  
  if(p == NULL){
    printf("Fail to allocate memory\n");
    exit(1);
  }else{
    stb->total += INCREMENTAL_SIZE;
  }

}


void dropSymbolTable(SymbolTable *stb)
{
  free(stb->entries);
}


int isFull(SymbolTable *stb)
{
  return(stb->current == stb->total);
}


void addEntry(void *key, void *value, SymbolTable *book)
{
  Entry tmp;
  Entry *p = book->entries;
  int current = book->current;
  int exist;

  /* search for the existing entry */
  exist = getEntryValue(key, book);
  if(exist == -1){
    /* if not exist */
    if(isFull(book)){
      /* if the book is full */
      /* increase the size of the book */
      extendBook(book);
      p[current] = (*(book->makeNode))(key, value);
      book->current++;
    }else{
      p[current] = (*(book->makeNode))(key, value);
      book->current += 1;
    }    

  }else{
    /* if exist, overwrite the existing one */
    book->entries[exist] = (*(book->makeNode))(key, value);
  }
  
}


char getMenu()
{
  char choice;
  printf("+===============================================+\n");
  printf("| 1. Add new phone entry                        |\n");
  printf("| 2. Search for a number                        |\n");
  printf("| 3. List all the contacts                      |\n");
  printf("| 4. Exit                                       |\n");
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

void displayEntry(Entry e)
{
  int key =  *((int *)(e.key));
  printf("%-30s%-15d\n", (char *)(e.value), key);
}

int main()
{
  char choice;
  char name[80];
  int number;
  int found;
  SymbolTable book;
  int i;
  /* initialize phone book */
  book = createSymbolTable(&makePhoneBook, &comparePhone);

  do{
    choice = getMenu();
    switch(choice){

    case '1':
      printf("Enter the name: ");
      scanf("%[^\n]", name);
      myfflush();
      printf("Enter the number: ");
      scanf("%d", &number);
      myfflush();
      addEntry(&number, &name, &book);
      printf("%d\n", book.total);
      break;

    case '2':
      printf("Enter the number you want to find: ");
      scanf("%d", &number);
      myfflush();
      found = getEntryValue(&number, &book);
      if(found == -1) printf("Not found\n");
      else{
	displayTitle();
	displayEntry(book.entries[found]);
      }      
      break;

    case '3':
      displayTitle();
      for(i = 0; i < book.current; i++){
	displayEntry(book.entries[i]);
      }
      break;

    case '4':
      dropSymbolTable(&book);
      break;
      
    default: printf("Invalid choice\n");
    }
  }while(choice != EXIT);
}
