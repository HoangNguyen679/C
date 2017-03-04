#include<stdio.h>
#include<string.h> 
typedef struct node
{
	char data;
	struct node *next;
} *NODE;
typedef struct {
	NODE head
} stack;
stack initStack(stack *S)
{
	(*S).head=NULL;
	return (*S);
}
stack stackPush(stack *S,char a)
{
	NODE p;
	p=(NODE )malloc(sizeof(struct node));
	p->data=a;
	if((*S).head==NULL) {
		S->head=p;
		p->next=NULL;
		return *S;
	}
	p->next=S->head;
	S->head=p;
	return *S;
}
char stackPop(stack *S)
{
	NODE p;
	p=(*S).head;
	(*S).head=(*S).head->next;
	return p->data;
}
stack arrayPush(char *a,stack *S)
{
	int i;
	for(i=0;i<strlen(a);i++)
	{
		stackPush(S,a[i]);
	}
	return (*S);
}
printStack(stack S)
{
	NODE p;
	for(p=S.head;p!=NULL;p=p->next)
		printf("%c",p->data);
	
}
 
int val(char chr) {return (chr-'0');}//so tuong ung voi ki tu chr
char chr(int val) {return (val+'0');} //chu tuong ung voi so var
char chradd(char a, char b, int *carry)  // carry la so du
 {
    int temp = val(a) + val(b) + *carry;
    carry = temp/10;
    return chr(temp %10);
}
stack stradd (stack a,stack b, stack *c) 
{
int i,j,carry=0;
char m,n,k;
while(a.head && b.head) 
{
	m=stackPop(&a); n=stackPop(&b);
	k=chradd(m,n,&carry);
	stackPush(c,k);
}
if(a.head==NULL && b.head==NULL) return *c;
if(a.head==NULL)
{
	while(b.head){
	n=stackPop(&b);
	k=chradd('0',n,&carry);
	stackPush(c,k);
}
}
else if(b.head==NULL)
{
	while(a.head)
	{
	m=stackPop(&a);
	k=chradd(m,'0',&carry);
	stackPush(c,k);
}
}
if(carry)
stackPush(c,chr(k));
return  *c;
}
int main(int argv,char * argc[])
{
	stack so1,so2,so3;
	initStack(&so1);
	initStack(&so2);
 	initStack(&so3);
 	char a[40],b[40],c[40];
 	printf("so thu 1:\n");
 	gets(a);
 	arrayPush(a,&so1);
 	printStack(so1);
 	printf("\n");
	printf("viet so thu 2: \n");
	gets(b);
	arrayPush(b,&so2);
	printStack(so2);
	printf("\n");
	stradd(so1,so2,&so3);
	printf("so thu 3: \n");
	printStack(so3);
	printf("\n");
	return 1;
}