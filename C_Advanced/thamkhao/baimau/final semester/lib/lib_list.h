#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"element.h"
typedef struct node
{elementtype data;struct node *next;}node;
//==========================================================
void inp(elementtype *data);
void update(node *root,char str[]);
void free_n(node *root);
node *search(node *root,int n);
node *insert(node *root,elementtype data,int n);
node *creat(char str[]);
node *del(node *root,int n);
node *change(node *root,int n);
node *re(node *root);
//==========================================================
//search ===================================================
node *search(node *root,int n)
{
  node *tmp;
  int i=0;
  for(tmp=root;tmp!=NULL;tmp=tmp->next) {i++;if(i==n) break;}
  return tmp;
}
//insert ===================================================
node *insert(node *root,elementtype data,int n)
{
  node *new,*cur,*tmp;
  new=(node *)malloc(sizeof(node));
  new->data=data;new->next=NULL;
  if(root==NULL) root=new;
  else
    if(n==0) {new->next=root;root=new;}
    else
      {
        cur=search(root,n);
        if(cur==NULL)
          {for(tmp=root;tmp->next!=NULL;tmp=tmp->next);
            tmp->next=new;}
        else
          {new->next=cur->next;cur->next=new;}
      }
  return(root);
}
// creat ===================================================
node *creat(char str[])
{
  node *new,*root=NULL;
  FILE *f;
  elementtype *data;
  if((f=fopen(str,"rb"))==NULL)
    {printf("Cant open file %s\n",str);return NULL;}
  else
    {
      data=(elementtype *)malloc(sizeof(elementtype));
      while(!feof(f))
        {
          fread(data,sizeof(elementtype),1,f);
          if(!feof(f))
            root=insert(root,*data,0);
        }
      fclose(f);
      return(root);
    }
}
//Delete ===================================================
node *del(node *root,int n)
{
  node *tmp=NULL,*cur=NULL;
  if((cur=search(root,n))==NULL) {printf("Cant find data\n");}
  else
    if(n==1) {tmp=root;root=root->next;free(tmp);}
    else
      {cur=search(root,n-1); tmp=cur->next;cur->next=tmp->next;free(tmp);}
  return root;
}
//free =====================================================
void free_n(node *root)
{
  node *to_free;
  to_free=(node*)malloc(sizeof(node));
  to_free=root;
  while(to_free!=NULL)
    {root=root->next;free(to_free);to_free=root;}
}
//change ===================================================
node *change(node *root,int n)
{
  node *cur;
  elementtype data;
  cur=search(root,n);
  if(cur!=NULL)
    {
      printf("Enter new data:");
      inp(&data);
      cur->data=data;
    }
  else
    printf("Cant find data\n");
  return root;
}
//update ===================================================
void update(node *root,char str[])
{
  node *tmp;
  FILE *f;
  elementtype data;
  if((f=fopen(str,"wb"))==NULL)
    {printf("Cant open file\n");}
  else
    {
      for(tmp=root;tmp!=NULL;tmp=tmp->next)
        {
          data=tmp->data;
          fwrite(&data,sizeof(elementtype),1,f);
        }
    }
}
//Re =======================================================
node *re(node *root)
{
  node *cur,*tmp=NULL,*new=NULL;
  for(cur=root;cur!=NULL;cur=cur->next)
    {if(new==NULL) new=cur;
      else {new->next=tmp;tmp=new;new=cur;}
    }
  new->next=tmp;
  return new;
}
