#include<stdio.h>
#include<stdlib.h>
#include"linked_list_sort.h"

node *root1,*cur1,*prev1;
node *root2,*cur2,*prev2;
node *root,*cur,*prev;
node *rootchinh,*curchinh,*prevchinh;

FILE *f1,*f2,*f;
char file1[]="9A.txt";
char file2[]="9B.txt";
char file[]="excellent.txt";

void menu()
{
  printf("\n\nMenu\n\n");
  printf("1. Doc file\n");
  printf("2. Tim kiem\n");
  printf("3. Danh sach xuat sac\n");
  printf("4. Ghi file\n");
  printf("5. Gop danh sach\n");
  printf("6. Thoat\n");
  printf("\nPlease select: ");
}
void docfile()
{
  infosv a,b;
  char str[MAX];
  int l1=0,l2=0;
  while(fgets(str,MAX,f1)) l1++;
  if(l1 %2 ==1)
    {
      printf("Lop 9A\n");
      printf("Thieu diem thang cuoi cung nha :v\n");
      double diem1;
      printf("Nhap diem cho no nao :");scanf("%lf",&diem1);
      fprintf(f1,"%lf",diem1);
    }
  rewind(f1);
  while(fgets(str,MAX,f2)) l2++;
  if(l2 %2 ==1)
    {
      printf("Lop 9B\n");
      printf("Thieu diem thang cuoi cung nha :v\n");
      double diem2;
      printf("Nhap diem cho no nao :");scanf("%lf",&diem2);
      fprintf(f2,"%lf",diem2);
    }
  rewind(f2);
  while(!feof(f1))
    {
      fscanf(f1,"%[^\n]\n",a.ten);
      fscanf(f1,"%lf\n",&a.diem);
      insert(&root1,&cur1,&prev1,a);
    }
  //printList(root1);
  while(!feof(f2))
    {
      fscanf(f2,"%[^\n]\n",a.ten);
      fscanf(f2,"%lf\n",&a.diem);
      insert(&root2,&cur2,&prev2,a);
    }
  //printList(root2);
}
void timkiem()
{
  double x;
  int i=1,j=1;
  printf("\n\nNhap so x: ");scanf("%lf",&x);getchar();
  node *tmp1=root1,*tmp2=root2;
  while(tmp1 != NULL)
    {
      if(tmp1->data.diem >=x)
        {
          printNode(tmp1);
          i++;
        }
      tmp1=tmp1->next;
    }
  if(i==1) printf("Khong co sinh vien nao lop 9A diem >= %4.1f\n",x);
  while(tmp2 != NULL)
    {
      if(tmp2->data.diem >=x)
        {
          printNode(tmp2);
          j++;
        }
      tmp2=tmp2->next;
    }
  if(j==1) printf("Khong co sinh vien nao lop 9B diem >= %4.1f\n",x);
}
void xuatsac()
{
  int i=0,j=0;
  node *tmp1=root1,*tmp2=root2;
  while(tmp1 != NULL)
    {
      if(tmp1->data.diem >= 8.5)
        {
          insert(&root,&cur,&prev,tmp1->data);
          i++;
        }
      tmp1=tmp1->next;
    }
  while(tmp2 != NULL)
    {
      if(tmp2->data.diem >= 8.5)
        {
          insert(&root,&cur,&prev,tmp2->data);
          j++;
        }
      tmp2=tmp2->next;
    }
  printList(root);
}
void ghifile()
{
  node *tmp=root;
  while(tmp != NULL)
    {
      fprintf(f,"%s\n%f\n",tmp->data.ten,tmp->data.diem);
      tmp=tmp->next;
    }
}
void in()
{
  node *tmp1=root1,*tmp2=root2;
  while(tmp1 != NULL)
    {
       insert(&rootchinh,&curchinh,&prevchinh,tmp1->data);
       tmp1=tmp1->next;
    }
  while(tmp2 != NULL)
    {
      insert(&rootchinh,&curchinh,&prevchinh,tmp2->data);
      tmp2=tmp2->next;
    }
  printList(rootchinh);
}
int main()
{
  root1=cur1=prev1=root2=cur2=prev2=root=cur=prev=rootchinh=curchinh=prevchinh=NULL;
  int k;
  f1=fopen(file1,"r+");
  f2=fopen(file2,"r+");
  f=fopen(file,"w");
  do
    {
      menu();scanf("%d",&k);getchar();
      switch(k)
        {
        case 1:docfile();break;
        case 2:timkiem();break;
        case 3:xuatsac();break;
        case 4:ghifile();break;
        case 5:in();break;
        case 6:return 0;
        default: printf("\n\nnhap sai\n\n");
        }
    }
  while(1);
}
