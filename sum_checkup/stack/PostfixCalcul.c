#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000
#define MAX_LINE 81
int stack[MAX];
int top;

//tinh gia tri bieu thuc
int eval(char *s);
// ktra co phai phep toan
int isOperation(char op);
//pop
int pop();
//push
void push(int a);
//thuc hien phep toan
int doOperation(int a, int b, char op);

int main(){
	char expression[MAX_LINE];
	int value;

	printf("Nhap vao bieu thuc: \n");
	scanf("%[^\n]",expression);

	value = eval(expression);
	printf("Gia tri cua bieu thuc: %i\n", value);

	return 0;
}

int isOperation(char op){
	if(op == '+' || op == '-' || op == '*')
		return 1;
	else 
		return 0;
}

void push(int a){
	stack[++top] = a;
}

int pop(){
	int ret = stack[top--];
	return ret;
}

int doOperation(int a, int b, char op){
	int ans;
	switch(op){
		case '+' : ans = a + b; break;
		case '-' : ans = a - b; break;
		case '*' : ans = a * b; break;
	}
	return ans;
}

int eval(char *s){
	char *ptr;
	int first, second, c;
	ptr = strtok(s, " ");
	top = -1;
	while(ptr){
		if(isOperation(*ptr)){
			second = pop();
			first = pop();
			c = doOperation(first, second, *ptr);
			push(c);
		} else {
			c = atoi(ptr);
			push(c);
		}
		ptr = strtok(NULL, " ");
	}
	return pop();
}