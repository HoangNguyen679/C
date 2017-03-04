#include<stdio.h>
#include"tree_str.h"
void menu()
{
  printf("\n\nMENU\n\n");
  printf("1. Doc file\n");
  printf("2. Hien thi\n");
  printf("3. Dich\n");
  printf("4. Cap nhat va thoat\n");
  printf("\nPlease select: ");
}
void docfile(FILE *f, node **tree )
{
  infodict a;
  while(!feof(f))
    {
      fscanf(f,"%s\t%[^\n]\n",a.tu,a.nghia);
      *tree=insert(*tree,a);
    }
}
char *chuanhoa(char str[])
{
  int i=0;
  while(str[i] != '\0')
    {if(str[i] >= 65 && str[i] <=90) str[i] +=32; i++;}
  return str;
}
void dich(node **tree)
{
  char str[2*MAX];
  char cau[2*MAX];cau[0]='\0';
  printf("Nhap vao cau can dich : ");scanf("%[^\n]",str);
  chuanhoa(str);
  char *pch;
  infodict b,c;
  int k1;
  node *tmp;
  pch=strtok(str," ");
  while(pch != NULL)
    {
      // printf("%s\n",pch);
      strcpy(b.tu,pch);
      if((tmp=search(*tree,b)) == NULL)
        {
          printf("\n\nThieu tu %s\n",b.tu);
          printf("\nBan muon bo sung tu moi khong ?\n");
          printf("1. Co tui mun lem :3\n");
          printf("2. Deo :v\n");
          printf("Chon di bo: ");scanf("%d",&k1);getchar();
          if(k1==1)
            {
              do
                {
                  printf("\n\nThem tu\n\n");
                  printf("Nhap tu can them: ");scanf("%s",c.tu);getchar();
                }
              while(strcmp(c.tu,b.tu) != 0);
              printf("Nhap nghia cua tu: ");scanf("%[^\n]",c.nghia);
              *tree=insert(*tree,c);
              strcat(cau,c.nghia);
              strcat(cau," ");}
          else return;
        }
      else
        {
          // printf("%s\n",tmp->data.nghia);
          strcat(cau,tmp->data.nghia);
          strcat(cau," ");
        }
      pch=strtok(NULL," ");
    }
  printf("\n\nCau da dich la: %s",cau);
}
void ghifile(FILE *f,node *tree)
{
  if(tree != NULL)
    {
      ghifile(f,tree->left);
      fprintf(f,"%s\t%s\n",tree->data.tu,tree->data.nghia);
      ghifile(f,tree->right);
    }
 }
int main()
{
  int k;
  node *tree=NULL;
  FILE *f;
  char file[]="data.txt";
  if((f=fopen(file,"r+")) == NULL){printf("\n\nLoi mo file\n\n");return;}
  do
    {
      menu();scanf("%d",&k);getchar();
      switch(k)
        {
        case 1:docfile(f,&tree);break;
        case 2:printf("\n\n");inorder(tree);break;
        case 3:dich(&tree);break;
        case 4:rewind(f);ghifile(f,tree);return 0;
        default: printf("\n\nChon sai roi mo :v\n\n");
        }
    }
  while(1);
}
