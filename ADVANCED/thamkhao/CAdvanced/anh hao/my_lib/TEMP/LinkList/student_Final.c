#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct Student_t {
	char id[MAX];
	char name[MAX];
	int grade;
	struct Student_t *next; 
} Student;

Student *root;
Student *cur;

int GetMenu();
int Insert(Student);
int Traversing();
int Search();
int RemoveAStudent(int n);
int ChangeGrade(char *);

int main(int argc, char **argv){
	
	Student to_Add;
	char id_To_Del[MAX];	
	int i, n, menu;
	char c;
	char idToChange[MAX];
	
	FILE *fout;
	if((fout= fopen("save.dat", "r+b"))== NULL) perror("ERROR: ");
	do{	
		switch(menu= GetMenu()){
		case 1: //Insert a student
			printf("#Insert Student:\n"); //Get Data to Insert
			printf("ID: "); fflush(stdin); gets(to_Add.id);
			do {
				printf("Grade (0<=grade<=10): "); fflush(stdin); scanf("%d", &to_Add.grade);
			}	while (to_Add.grade>10 || to_Add.grade<0);
			
			 //Inserting
			if(Insert(to_Add)){
				printf("%d\n", fwrite(&to_Add, sizeof(to_Add), 1*sizeof(to_Add), fout));
				printf("Insert successful!\n");
			}
			else printf("ID existed. Insert another ID\n");
			break;
			
		case 2:	//Traversing list	
			Traversing();
			break;
			
		case 3: //Remove a student

			printf("Enter student ID: "); fflush(stdin); gets(id_To_Del);
			if(RemoveAStudent(id_To_Del))	printf("Remove successful!\n");
			else printf("Not match any ID\n");
			break;
		
		case 4: //Search a Student
			Search();
			break;
			
		case 5:
			printf("Input ID: "); fflush(stdin); gets(idToChange);
			ChangeGrade(idToChange);
			break;
			
		case 6:

			break;
		}
	}
	while(menu!= 0);
	fclose(fout);
}

/////Functions/////////////////////////////////////////////////////////////////
int GetMenu(){
	int menu;
	do{
		fflush(stdin); printf("Press Return to continue\n");	char c;	scanf("%c", &c);
		printf("\n     ---Menu---\n");
		printf("1. Insert a student\n");
		printf("2. Traversing list\n");
		printf("3. Remove a node\n");
		printf("4. Search a student\n");
		printf("5. Change Grade\n");
		printf("6. Save to Disk\n");
		printf("0. Exit\n");
		printf("Your choice: "); fflush(stdin); scanf("%d", &menu); printf("\n");
	}
	while(menu< 0 || menu> 6);
	return menu;
}


int Insert(Student to_Add){
	Student *toAdd;
	toAdd= (Student*)malloc(sizeof(Student));
	*toAdd= to_Add;
	
	//Check if there exist ID
	for(cur= root; cur!= NULL; cur= cur->next){
		if(strcmp(toAdd->id, cur->id)== 0) {
			return 0;
		}
	}
	
	if(root== NULL) { 
		root= toAdd;
		root->next= NULL;
	}else if(toAdd->grade > root->grade) {
		toAdd->next= root;
		root= toAdd;
	}else {
		Student *currStd, *preStd;
		currStd= root;
		while(currStd!= NULL && toAdd->grade < currStd->grade){
			preStd= currStd;
			currStd= currStd->next;
		}
		preStd->next= toAdd;
		toAdd->next= currStd;
	}
	return 1;
}


int Traversing(){
	int i;
	printf("**Start list**\n");
	for ( cur = root, i=1; cur != NULL; cur = cur->next, i++ ) {
		printf("No.%-2d-\t", i);
		printf("%s- %d\n", cur->id, cur->grade);
	}
	printf("**End list**\n");
}


int Search(){
	char idSearch[MAX];
	printf("#Search Student\nType ID: "); fflush(stdin); gets(idSearch);
	
	for(cur = root; cur!= NULL; cur= cur->next){
		if(strcmp(idSearch, cur->id)== 0) {
			printf("%d\n", cur);
			return 1;
		}
	}
	
	printf("Not match\n"); 
	return 0;
}

int RemoveAStudent(int idDel){
	Student *prev, *del;
	
	
	for(cur= root; cur!= NULL; cur= cur->next){
		if(strcmp(idDel, cur->id)== 0) {
			
			if(cur== root){//if del is root
				del= root;
				root= root->next;	
			}else{
				//move pre to position before cur
				prev= root;
				while(prev->next!= cur) prev= prev->next;

				prev->next = cur->next;	
				free(cur);		
			}
		return 1; //remove successful	
		}//end if
	}//end for
	return 0;
}


int ChangeGrade(char *idToChange){
	Student toChange;
	int newGrade;
	for(cur= root; cur!= NULL; cur= cur->next){
		if(strcmp(idToChange, cur->id)== 0) {
			printf("New Grade: "); fflush(stdin); scanf("%d", &newGrade);
			strcpy(toChange.id, idToChange);
			toChange.grade= newGrade;
			RemoveAStudent(toChange.id);
			Insert(toChange);
			return 1;
		}
	}
	printf("Not match any ID\n");
	return 0;
}
