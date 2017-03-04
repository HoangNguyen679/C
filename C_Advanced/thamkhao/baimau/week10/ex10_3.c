#include<stdio.h>
#include<stdlib.h>
#include"libTree.h"
void in(node *root)
{
}
int main()
{
  char str[MAX];
  char a,b,c,d;
  node *root=NULL;
  printf("Nhap vao cac gia tri cua bieu thuc:\n");
  printf("a=");scanf("%c",&a);while(getchar()!='\n');
  printf("b=");scanf("%c",&b);while(getchar()!='\n');
  printf("c=");scanf("%c",&c);while(getchar()!='\n');
  printf("d=");scanf("%c",&d);while(getchar()!='\n');
  root=merge('+',merge('!',creat(a),NULL),merge('/',merge('-',creat(b),creat(c)),creat(d)));
  printf("Cay bieu thuc duoc mo ta:\n");
  in(root);
  printf("Dang tien to(thuc hien tu phai sang trai):");preoder(root);printf("\n");
  printf("Dang hau to(thuc hien tu tri sang phai):");postoder(root);printf("\n");
  printf("Dang trung to(thuc hien tu trai sang phai k ke thu tu uu tien):\n");inoder(root);printf("\n");
  printf("Mo ta\n");

  return 0;
}

