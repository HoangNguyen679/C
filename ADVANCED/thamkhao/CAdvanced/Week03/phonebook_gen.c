#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gensymboltable.h"

Entry* makeNewContact(void*, void*);
int cmpName(void*, void*);

char getMenu();
void clear_buffer();
void readDataFrom(FILE*, SymbolTable*);
void showPhoneBook(SymbolTable*);

int main(int argc, char const *argv[])
{
	FILE* data_file = fopen(argv[1], "r");
	if (data_file == NULL) {
		printf("Cannot open file %s!\n", argv[1]);
		return 0;
	}

	char choice;
	SymbolTable* phoneBook = creatSymbolTable(makeNewContact, cmpName);
	readDataFrom(data_file, phoneBook);

	while (1)
	{
		clear_buffer();
		choice = getMenu();

		switch (choice)
		{
		case '1'://show phonebook
		{
			showPhoneBook(phoneBook);

			break;
		}
		case '2':// add new contact
		{
			char new_name[30];
			long new_number;
			int result_index;
			int foo;

			printf("Enter name: ");
			scanf("%s", new_name);

			result_index = searchEntry((void*)new_name, phoneBook);
			if (result_index == -1) {// contact hasn't existed
				printf("Enter number: ");
				scanf("%ld", &new_number);
				addEntry((void*)new_name, (void*)&new_number, phoneBook);
				printf("Adding completed!\n");
			}
			else {// contact already existed
				printf("\"%s\" has existed. Do you want to overwrite? (1.Yes, 0.No): ", new_name);
				scanf("%d", &foo);
				if (foo) {
					printf("Enter number: ");
					scanf("%ld", &new_number);
					*(long*)phoneBook->entries[result_index].value = new_number;
					printf("Finish overwriting!\n");
				}
			}

			break;
		}
		case '3':// search contact
		{
			char name_to_search[30];
			Entry* p_found_contact;

			printf("Enter name to search: ");
			scanf("%s", name_to_search);
			p_found_contact = getEntry(name_to_search, phoneBook);
			if(p_found_contact == NULL)// not found
				printf("Cannot find \"%s\" in the phonebook!\n", name_to_search);
			else// found
				printf("Name: %s\t\tNumber: (+84)%ld\n", 
					(char*)p_found_contact->key,
					*(long*)p_found_contact->value);

			break;
		}
		case '4':// exit
		{
			dropSymbolTable(phoneBook);
			fclose(data_file);
			return 0;
			break;
		}
		default:
		{
			printf("Invalid!\n");
			break;
		}
		}
	}

	return 0;
}

char getMenu()
{
	char choice;

	printf("---------------------------------------------------------------\n");
	printf("\t.================================.\n");
	printf("\t*    1.Show phonebook            *\n");
	printf("\t*    2.Add new contact           *\n");
	printf("\t*    3.Search contact            *\n");
	printf("\t*    4.Exit                      *\n");
	printf("\t*================================*\n");

	printf("\t\tEnter your choice: ");
	choice = getchar();
	printf("---------------------------------------------------------------\n");

	return choice;
}

void clear_buffer ()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

void readDataFrom(FILE* data_file, SymbolTable* phoneBook) {
	char new_name[30];
	long new_number;
	while (!feof(data_file)) {
		fscanf(data_file, "%s %ld", new_name, &new_number);
		addEntry((void*)new_name, (void*)&new_number, phoneBook);
	}
	printf("Reading data completed!\n");
}

void showPhoneBook(SymbolTable* phoneBook) {
	int i;
	printf("%9s%28s\n\n", "Name", "Phone number");
	for (i = 0; i < phoneBook->total; i++) {
		printf("%s\t\t(+84)%ld\n",
		       (char*)phoneBook->entries[i].key,
		       *(long*)phoneBook->entries[i].value);
	}
}

Entry* makeNewContact(void* name, void* number) {
	Entry* new_contact = (Entry*)malloc(sizeof(Entry));
	new_contact->key = strdup((char*)name);
	new_contact->value = malloc(sizeof(long));
	memcpy(new_contact->value, number, sizeof(long));
	return new_contact;
}

int cmpName(void* first_cont, void* second_cont) {
	return strcmp((char*)first_cont, (char*)second_cont);
}
