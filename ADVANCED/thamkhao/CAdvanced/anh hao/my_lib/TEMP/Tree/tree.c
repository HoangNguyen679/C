#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

struct node
{
	int data;
	struct node *lptr,*rptr;
};
typedef struct node bnode;
bnode *insert(bnode *p,int value);

void inorder(bnode *p);
void preorder(bnode *p);
void postorder(bnode *p);



bnode *MakeNewNode(int data){
	bnode *newNode = NULL;
	newNode = (bnode*)malloc(sizeof(bnode));
	newNode->lptr = NULL;
	newNode->rptr = NULL;
	newNode->data = data;
	return newNode;
}

bnode *RandomInsert(bnode *tree, int data){
	bnode *newNode, *p;
	newNode = MakeNewNode(data);
	if(tree == NULL) return newNode;
	if(rand()%2 == 0){
		p = tree;
		while(p->lptr != NULL) p = p->lptr;
		p->lptr = newNode;
		printf("Node %d is left child of %d\n", data, (*p).data);
	}
	else{
		p = tree;
		while(p->rptr != NULL) p = p->rptr;
		p->rptr = newNode;
		printf("Node %d is right child of %d\n", data, (*p).data);
	}
	return tree;
}

void main()
{
	srand((unsigned)time(NULL));
	int a,i,j,n;
	bnode *root=NULL;
	do
	{
		printf("\n\tBINARY TREE TRAVERSAL");
		printf("\n\tMENU");
		printf("\n\t1. INSERT\n\t2. INORDER\n\t3. PREORDER\n\t4. POSTORDER\n\t5. EXIT");
		printf("\n\tENTER YOUR CHOICE ===> ");
		scanf("%d",&j);
		switch(j)
		{
			case 1:
			printf("\n\tENTER THE NUMBER OF ELEMENTS TO BE INSERTED ==> ");
			scanf("%d", &n);
			for(i = 0; i < n; i++)
				root = RandomInsert(root, rand()%10);
			
			break;

			case 2:
			inorder(root);
			break;

			case 3:
			preorder(root);
			break;

			case 4:
			postorder(root);
			break;

			case 5:
			exit(0);
		}
	}while(j!=5);
}
bnode *insert(bnode *p,int value)
{
	int ch;
	bnode *newnode;
	if(p==NULL)
	{
		newnode=(bnode *)malloc(sizeof(bnode));
		newnode->data=value;
		newnode->lptr=NULL;
		newnode->rptr=NULL;
	  p=newnode;
	}
	else
	{
		printf("\n\tMENU:");
		printf("\n\t1.LEFT TREE\n\t2.RIGHT TREE");
		printf("\n\tENTER YOUR CHOICE ===> ");
		scanf("%d",&ch);
		if(ch==1)
		p->lptr=insert(p->lptr,value);
		else
		p->rptr=insert(p->rptr,value);
	}
	return p;
}
void preorder(bnode *p)
{
	if(p==NULL)
	return;
	else
	{
		printf("\t%d",p->data);
		preorder(p->lptr);
		preorder(p->rptr);
	}
}

void postorder(bnode *p)
{
	if(p==NULL)
	return;
	else
	{
		postorder(p->lptr);
		postorder(p->rptr);
		printf("\t%d",p->data);
	}
}

void inorder(bnode *p)
{
	if(p==NULL)
	return;
	else
	{
		inorder(p->lptr);
		printf("\t%d",p->data);
		inorder(p->rptr);
	}
}

