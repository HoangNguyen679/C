#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.h"
void menu()
{
  printf("\n\nMENU\n\n");
  printf("1. Dang nhap\n");
  printf("2. Thoat\n");
  printf("Please select: ");
}
void menu1()
{
  printf("\n\nSINHVIEN\n\n");
  printf("1. Xem diem\n");
  printf("2. Doi mat khau\n");
  printf("3. Ghi lai thong tin len file\n");
  printf("4. Thoat\n");
  printf("Please select: ");
}
void menu2()
{
  printf("\n\nADMIN\n\n");
  printf("1. Them sinh vien\n");
  printf("2. Danh sach sinh vien\n");
  printf("3. Xoa sinh vien\n");
  printf("4. Ghi lai thong tin len file\n");
  printf("5. Thoat\n");
  printf("Please select: ");
}
void docfile(FILE *f,node **tree)
{
  data_student a;
  while(!feof(f))
    {
      fscanf(f,"%s\t%s\t%f\n",a.user,a.pass,&a.diem);
     *tree=insert(*tree,a);
    }
}
void ghifile(FILE *f,node *tree)
{
  if(!isEmptyTree(tree))
    {
      ghifile(f,tree->left);
      fprintf(f,"%s\t%s\t%f\n",tree->data.user,tree->data.pass,tree->data.diem);
      ghifile(f,tree->right);
    }
}
void themsv(node **tree)
{
  data_student a;
  printf("Nhap user: ");scanf("%s",a.user);
  printf("Nhap pass: ");scanf("%s",a.pass);
  printf("Nhap diem: ");scanf("%f",&a.diem);getchar();
  (*tree) = insert(*tree,a);
}
void xoasv(node **tree)
{
  data_student a;
  node *temp;
  printf("Nhap user sinh vien muon xoa: ");scanf("%s",a.user);
  if((temp=search(*tree,a)) == NULL)
    {printf("Khong co sinh vien can tim\n");return;}
  else
    {
      if(strcmp(temp->data.user,"Admin") == 0)
        {printf("Khong co quyen truy cap\n");return;}
      else
        {
          printf("%15s\t%10s\t%.1f\n",temp->data.user,temp->data.pass,temp->data.diem);
          printf("Du lieu sinh vien tren se bi xoa\n");
          *tree = delete(*tree,temp->data);
        }
    }
}
int main()
{
  FILE *f;
  char filename[]="sinhvien.txt";
  if((f=fopen(filename,"r+"))== NULL)
    {printf("Cannot open %s\n",filename);return -1;}
  int k,k1,k2;
  node *tree=NULL;
  node *temp = NULL;
  data_student a,them;
  int i=0;
  char matkhaumoi1[MAX],matkhaumoi2[MAX];
  docfile(f,&tree);
  do
    {
      menu();
      scanf("%d",&k);getchar();
      switch(k)
        {
        case 1:
          {
            do
              {
                printf("Username: ");scanf("%s",a.user);
                printf("Password: ");scanf("%s",a.pass);
                if((temp=search(tree,a)) == NULL)
                  {
                    i++;
                    if(i == 3) return -2;
                    printf("\n\nNhap sai\n\n");
                    continue;
                  }
                else
                  {
                    if(strcmp(a.pass,temp->data.pass) != 0)
                      {
                        i++; if(i == 3) return -2;
                        printf("\n\nNhap sai\n\n");
                        continue;
                      }
                    else
                      {
                        printf("Dang nhap thanh cong");
                        if(strcmp(a.user,"Admin") != 0)
                          {
                            do
                              {
                                menu1();
                                scanf("%d",&k1);getchar();
                                if(k1==4)break;
                                switch(k1)
                                  {
                                  case 1:
                                    printf("Diem cua %s la %.1f\n",temp->data.user,temp->data.diem);break;
                                  case 2:
                                    printf("Nhap mat khau moi: ");
                                    scanf("%s",matkhaumoi1);
                                    printf("Nhap lai mat khau : ");
                                    scanf("%s",matkhaumoi2);
                                    if(strcmp(matkhaumoi1,matkhaumoi2) != 0)
                                      printf("Hai mat khau khong khop\n");
                                    else
                                      {
                                        strcpy(temp->data.pass,matkhaumoi1);
                                        printf("Mat khau da duoc doi\n");
                                      }
                                    break;
                                  case 3:
                                    {rewind(f);ghifile(f,tree); break;}
                                  default: printf("Wrong choice\n");
                                  }
                              }
                            while(1);
                          }
                        else
                          {
                            do
                              {
                                menu2();
                                scanf("%d",&k2);getchar();
                                if(k2==5) break;
                                switch(k2)
                                  {
                                  case 1:
                                    themsv(&tree);break;
                                  case 2:
                                    printf("Danh sach sinh vien:\n\n");
                                    inorder(tree);
                                    break;
                                  case 3:
                                    xoasv(&tree);break;
                                  case 4:
                                    {rewind(f);ghifile(f,tree); break;}
                                  default: printf("Wrong choice\n");
                                  }
                              }
                            while(1);
                          }
                      }
                  }break;
              }
            while(1);
          }/////////////////////////////////////////////////////////// hetcase1
          break;
        case 2: fclose(f);return 0;
        default: printf("Wrong choice\n");
        } //////////////////////////////////////////////////////////// het vong switch menu chinh
    }///////////////////////////////////////////////////////////////// het vong do menu chinh
  while(1);
} //////////////////////////////////////////////////////////////////// het main

