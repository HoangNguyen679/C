/* fox */
// Date Create: 1/4/16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

#define FILE_NAME "phone_data.txt"

typedef struct phone_address{
  char name[30];
  char tel[12];
}Contact;

char getMenu();
void clear_buffer();
int get_num_of_contact(FILE *);
void read_data(FILE *,Contact*,int);

int main(int argc,char *argv[])
{

  // Open file -------------------------------------------------------
  FILE *f = fopen(FILE_NAME, "r");
  if (f == NULL)
    {
      fprintf(stderr,"Can not open %s !\n",FILE_NAME);
      return 1;
    }
  int num_of_contact = get_num_of_contact(f);
  Contact * contact = (Contact*)malloc(sizeof(Contact) *num_of_contact);
  if(contact == NULL)
    {
      fprintf(stderr, " Malloc failed in %s:%d!!\n",__FILE__,__LINE__);
      return 1;
    }

  // Read from file and add to jrb------------------------------------
  read_data(f,contact,num_of_contact);
  printf("Reading data completed...\n");

  JRB t = make_jrb();
  if (t == NULL)
    {
      fprintf(stderr, "NULL value error in %s:%d\n",__FILE__,__LINE__);
      return 1;
    }
  
  int i;
  for(i = 0; i < num_of_contact; i++)
    {
      jrb_insert_str(t,contact[i].name,
		     new_jval_v(contact[i].tel));
    }
  char choice;

  while(1)
    {
      clear_buffer();
      choice = getMenu();

      switch(choice)
	{
	case '1': // show contact
	  {
	    JRB temp;
	    jrb_traverse(temp,t)
	      printf("%-30s\t%s\n",temp->key.s,temp->val.s);
	  }
	  break;
	case '2': //search contact
	  {
	    char name_to_search[30];
	    clear_buffer();
	    printf("Enter name: ");
	    scanf("%[^\n]",name_to_search);
	    JRB result = jrb_find_str(t, name_to_search);
	    if(result == NULL)
	      printf("Can not find \"%s\"!\n", name_to_search);
	    else
	      printf("%s - %s\n",result->key.s,result->val.s);
	  }
	  break;
	case '3': //add new contact
	    {
	      char newname[30];
	      char newnumber[12];

	      clear_buffer();
	      printf("Enter new name: ");
	      scanf("%[^\n]",newname);

	      
	      clear_buffer();
	      printf("Enter new number: ");
	      scanf("%[^\n]",newnumber);

	      jrb_insert_str(t,newname,new_jval_v(newnumber));

	      printf("Adding completed!\n");
	      
	    }
	    break;
	    case '4'://exit
	      {
		jrb_free_tree(t);
		free(contact);
		fclose(f);
		return 0;
	      }
	default:
	  {
	    printf("Invalid!\n");
	    break;
	  }
	}
    }
}

char getMenu()
{
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

void clear_buffer()
{
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}

int get_num_of_contact(FILE *f)
{
  int counter = 0;
  char line[80];
  while(fgets(line,80,f)) counter++;
  rewind(f);
  return counter;
}

void read_data(FILE *f,Contact *contact,int num_of_contact)
{
  int i;
  for(i = 0; i < num_of_contact; i++)
    {
      fscanf(f,"%s %s\n",
	     contact[i].name,contact[i].tel);
    }
}
