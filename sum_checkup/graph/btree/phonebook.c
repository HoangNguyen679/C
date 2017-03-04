#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#define FILE_NAME "phone_data.csv"

typedef struct phone_address{
  char tel[12];
}contact_data;

char getMenu();
void clear_buffer();
int get_num_of_contact(FILE *);
void read_data(FILE *,BTA *,int);
void showBtfile(BTA *);
void searchBtfile(BTA *);
void addBtfile(BTA *);


int main(int argc, char *argv[]){
  
  /*   ---    Open file   ---    */
  
  FILE *f = fopen(FILE_NAME, "r");
  if (f == NULL) {
    fprintf(stderr,"Can not open %s !\n",FILE_NAME);
    return -1;
  } 

  /*   ---   Read data   ---   */

  btinit();
  BTA *btfile = btcrt("phonebook_db", 0, 0);
  int num_of_contact = get_num_of_contact(f);
  read_data(f, btfile, num_of_contact);
  fclose(f);

  /*   ---   Make choice   ---   */
  char choice;
  while(1) {
    clear_buffer();
    choice = getMenu();

    switch(choice) {
    case '1': showBtfile(btfile); break;
    case '2': searchBtfile(btfile);break;
    case '3': addBtfile(btfile);break;
    case '4': btcls(btfile); return 0;
    default: printf("Invalid!\n");break;
    }
  }
}

char getMenu(){
  char choice;
  printf("---------------------------------------------------------------\n");
  printf("\t.================================.\n");
  printf("\t*    1.Show Phonebook            *\n");
  printf("\t*    2.Search contact            *\n");
  printf("\t*    3.Add new contact           *\n");
  printf("\t*    4.Exit                      *\n");
  printf("\t*================================*\n");	
  printf("\t\tEnter your choice: ");
  choice = getchar();
  printf("---------------------------------------------------------------\n");

  return choice;
  
}

void clear_buffer(){
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}

int get_num_of_contact(FILE *f){
  int counter = 0;
  char line[80];
  while(fgets(line,80,f)) counter++;
  rewind(f);
  return counter;
}

void read_data(FILE *f,BTA *btfile,int num_of_contact){
  int i;
  for(i = 0; i < num_of_contact; i++) {
    contact_data contact;
    char name[30];
    fscanf(f,"%s %s\n",name,contact.tel);
    btins(btfile, name, (char *)&contact,sizeof(contact_data)); //insert a key and data
  }
}

void showBtfile(BTA *btfile){
  btpos(btfile, ZSTART); // set the position of current root ZSTART or ZEND
  printf("%-30s\t%-12s\n\n","NAME","TEL");
  while(1) {
    char name[30];
    contact_data contact;
    int size_receive;
    if(btseln(btfile, name, (char *)&contact,
	      sizeof(contact_data), &size_receive) == QNOKEY)  // locate and return next data in tree
                                                               // if no next function return QNOKEY
      break;
    printf("%-30s\t%-12s\n", name, contact.tel);
  } 
}

void searchBtfile(BTA *btfile){
  clear_buffer();
  char search_name[30];
  contact_data contact;
  int rsize;
  printf("Enter name to search: ");scanf("%[^\n]",search_name);
  if (btsel(btfile, search_name, (char *)&contact,
	    sizeof(contact_data), &rsize) == 0) {
    
    printf("\n\n%-30s\t%-12s\n\n","NAME","TEL");
    printf("%-30s\t%-12s\n", search_name, contact.tel);

  } else printf("\n\nNot found!\n\n");
}

void addBtfile(BTA *btfile) {
  clear_buffer();
  char add_name[30];
  contact_data add_contact;
  int rsize;
  printf("Enter name to add: "); scanf("%[^\n]",add_name);clear_buffer();
  printf("Enter tel: "); scanf("%[^\n]",add_contact.tel);clear_buffer();
  if (btsel(btfile, add_name, (char *)&add_contact,
	    sizeof(contact_data), &rsize) == 0) {
    
    printf("%s is available.\nDo you want to update contact?\n",add_name);
    printf("1.Yes\n2.No\n\nYour choice: ");
    int k; scanf("%d",&k);
    if (k == 1)
      btupd(btfile, add_name, (char *)&add_contact, sizeof(contact_data));
    else if (k == 2);
    else {printf("Invalid!\n");}
    printf("Your update:");
    printf("\n\n%-30s\t%-12s\n\n","NAME","TEL");
    printf("%-30s\t%-12s\n", add_name, add_contact.tel);
  } else
    btins(btfile, add_name, (char *)&add_contact, sizeof(contact_data));
}
