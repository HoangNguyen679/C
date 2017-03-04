#include<stdio.h>
#include<stdlib.h>
#include"tree_str.h"

void menu()
{
  printf("\n\nMENU\n\n");
  printf("1. Doc file A\n");
  printf("2. Doc file B\n");
  printf("3. Tim kiem\n");
  printf("4. Tong hop\n");
  printf("5. Thong ke\n");
  printf("6. Thoat\n\n");
  printf("Nhap lua chon: ");
}

void docfileA(node **tree,FILE *f1,char file1[])
{
  if((f1=fopen(file1,"r+")) == NULL)
    {printf("Loi mo file\n");return ;}
  infodochoi a;
  while(!feof(f1))
    {
      fscanf(f1,"%d",&a.maso);
      fgetc(f1);
      fscanf(f1,"%[^\n]\n",a.dochoi);
      if(strcmp(a.dochoi,"")==0)
        {
          printf("\nNhap thong tin do choi cua ma so %d: ",a.maso);
          scanf("%[^\n]",a.dochoi);
        }
      *tree=insert(*tree,a);
      strcpy(a.dochoi,"");
      a.maso=-1;
    }
  inorder(*tree);
}


void in(node *root)
{
  if(root != NULL)
    {
      in(root->right);
      printf("%4d\t%-30s\n",root->data.maso,root->data.dochoi);
      in(root->left);
    }
}


int main()
{
  int k;int soluong=0;
   int i=0,j;
  FILE *f1,*f2;
  char file1[]="A.txt";
  char file2[]="B.txt";
  node *tree=NULL;
  node *tmp=NULL;
  infodochoi mang[100];
  do
    {
      menu(); scanf("%d",&k);getchar();
      switch(k)
        {
        case 1:docfileA(&tree,f1,file1);break;
        case 2:
          {

            if((f2=fopen(file2,"r+")) == NULL)
              {printf("Loi mo file\n");return ;}
            while(!feof(f2))
              {
                fscanf(f2,"%d\t%[^\n]\n",&mang[i].maso,mang[i].dochoi);
                if(strcmp(mang[i].dochoi,"")==0)
                  {
                    printf("\nNhap thong tin do choi cua ma so %d: ",mang[i].maso);
                    scanf("%[^\n]",&mang[i].dochoi);
        }
                i++;
              }
            for(j=0;j<i;j++)
              printf("%4d\t%-30s\n",mang[j].maso,mang[j].dochoi);
          }
          break;
        case 3:
          {
            for(j=0;j<i;j++)
              {
                if((tmp=search(tree,mang[j])) != NULL)
                  {
                    printf("Thong tin bi lap\n");
                    printf("%4d\t%-30s\n",mang[j].maso,mang[j].dochoi);
                    tree=delete(tree,mang[j]);
                  }
              }
            printf("\nCay sau khi xoa thong tin lap:\n");
            inorder(tree);
          }
          break;
        case 4:
          {
            for(j=0;j<i;j++)
              tree=insert(tree,mang[j]);
            in(tree);
          }
          break;
        case 5:
          {

          }
          break;
        case 6: return 0;
        default: printf("\nNhap sai lua chon\n");
        }
    }
  while(1);
}
