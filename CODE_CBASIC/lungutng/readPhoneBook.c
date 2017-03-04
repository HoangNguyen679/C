#include<stdio.h>
typedef struct {
  char name[30];
  char tel[12];
  char email[30];
} address;
typedef struct node{
  address data;
  struct node *next;
} *NODEPTR;
void init(NODEPTR *plist)
{
  *plist=NULL;
}
int emtyList(NODEPTR plist)
{
  return plist==NULL;
}
void addHead(NODEPTR *plist,address a)
{
  NODEPTR p;
  p=(NODEPTR )malloc(sizeof(struct node));
  p->data=a;
  if(emtyList(*plist)==1)
    {
      p->next=NULL;
      *plist=p;
      return;
    }
  p->next=*plist;
  *plist=p;
}
void printList(NODEPTR plist)
{
  NODEPTR p;
  for(p=plist;p!=NULL;p=p->next)
    printf("%-30s%-20s%-15s\n",p->data.name,p->data.tel,p->data.email);
}
void importList(NODEPTR *plist)
{
  FILE *f;
  address b[1];
  if(f=fopen("phonebook.dat","rb"))
    {
      while(feof(f)==0)
	{
	  fread(b,sizeof(address),1,f);
	  addHead(plist,b[0]);
	}
      fclose(f);
    }
  else return;
}
int main(int argv,char* argc[])
{
  NODEPTR plist;
  init(&plist);
  importList(&plist);
  printList(plist);
  return 1;
}
