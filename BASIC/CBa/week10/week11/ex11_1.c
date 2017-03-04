#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"libTree.h"
char* vong[4]={"Vong loai","Vong tu ket","Vong ban ket","Tran chung ket"};
int dem_v[4];
node *add_t(add data[],int *n,node *tree)
{
  if(tree!=NULL)
    {
      tree->left=add_t(data,n,tree->left);
      tree->right=add_t(data,n,tree->right);
      if(isleaf(tree)==1)
        {tree->data=data[(*n)];(*n)++;}
      else
        {
          if(rand()%2+1==1) tree->data=tree->left->data;
          else tree->data=tree->right->data;
        }
    }
  return tree;
}
void read_t(FILE *f,add data[])
{
  char buff[MAX];
  add tmp;
  int i=0,j;
  while(!feof(f))
    {fscanf(f,"%s",buff);
      if(!feof(f))
        {strcpy(tmp.name,buff);
          data[i]=tmp;i++;}
    }
}
void print(node *tree,int n,FILE *f)
{
  int i;
  if(tree!=NULL)
    {
      print(tree->left,n-1,f);
      for(i=0;i<n;i++) fprintf(f,"%15s"," ");
      fprintf(f,"%s\n",tree->data.name);
      print(tree->right,n-1,f);
    }
}
int main(int argc,char* argv[])
{
  FILE *f,*f2;
  node *tree=NULL;
  int i,n;
  char result[]="treegame.txt";
  add data[20],dat;
  if(argc!=2)
    {printf("Sai loi cu phap: %s <ten file data>\n",argv[0]);}
  else
    if((f=fopen(argv[1],"r"))==NULL)
      {printf("Cant open file %s\n",argv[1]);exit(1);}
    else
      {if((f2=fopen(result,"w"))==NULL)
          {printf("Cant open file %s\n",result);exit(1);}
        else
          {
            read_t(f,data);
            strcpy(dat.name," ");
            tree=makefull(tree,4,dat);
            srand(time(NULL));
            n=0;
            tree=add_t(data,&n,tree);
            print(tree,4,f2);
            fclose(f2);
          }
        fclose(f);
      }
  return 0;
}
