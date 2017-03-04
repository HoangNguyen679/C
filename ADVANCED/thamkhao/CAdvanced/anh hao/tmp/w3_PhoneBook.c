#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define INITIAL_SIZE 		5
#define INCREMENTAL_SIZE 	5
#define BUFF_SIZE			80

typedef struct 
{
	char 		name[BUFF_SIZE];
	long 		number;
} PhoneEntry;

typedef struct
{
	PhoneEntry 	*entries;
	int 		total;
	int 		size;
} PhoneBook;

PhoneBook CreatePhoneBook(int size)
{
	PhoneBook newBook;
	newBook.total = 0;
	newBook.size  = size;
	newBook.entries = (PhoneEntry*)malloc(sizeof(PhoneEntry)*size);
	return newBook;
}

void DropPhoneBook(PhoneBook *book)
{
	free(book->entries);
	book->entries = NULL;
	book->size = 0;
	book->total = 0;
}

int BinarySearchPhoneEntry(PhoneBook book, int l, int r, char *name, int *found)
{
	if (l > r) {*found = 0; return l;}
	int m = (l + r) / 2;
	if (strcmp(book.entries[m].name,name) > 0) return BinarySearchPhoneEntry(book, l, m-1, name, found);
	if (strcmp(book.entries[m].name,name) < 0) return BinarySearchPhoneEntry(book, m+1, r, name, found);
	if (strcmp(book.entries[m].name,name) == 0) {*found = 1; return m;}
}

void AddPhoneNumber(PhoneBook *book, char *name, long number)
{
	// If number of entries is larger than size, 
	// create new phone book with larger memory then
	// copy old data to new phonebook and free old phonebook
	if (book->total >= book->size)
	{
		PhoneBook newBook = CreatePhoneBook(book->size + INCREMENTAL_SIZE);
		newBook.size = book->size + INCREMENTAL_SIZE;
		newBook.total = book->total;
		memcpy(newBook.entries, book->entries, sizeof(PhoneEntry)*book->total);
		DropPhoneBook(book);
		*book = newBook;
	}
  
	if (book->total == 0)
	{
		strcpy(book->entries[0].name, name);
		book->entries[0].number = number;
		book->total++;
		return;
	}
	//
	int found;
	int pos = BinarySearchPhoneEntry(*book, 0, book->total, name, &found);
	
	// If there already exists an entry, just update it.
	if (found == 1)	
		book->entries[pos].number = number;
	else // insert new entry to phonebook
	{
		book->total++;
		// move data for one element then insert to this position
		PhoneEntry *temp = (PhoneEntry*)malloc(sizeof(PhoneEntry)*book->total);
		memcpy(temp, (book->entries)+pos, sizeof(PhoneEntry)*(book->total-1-pos));
		strcpy(book->entries[pos].name, name);
		book->entries[pos].number = number;
		memcpy((book->entries)+pos+1, temp, sizeof(PhoneEntry)*(book->total-1-pos));
		free(temp); temp = NULL;
	}
}

PhoneEntry *GetPhoneNumber(PhoneBook book, char *name)
{
	int found;
	int pos = BinarySearchPhoneEntry(book, 0, book.total, name, &found);

	if (found == 0) return NULL;
	else return (book.entries)+pos;
}

void ShowPhoneEntry(PhoneEntry entry)
{
	printf("%-15s : %d\n", entry.name, entry.number);
}

void ShowPhoneBook(PhoneBook book)
{
	int i;
	for (i = 0; i < book.total; i++)
	{
		ShowPhoneEntry(book.entries[i]);
	}
}



int main(int argc, char const *argv[])
{
	PhoneBook myContact = CreatePhoneBook(INITIAL_SIZE);
	AddPhoneNumber(&myContact, "f", 6);
	AddPhoneNumber(&myContact, "a", 1);
	AddPhoneNumber(&myContact, "e", 5);
	AddPhoneNumber(&myContact, "c", 3);
	AddPhoneNumber(&myContact, "d", 4);
	AddPhoneNumber(&myContact, "b", 2);

	ShowPhoneBook(myContact);

	PhoneEntry *testgetphonenumber = GetPhoneNumber(myContact, "ca");
	if (testgetphonenumber == NULL) printf("Not found!\n");
	else ShowPhoneEntry(*testgetphonenumber);

	DropPhoneBook(&myContact);
	return 0;
}

