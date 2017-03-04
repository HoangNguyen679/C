#include<stdio.h>
#include<stdlib.h>
#include"doubly_linked_list.h"

int main()
{
  node *root = NULL,*cur = NULL,*tail = NULL;
  int x,i,a;
  printf("nhap so note: ");
  scanf("%d",&x);
  for(i = 0; i < x; i++){
    printf("nhap data cua note %d: ",i+1);
    scanf("%d",&a);
    insertLast(&root,&cur,&tail,a);
  }
  printf("danh sach da tao:\n");
  printList(root);printf("\n");
  move_to_front(&root,&cur,&tail,3);
  printList(root);printf("\n");
  transpose(&root,&cur,&tail,4);
  printList(root);printf("\n");
  return 1;
}
