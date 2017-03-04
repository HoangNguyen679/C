#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"tree.h"
void menu()
{
  printf("MENU\n\n");
  printf("1. Doc file\n");
  printf("2. Duyet theo thu tu giua\n");
  printf("3. Duyet theo thu tu truoc\n");
  printf("4. Duyet theo thu tu sau\n");
  printf("5. Duyet theo chieu rong\n");
  printf("6. Ghi ra file\n");
  printf("7. Thoat\n");
  printf("Please select: ");
}
void docfile(FILE *f,node** tree)
{
  char *str;
  int i;
  str = (char *)malloc(20*sizeof(char));
  elementtype x;
  while(!feof(f))
    {
      fscanf(f,"%s",str);
      for(i=0; i< strlen(str); i++)
        {
          if(isupper(str[i])) str[i]=tolower(str[i]);
          if(str[i] >122 || str[i] <97)
            if(str[i+1] = '\0')
              str[i]='\0';
        }
      strcpy(x.word,str);
      x.count =1;
      *tree=insert(*tree,x);
    }
}
void ghifile(FILE *f_ghi,node *tree)
{
  if(tree != NULL)
    {
      fwrite(&tree->data,sizeof(elementtype),1,f_ghi);
      ghifile(f_ghi,tree->left);
      ghifile(f_ghi,tree->right);
    }
}
int main(int argc,char *argv[])
{
  if(argc != 2)
    {printf("Wrong argument\n");return 1;}
  FILE *f,*f_ghi;
  char file[MAX],file_ghi[]="dulieura.dat";
  strcpy(file,argv[1]);
  int k;
  node *tree = NULL;
  if((f=fopen(file,"r")) == NULL)
    {printf("Cannot open %s\n",file);return -1;}
  if((f_ghi=fopen(file_ghi,"wb")) == NULL)
    {printf("Cannot open %s\n",file_ghi);return -1;}
  do
    {
      menu();
      scanf("%d",&k);getchar();
      switch(k)
        {
        case 1:
          docfile(f,&tree);break;
        case 2:
          inorder(tree);break;
        case 3:
          preorder(tree);break;
        case 4:
          postorder(tree);break;
        case 5:
          breath_order(tree);break;
        case 6:
          printf("Du lieu se duoc ghi vao file %s\n",file_ghi);
          ghifile(f_ghi,tree);break;
        case 7: return 0;
        default: printf("Wrong choice\n");
        }
    }
  while(1);
  fclose(f);
  return 0;
}
