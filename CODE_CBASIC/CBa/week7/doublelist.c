#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
  char model[25];
  char rom[3];
  char screen[5];
  char price[8];
}info;

typedef info elementtype;
typedef struct node node;

typedef struct node
{
  elementtype data;
  node* next;
  node* prev;
} node;

node *makenewnode(elementtype data)
{
  node* new;
  new= (node *) malloc( sizeof(node));
  new->data=data;
  new->next=NULL;
  new->prev=NULL;
  return new;
}

void insertAtBegin(elementtype data,node** root,node** tail,node **cur)
{
  node* new;
  new=makenewnode(data);
  if(*root==NULL)
    {
      *root=new;
      *tail=new;
    }
  else
    {
      new->next=*root;
      (*root)->prev=new;
      *root =new;
    }
  *cur=*root;
}
void insertAtLast(elementtype data,node** root,node** tail,node** cur)
{
  node* new;
  new=makenewnode(data);
  if(*tail==NULL)
    {

      *root=new;
      *tail=new;
    }
  else
    {
      (*tail)->next=new;
      new->prev=*tail;
      *tail =new;
    }
  *cur=*root;
}
void insertAfterCurrent(elementtype data,node **root,node **tail,node **cur)
{
  node *new;
  new=makenewnode(data);
  new->prev=*cur;
  if((*cur)->next!=NULL)
    new->next=(*cur)->next;
  else *tail=new;
  (*cur)->next=new;
  *cur=new;
}
void insertBeforeCurrent(elementtype data,node **root,node **tail,node **cur)
{
  node *new;
  new=makenewnode(data);
  new->next=*cur;
  if(*cur!=*root)
    new->prev=(*cur)->prev;
  else
    *root=new;
  (*cur)->prev=new;
  *cur=new;
}
void free_1st_node(node** root)
{
  node* to_free;
  to_free=*root;
  *root=(*root)->next;
  free(to_free);
}
void free_current_node(node **root,node **tail,node **cur)
{
  node *new_cur;
  if(*cur==*root)
    {
      *root=(*root)->next;
      new_cur=*root;
    }
  else if(*cur==*tail)
    {
      *tail=(*tail)->prev;
      new_cur=*tail;
    }
  else
    {
      (*cur)->prev->next=(*cur)->next;
      (*cur)->next->prev=(*cur)->prev;
      new_cur=(*cur)->next;
    }
  free(*cur);
  *cur=new_cur;
}
void free_all(node *root)
{
  node *del;
  while(root!=NULL)
    {
      del=root;
      root=root->next;
      free(del);
    }
}
/*
node *find_node_by_name(char *s,node *root)
{
  node *a;
  node *p;
  for(a=root;a!=NULL;a=a->next)
    {
      if(!strcmp((a->data).name,s))
	{
	  p=a;
	  break;
	}
    }
  return p;
}
*/
void set_current_from_root(int n,node* root, node** cur)
{
  int i=0;
  *cur=root;
  for(i=1;i<n;i++)

    *cur=(*cur)->next;

}


/*
elementtype insert_data(elementtype data)
{
  printf("Name: ");scanf("%s",data.name);getchar();
  printf("Tel: "); scanf("%s",data.tel);getchar();
  printf("Email: "); scanf("%s",data.email); getchar();
  return data;
}
*/
void displaynode(node* p)
{
 elementtype  tmp=p->data;
 printf("%-10s\t%-6s\t%-20s\t%-10s\n",tmp.model,tmp.rom,tmp.screen,tmp.price);
}
void traversinglist(node* root)
{
  node* p;
  for(p=root;p!=NULL;p=p->next)
    {
      displaynode(p);

    }
}
int main()
{
  node *root1=NULL;
  node *tail1=NULL;
  node *cur1;
  int a;
  int n,i;
  char s[20];
  node *p;
  elementtype data;
  FILE *fp;
  fp=fopen("sony.dat","r+b");
  info data1[20];
  int j;
  i=fread(data1,sizeof(info),20,fp);

  printf("%d\n",j);


  while(a!=9)
{
  printf("MENU NODE\n");
  printf("1.insert at the begin\n");
  printf("2.insert at the end\n");
  printf("3.insert after current\n");
  printf("4.insert before current\n");
  printf("5.delete 1st node\n");
  printf("6.delete current node\n");
  printf("7.delete all node\n");
  printf("8.search node by name\n");
  printf("8.change tel by name in menu 7\n");
  printf("9.quit\n");
  scanf("%d",&a);
  switch(a)
    {
        case 1:
          j=i;
          while(j>0)
        {

          insertAtBegin(data1[j-1],&root1,&tail1,&cur1);
	  j--;

        }
      traversinglist(root1);




      break;


    case 2:
      j=i;
      while(j>0)
        {

          insertAtLast(data1[j-1],&root1,&tail1,&cur1);
	  j--;

        }
      traversinglist(root1);
      break;
    case 3:
      j=i;
      while(j>0)
        {

          insertAfterCurrent(data1[j-1],&root1,&tail1,&cur1);
	  j--;

        }
      traversinglist(root1);
      break;

        case 4:
          j=i;
       while(j>0)
        {

          insertBeforeCurrent(data1[j-1],&root1,&tail1,&cur1);
	  j--;

        }
      traversinglist(root1);
      break;

    case 5:
      free_1st_node(&root1);
      traversinglist(root1);
      break;
    case 6:
      free_current_node(&root1,&tail1,&cur1);
      traversinglist(root1);
      break;
    case 7:
      free_all(root1);
      break;

      /*
        case 8:
      printf("search name: \n");scanf("%s",s);
      p=find_node_by_name(s,root1);
      displaynode(p);
      break;

    case 8:
      printf("new tel: \n"); scanf("%s",s);
      strcpy((p->element).tel,s);
      displayNode(p);
      break; */
    case 9: break;
    default: printf("no choice here !\n"); break;

    }
 }

}
