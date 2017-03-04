#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
void menu()
{
  printf("\n\nMENU\n\n");
  printf("1. Tim kiem\n");
  printf("2. Them tu\n");
  printf("3. Xoa tu\n");
  printf("4. Ghi ra file\n");
  printf("5. Thoat\n");
  printf("Please select: ");
}
void docfile(FILE *f,node **tree)
{
  int i,num=0;
  word *a;
  char str[MAX];
  while(fgets(str,MAX,f) != NULL) num++;
  rewind(f);
  a=(word *)malloc(num*sizeof(word));
  for(i=0;i<num;i++)
    {
      fscanf(f,"%s%s",a[i].tu,a[i].nghia);
     *tree = insert(*tree,a[i]);
    }
}
void timkiem(node *tree)
{
  char s[MAX];
  word x;
  node *tmp=NULL;
  printf("\nChu y: tu can tim kiem khong co dau cach, neu tu ghep thi dung dau _ de noi\n\n");
  printf("Nhap tu can tim kiem: ");scanf("%s",s);
  strcpy(x.tu,s);
  tmp = search(tree,x);
  if(tmp == NULL)printf("\nTu ban vua tim khong co trong tu dien\n\n");
  else
    {
      printf("\n%15s\t%15s\n\n","TU","NGHIA");
      printf("%15s\t%15s\n\n",tmp->data.tu,tmp->data.nghia);
    }
}
void themtu(node **tree)
{
  word x;
  printf("\nChu y: tu khong co dau cach, neu tu ghep thi dung dau _ de noi\n\n");
  printf("Tu ban muon them la: ");scanf("%s",x.tu);
  printf("Nghia cua tu do la: ");scanf("%s",x.nghia);
  *tree = insert(*tree,x);
}
void xoatu(node **tree)
{
  word x;
  printf("\nChu y: tu khong co dau cach, neu tu ghep thi dung dau _ de noi\n\n");
  printf("Tu ban muon xoa la: ");scanf("%s",x.tu);
  delete(*tree,x);
}
void ghifile(FILE *f_ghi,node *tree)
{
  if(tree != NULL)
    {
      fwrite(&tree->data,sizeof(word),1,f_ghi);
      ghifile(f_ghi,tree->left);
      ghifile(f_ghi,tree->right);
    }
}
int main()
{
  FILE *f,*f_ghi;
  char filename[]="dict.txt";
  char file_ghi[]="dulieura.dat";
  int i,k;
  node * tree=NULL;
  if((f=fopen(filename,"r")) == NULL)
    {printf("Loi mo file : %s",filename);return 1;}
  if((f_ghi=fopen(file_ghi,"wb")) == NULL)
    {printf("Loi mo file : %s",file_ghi);return 1;}
  docfile(f,&tree);
  do
    {
      menu();
      scanf("%d",&k);getchar();
      switch(k)
        {
        case 1:
          timkiem(tree);break;
        case 2:
          themtu(&tree);break;
        case 3:
          xoatu(&tree);break;
        case 4:
          printf("Du lieu se duoc ghi ra file %s\n",file_ghi);
          ghifile(f_ghi,tree);break;
        case 5: fclose(f);fclose(f_ghi);return 0;
        default: printf("Wrong choice\n");
        }
    }
  while(1);
}
