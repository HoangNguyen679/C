#include<stdio.h>
#include<stdlib.h>
#include"doubly_linked_list.h"

int main(){
  node *root = NULL,*cur = NULL,*tail = NULL;
	int x,i,a;
	printf("nhap so note\n");
    scanf("%d",&x);
    for(i = 0; i < x; i++){
    	printf("nhap data cua note %d: \n",i+1);
   		scanf("%d",&a);
   		insertFirst(&root,&cur,&tail,a);
	}
	printf("danh sach da tao:\n");
	printList(root);printf("\n");
    deleteCur(&root,&cur,&tail);
    printList(root);
	return 1;
}
