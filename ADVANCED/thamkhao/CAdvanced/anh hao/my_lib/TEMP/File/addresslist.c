#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct Address{
	char name[MAX];
	char number[MAX];
	char email[MAX];
} address;

struct addressList{
	struct addressList *next;
	address addr;
};

struct addressList *root;
struct addressList *cur;

int GetMenu();
int Create();
int showAddress(address);
int Traversing();
int RemoveANode(int );
struct addressList Insert(int );
int RemoveAllNode();
int ReverseList(int );


int main(int argc, char const *argv[]) {
	int i, n, menu;
	char c;
	
	do{
		switch(menu= GetMenu()){
		case 1: //Creating a list
			printf("Number of node in list: "); scanf("%d", &n);
			for(i= 0; i<n; i++)	Create();
			break;
			
		case 2:	//Insert a node
			printf("Insert a node at: "); fflush(stdin); scanf("%d", &n);
			Insert(n);	
			break;
			
		case 3: //Remove a node
			printf("What node do you want to remove? "); fflush(stdin); scanf("%d", &n);
			RemoveANode(n);
			break;
			
		case 4:
			Traversing();	
			break;
			
		case 5: 
			printf("Are you sure? (y/n) "); fflush(stdin); scanf("%c", &c);
			if(c== 'y'){
				RemoveAllNode();
				break;
			}
			else break;
		
		case 6:
			break;	
			
		}
	}
	while(menu!= 0);



	
	return 0;
}


/////Functions/////////////////////////////////////////////////////////////////
int GetMenu(){
	int menu;
	do{
		fflush(stdin); printf("Press Return to continue\n");	char c;	scanf("%c", &c);
		printf("\n     ---Menu---\n");
		printf("1. Create list\n");
		printf("2. Insert a node\n");
		printf("3. Remove a node\n");
		printf("4. Traversing list\n");
		printf("5. Remove all node\n");
		printf("6. Reverse list\n");
		printf("0. Exit\n");
		printf("Your choice: "); fflush(stdin); scanf("%d", &menu);
	}
	while(menu< 0 || menu> 6);
	return menu;
}




int Create() {
	address newAddr;
	printf("Input name: "); fflush(stdin); gets(newAddr.name);
	//printf("Input number: "); fflush(stdin); gets(newAddr.number);
	//printf("Input email: "); fflush(stdin); gets(newAddr.email);
	
	struct addressList *new;
	new = (struct addressList*)malloc(sizeof(struct addressList));
	new->addr = newAddr;
	new->next = NULL;
	
	if ( root == NULL ) { /* if there is no element */
		root = new;
		cur = root;
	} 
	else {
		cur->next = new;
		cur = new;
	}
}

int showAddress(address addr){
	//printf("%s-%s-%s\n", addr.name, addr.number, addr.email);
	printf("%s\n", addr.name);
}

int Traversing(){
	int i;
	printf("**Start list**\n");
	for ( cur = root, i=0; cur != NULL; cur = cur->next, i++ ) {
		printf("No.%-2d-\t", i);
		showAddress(cur->addr);
	}
	printf("**End list**\n");
}

int RemoveANode(int n){
	struct addressList *prev, *del, *temp;
	int i;

	//del= (struct addressList*)malloc(sizeof(struct addressList));
	
	if(n== 0) {
		del= root;
		root= root->next;
		free(del);
	}
	else {
		cur= root;
		for(i=1 ;i< n; i++){
			cur= cur->next;
		}
		prev= cur;
		cur=cur->next;
		prev->next = cur->next;
		free(cur);
	}
}

struct addressList Insert(int n){
	struct addressList *new, *prev;
	new= (struct addressList*)malloc(sizeof(struct addressList));
	address newAddr;
	printf("Input name: "); fflush(stdin); gets(newAddr.name);	
	new->addr= newAddr;
	new->next= NULL;
	
	cur= root;
	int i;
	for (i=1; i< n; i++) cur= cur->next;

	prev= cur;
	cur= cur->next;
	prev->next= new;
	new->next= cur;
}


int RemoveAllNode(){
	struct addressList *toFree;
//	toFree= (struct addressList*)malloc(sizeof(struct addressList));
	toFree= root;
	while(root!= NULL){
		root= root->next;
		free(toFree);
		toFree= root;
	}
}

int ReverseList(int n){
	int i;
	
}