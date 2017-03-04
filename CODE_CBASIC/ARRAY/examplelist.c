#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "singly_linked_list.h"

int main(){

	node *root = NULL, *cur = NULL, *prev = NULL;
	node *root1 = NULL, *cur1 = NULL, *prev1 = NULL;
	node *root2 = NULL, *cur2 = NULL, *prev2 = NULL;

	elementtype a;
	int i,n;
	// tao phan tu dau tien
	srand ((unsigned)time(NULL));
	a = -100 + rand() % 201;
	root = insertFirst(&root,&cur,&prev,a);
	printf("Nhap vao so luong phan tu\n");
	scanf("%i",&n); printf("\n");

	//tao ngau nhien danh sach va dua ra man hinh
	cur = root;
	for(i = 2; i <= n; i++){
		a = -100 + rand() % 201;
		cur = insertAfterCur(&root,&cur,&prev,a);
	}
	printf("========> Danh sach ban dau: \n");
	printList(root);printf("\n");
    cur = root;
	while(cur){
		if(cur->e > 0)
			if (!root1) root1 = insertFirst(&root1,&cur1,&prev1,cur->e);
			else {
				insertAfterCur(&root1,&cur1,&prev1,cur->e);
			}
        else{
			if (!root2) root2 = insertFirst(&root2,&cur2,&prev2,cur->e);
			else {
				insertAfterCur(&root2,&cur2,&prev2,cur->e);
				}
        }
			cur = cur->next;
	}
	printf("========> Danh sach so duong: \n");printList(root1);printf("\n");
	printf("========> Danh sach so am: \n");printList(root2);printf("\n");
	freeList(&root);freeList(&root1);freeList(&root2);
	return 0;
}
