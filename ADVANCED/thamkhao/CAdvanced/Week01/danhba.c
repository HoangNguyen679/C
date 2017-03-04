#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 40

struct Contact {
	char name[MAX];
	char phone[MAX];
	char email[MAX];
};

void showList(Contact*, int);
int getNumOfContact(FILE*);
void readDataFrom(FILE*, Contact*, int);
char getMenu();
void clear_buffer();
void gen_qsort(
	void* buf,
	int num,
	int size,
	int (*cmp_fn)(void const*, void const*)
);
int name_cmp(void const*, void const*);
int phone_cmp(void const*, void const*);
int email_cmp(void const*, void const*);

int main(int argc, char const *argv[])
{
	//-- Open file ---------------------------------------
	char file_name[] = "danhba.txt";
	FILE* data_file = fopen(file_name, "r");
	if (data_file == NULL) {
		printf("Cannot open file %s!\n", file_name);
	}

	char choice;
	int numOfContact = getNumOfContact(data_file);
	Contact* contact = (Contact*)malloc(sizeof(Contact) * numOfContact);

	readDataFrom(data_file, contact, numOfContact);
	printf("Reading data completed...\n\n");
	//showList(contact, numOfContact);

	while (1)
	{
		clear_buffer();
		choice = getMenu();

		switch (choice)
		{
		case '1':// sort by name
		{
			gen_qsort(contact, numOfContact, sizeof(Contact), name_cmp);
			showList(contact, numOfContact);
			break;
		}
		case '2':// sort by phone
		{
			gen_qsort(contact, numOfContact, sizeof(Contact), phone_cmp);
			showList(contact, numOfContact);
			break;
		}
		case '3':// sort by email
		{
			gen_qsort(contact, numOfContact, sizeof(Contact), email_cmp);
			showList(contact, numOfContact);
			break;
		}
		case '4'://exit
		{
			free(contact);
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
}

void showList(Contact* contact, int numOfContact) {
	int i;
	for (i = 0; i < numOfContact; i++)
		printf("%s\t%s\t%s\n",
		       contact[i].name,
		       contact[i].phone,
		       contact[i].email);
	printf("\n");
}

int getNumOfContact(FILE* data_file) {
	int counter = 0;
	char line[100];
	while (fgets(line, 100, data_file))
		counter++;
	rewind(data_file);
	return counter;
}

void readDataFrom(FILE* data_file, Contact* contact, int numOfContact) {
	int i;
	for (i = 0; i < numOfContact; i++) {
		fscanf(data_file, "%s %s %s\n",
		       contact[i].name,
		       contact[i].phone,
		       contact[i].email);
	}
	rewind(data_file);
}

char getMenu()
{
	char choice;

	printf("---------------------------------------------------------------\n");
	printf("\t.================================.\n");
	printf("\t*    1.Sort by name              *\n");
	printf("\t*    2.Sort by phone number      *\n");
	printf("\t*    3.Sort by email             *\n");
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

void gen_qsort(
	void* buf,
	int num,
	int size,
	int (*cmp_fn)(void const*, void const*))
{
	char *_buf = (char*)buf;
	int L, R, mid;
	int i;

	while(num > 1){
		L = 0;
		R = num-1;
		mid = (L + R)/2;

		while(1){
			while(cmp_fn(&_buf[size*mid], &_buf[size*L])>0){
				L++;
			}
			while(cmp_fn(&_buf[size*mid], &_buf[size*R])<0)
				R--;
			if(L >= R) break;
			for(i = 0; i < size; i++){
				char tmp = _buf[size*L+i];
				_buf[size*L+i] = _buf[size*R+i];
				_buf[size*R+i] = tmp;
			}
			if(mid == L) mid = R;
			else if(mid == R) mid = L;
			L++;
			R--;
		}
		R++;
		if(R < num-R){
			qsort(_buf, R, size, cmp_fn);
			_buf = &_buf[size*R];
			num = num - R;
		}
		else{
			qsort(&_buf[size*R], num-R, size, cmp_fn);
			num = R;
		}
	}
}

int name_cmp(void const* contact_1, void const* contact_2){
	Contact first_contact = *((Contact*)contact_1);
	Contact second_contact = *((Contact*)contact_2);

	if(!strcmp(first_contact.name, second_contact.name)) return 0;
	else if(strcmp(first_contact.name, second_contact.name) < 0) return -1;
	else return 1;
}

int phone_cmp(void const* contact_1, void const* contact_2){
	Contact first_contact = *((Contact*)contact_1);
	Contact second_contact = *((Contact*)contact_2);

	if(!strcmp(first_contact.phone, second_contact.phone)) return 0;
	else if(strcmp(first_contact.phone, second_contact.phone) < 0) return -1;
	else return 1;
}

int email_cmp(void const* contact_1, void const* contact_2){
	Contact first_contact = *((Contact*)contact_1);
	Contact second_contact = *((Contact*)contact_2);

	if(!strcmp(first_contact.email, second_contact.email)) return 0;
	else if(strcmp(first_contact.email, second_contact.email) < 0) return -1;
	else return 1;
}