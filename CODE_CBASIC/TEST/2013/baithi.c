#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"
void menu()
{
  printf("\n\nMENU\n\n");
  printf("1. Tao cay\n");
  printf("2. Ket qua\n");
  printf("3. Tim kiem\n");
  printf("4. Xuong hang\n");
  printf("5. Xuat file\n");
  printf("6. Thoat\n");
  printf("Please select: ");
}
void docfile(FILE *f, node **tree)
{
  soccer_data temp1,temp2;
  node *tmp1,*tmp2;
  int diem1,diem2;
  int i=0;
  while(!feof(f))
    {
      fscanf(f,"%s\t%s\t%d\t%d\n",temp1.ma,temp2.ma,&diem1,&diem2);
      if((tmp1=search(*tree,temp1)) == NULL)
        {
          if(diem1>diem2) temp1.diem=3;
          else if(diem1<diem2) temp1.diem=0;
          else temp1.diem =1;
          *tree=insert(*tree,temp1);
            printf("%13s\t%3d\n",temp1.ma,temp1.diem);
        }
      else
        {
          if(diem1>diem2) tmp1->data.diem+=3;
          else if(diem1==diem2) tmp1->data.diem+=1;
        }
      if((tmp2=search(*tree,temp2)) == NULL)
        {
          if(diem1>diem2) temp2.diem=0;
          else if(diem1<diem2) temp2.diem=3;
          else temp2.diem =1;
          *tree=insert(*tree,temp2);
            printf("%13s\t%3d\n",temp2.ma,temp2.diem);
        }
     else
        {
          if(diem1<diem2) tmp2->data.diem+=3;
          else if(diem1==diem2) tmp2->data.diem+=1;
        }
    }
}
void timkiem(node *tree)
{
  soccer_data a;
  printf("Ten doi bong khong chua dau cach\n");
  printf("Nhap vao ten doi can tim: ");scanf("%s",a.ma);printf("\n\n");
  node *tmp=search(tree,a);
  if(tmp == NULL) printf("Khong co doi bong nay\n");
  else printf("Doi %s co %d diem\n",tmp->data.ma,tmp->data.diem);
}

void xuonghang(node **tree)
{
  int x;
  printf("X = ");scanf("%d",&x);
  node *p=*tree;
  printf("cac doi bi xuong hang la\n");
  xoa(*tree,x,p);
  printf("\n\n");
}
void ghifile(FILE *f_ghi,node *tree)
{
  if(!isEmptyTree(tree))
    {
      ghifile(f_ghi,tree->left);
      fprintf(f_ghi,"%10s\t%3d\n",tree->data.ma,tree->data.diem);
      ghifile(f_ghi,tree->right);
    }
}
int main()
{
  FILE *f,*f_ghi;
  char filename[]="bongda.txt";
  char file_ghi[]="ketqua.txt";
  if((f=fopen(filename,"r")) == NULL)
    {printf("Cannot open %s",filename);return -1;}
  if((f_ghi=fopen(file_ghi,"w")) == NULL)
    {printf("Cannot open %s",file_ghi);return -1;}

  node *tree= NULL;
  int k,dem=0;
  do
    {
      menu();
      scanf("%d",&k);getchar();
      switch(k)
        {
        case 1:
          docfile(f,&tree);
          if(isEmptyTree(tree)) printf("1\n");
          break;
        case 2:
          inorder(tree);
          break;
        case 3:
          timkiem(tree);
          break;
        case 4:
          xuonghang(&tree);
          break;
        case 5:
          ghifile(f_ghi,tree);
          printf("Du lieu da duoc ghi ra file %s\n",file_ghi);
          break;
        case 6: fclose(f);fclose(f_ghi); return 0;
        default: printf("Wrong choice\n");
        }
    }
  while (1);
}
