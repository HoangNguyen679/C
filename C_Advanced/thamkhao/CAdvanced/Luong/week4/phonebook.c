#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "jval.h"
#include "jrb.h"
#include "luong.h"

#define EXIT '5'
#define DISPLAYTITLE {printf("%-30s%-15s\n", "Name", "Number");}

char getMenu()
{
  char choice;
  printf("+===============================================+\n");
  printf("| 1. Load phonebook                             |\n");
  printf("| 2. Insert new contact                         |\n");
  printf("| 3. Delete a contact                           |\n");
  printf("| 4. Modify a phone number                      |\n");
  printf("| 5. Exit                                       |\n");
  printf("+===============================================+\n");
  printf("Your choice: ");
  scanf("%c", &choice);
  myfflush();
  return choice;
}


void insertNewNode(JRB book, char *key, char *name)
{
  char *skey = (char *) malloc(sizeof(strlen(key)));
  char *sname = (char *) malloc(sizeof(strlen(name)));
  strcpy(skey, key);
  strcpy(sname, name);
  Jval jname = new_jval_s(sname);

  jrb_insert_str(book, skey, jname);
  
}


int loadData(JRB b, char *fileName)
{
  FILE *f;
  int i;
  char buffer[500];
  char tokens[2][200];
  char *sname;
  char *skey;
  Jval name;
  /* count the number of lines in the file */
  int nline = countLine(fileName);

  f = fopen(fileName, "r");
  for(i = 0; i < nline; i++){
    fgets(buffer, 500, f);
    getTokens(buffer, tokens, '-');
    insertNewNode(b, tokens[1], tokens[0]);
  }
  
  fclose(f);
  
  return nline;
}


void displayTitle()
{
  printf("%-30s%-15s\n", "Name", "Number");
}

/*
void displayEntry(JRB node)
{
  printf("%-30s%-15s\n", jval_s((node)->val), jval_s((node)->key));
}
*/

void traverseBook(JRB book)
{
  
  JRB tmp;
  displayTitle();
  jrb_traverse(tmp, book){
    char *name = jval_s(tmp->val);
    char *key = jval_s(tmp->key);
    printf("%-30s%-15s\n", name, key);
  }

}


int main()
{
  char choice;
  char name[100];
  char number[12];
  char fileName[50];
  JRB result;
  int len;
  JRB book = make_jrb();
  
  do{
    choice = getMenu();

    switch(choice){
    case '1':
      printf("Enter file name: ");
      scanf("%[^\n]", fileName);
      myfflush();
      len = loadData(book, fileName);
      traverseBook(book);
      break;

    case '2':
      printf("Enter name: ");
      scanf("%[^\n]", name);
      myfflush();
      printf("Enter number: ");
      scanf("%[^\n]", number);
      myfflush();
      insertNewNode(book, number, name);
      traverseBook(book);
      break;

    case '3':
      printf("Enter the number you want to delete: ");
      scanf("%s", number);
      printf("%s\n", number);
      myfflush();
      result = jrb_find_str(book, number);
      if(result == NULL){
	printf("The number you enter does not exist\n");
      }else{
	jrb_delete_node(result);
      }
      traverseBook(book);
      break;

    case '4':
      printf("Enter the number you want to modify: ");
      scanf("%s", number);
      myfflush();
      result = jrb_find_str(book, number);
      if(result == NULL){
	printf("The number you enter does not exist\n");
      }else{
	printf("OK\n");
	printf("Enter new name:");
	scanf("%[^\n]", name);
	myfflush();
	printf("Enter new number: ");
	scanf("%[^\n]", number);
	myfflush();
	jrb_delete_node(result);
	insertNewNode(book, number, name);
	traverseBook(book);
      }
      break;

    case '5':
      jrb_free_tree(book);
      break;
    }

  }while(choice != EXIT);
}
