#include<stdio.h>
#include<stdlib.h>
#include<libTree.h>
#include<libQueue.h>

typedef struct add{
  char operation;
  int operand;} add;
typedef struct node {
  add data;
  struct node *left,*right;}node;

void main() {
  char str[100];
  printf("Nhap vao bieu thuc dang hau to: ");
  gets(str);
  char a;
  for(a=str;a!=NULL;a++) {
    switch(a) {
    case '+':

      /* nhap vao bieu thuc gia tri dang hau to, lap duoc cay va tinh duoc gia tri bieu thuc*
	 bai1: Viet chuong trinh xay dung cay nhi phan tu bieu thuc so hoc bieu dien o dang hau to. Kiem tra kq bang tinh nang duyet theo thu tu giua. Tinh gia tri bieu thuc (lap menu)
         bai2: Viet ham FindMin, FindMax cho thu vien cay nhi phan tim kiem
Tham so: con tro root
Return: con tro toi nut nho nhat hay lon nhat
         bai3: Viet chuong trinh tu dien thuat ngu tin hoc Anh Viet. Tieng Viet khong dau
Goi y: mot muc tu gom: tu tieng anh - giai nghia tieng viet
Dung cau truc BST de luu tru
Chuong trinh phai cho phep: tim kiem, them tu, xoa tu, ghi du lieu vao file
Mo rong: moi tu co 1 danh sach cac tu dong nghia.

