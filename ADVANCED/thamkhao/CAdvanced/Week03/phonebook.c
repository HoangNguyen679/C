#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct PhoneEntry{
  long number;
  char name[80];
} PhoneEntry;

typedef struct PhoneBook{
  PhoneEntry* entries;
  int total;
  int size;
} PhoneBook;

PhoneBook* createPhoneBook();
void addPhoneNumber(long, char*, PhoneBook*);
int searchEntry(long, const PhoneBook*);
void dropPhoneBook(PhoneBook*);

void showPhoneBook(PhoneBook*);

int main(){
  PhoneBook* book = createPhoneBook();
  int const n = 3;

  int i;
  long new_number;
  char new_name[30];
  for(i = 0; i < n; i++){
    printf("Entry %d:\n", i+1);
    printf("Enter name: ");
    scanf("%s",new_name);
    printf("Enter number: ");
    scanf("%ld", &new_number);
    addPhoneNumber(new_number, new_name, book);
  }
  printf("Finish!\n");

  showPhoneBook(book);

  dropPhoneBook(book);
  return 0;
}

PhoneBook* createPhoneBook(){
  PhoneBook* book = (PhoneBook*)malloc(sizeof(PhoneBook));
  book->total = 0;
  book->size = INITIAL_SIZE;
  book->entries = (PhoneEntry*)malloc(book->size*sizeof(PhoneEntry));

  return book;
}

void addPhoneNumber(long number, char* name, PhoneBook* book){
  int tmp = searchEntry(number, book);
  if(tmp == -1){//entry not exists yet
    PhoneEntry* new_entry = (PhoneEntry*)malloc(sizeof(PhoneEntry));
    new_entry->number = number;
    strcpy(new_entry->name, name);
    book->total++;

    if(book->total > book->size){//when exceed the maximum size 
      size += INCREMENTAL_SIZE;
      book->entries = (PhoneEntry*)realloc(book->entries, size*sizeof(PhoneEntry));
    }
    book->entries[(book->total-1)*sizeof(PhoneEntry)] = *new_entry;
  }
  else{//entry already existed
    book->entries[tmp*sizeof(PhoneEntry)].number = number;
    strcpy(book->entries[tmp*sizeof(PhoneEntry)].name, name);
  }
}

int searchEntry(long number, const PhoneBook* book){
  int i;
  for(i = 0; i < book->total; i++){
    if(book->entries[i*sizeof(PhoneEntry)].number == number) 
      return i;
  }
  return -1;
}

void dropPhoneBook(PhoneBook* book){
  free(book->entries);
  book->total = 0;
  book->size = 0;
  free(book);
}

void showPhoneBook(PhoneBook* book){
  int i;
  for(i = 0; i < book->total; i++){
    printf("%s\t%ld\n",
	   book->entries[i*sizeof(PhoneEntry)].name,
	   book->entries[i*sizeof(PhoneEntry)].number);
  }
}
