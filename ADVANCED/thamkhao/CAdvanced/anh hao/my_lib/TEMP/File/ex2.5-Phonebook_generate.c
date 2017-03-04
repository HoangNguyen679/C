#include <stdio.h>
#include <string.h>
#define MAX 20

typedef struct phoneBook{
	char name[MAX];
	char number[MAX];
	char email[MAX];
} contact;

contact myContact[100];


contact inputContact(contact *);

int main(){
	int i, n=6;
	strcpy(myContact[0].name,"Mother"); strcpy(myContact[0].number,"01234718934"); strcpy(myContact[0].email,"mother@gmail.com");
	strcpy(myContact[1].name,"Father"); strcpy(myContact[1].number,"7982153483"); strcpy(myContact[1].email,"father@gmail.com");
	strcpy(myContact[2].name,"Brother"); strcpy(myContact[2].number,"1837423489"); strcpy(myContact[2].email, "brother@gmail.com");
	strcpy(myContact[3].name,"Sister"); strcpy(myContact[3].number,"2341231235"); strcpy(myContact[3].email,"sister@gmail.com");
	strcpy(myContact[4].name,"Uncle"); strcpy(myContact[4].number,"4863582394"); strcpy(myContact[4].email,"uncle@gmail.com");
	strcpy(myContact[5].name,"Aunt"); strcpy(myContact[5].number,"0983427734"); strcpy(myContact[5].email,"aunt@gmail.com");
	
	
	/*printf("Number of contacts: ");
	int n;
	scanf("%d",&n);
	
	int i;
	for (i=0; i< n; i++){
		printf("Contact #%d: \n", i+1);
		inputContact(&myContact[i]);
	}
*/
	FILE *fileout;
	if((fileout= fopen("contact.txt", "w"))== NULL) perror("ERROR");
	else fwrite(myContact, sizeof(contact), n, fileout);
	fclose(fileout);
	
	fileout=(fopen("contact.txt", "r"));
	int freadnum=	fread(myContact, sizeof(contact), n, fileout);
	printf("fread return: %d, size of contact: %d\n", freadnum, sizeof(contact));
	
	for(i=0; i<n; i++){
		printf("Contact #%d: %-17s%-17s%-17s\n", i+1, myContact[i].name, myContact[i].number, myContact[i].email);
	}
	fclose(fileout);
	
	return 0;
}


//FUNCTIONS HERE

contact inputContact(contact *newContact){
	printf("Input name: ");
	fflush(stdin);
	gets(newContact->name);
	printf("Input phone number: ");
	fflush(stdin);
	gets(newContact->number);
	printf("Input email address: ");
	fflush(stdin);
	gets(newContact->email);
}
