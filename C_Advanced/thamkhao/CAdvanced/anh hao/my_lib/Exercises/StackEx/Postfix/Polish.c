#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX 100

typedef char ElementType;

#include "StackLinkList.h"

char string[MAX];

StackType *S = NULL;
StackType *P = NULL;

int main(int argc, char const *argv[]){
	printf("Input: "); gets(string);
	int n = strlen(string);

	int i;
	for(i=0; i<n; i++){
		char temp = string[i];
		if (temp>='0' && temp<='9') Push(temp, &P);
		if (temp=='*' || temp=='/') Push(temp, &S);
		if (temp=='+' || temp=='-'){

			if (string[i+1] != ' ') {
				Push(string[i+1]-'0', &P);
				i++;
			}
			else {
				if(!IsEmpty(&S) && (S->element=='*' || S->element=='/')) {
					Push(Pop(&S), &P);
					Push(temp, &S);
				} else Push(temp, &S);
			}
		}
		if (temp == '(') Push(temp, &S);
		if (temp == ')'){
			char ngoac;
			while(((ngoac=Pop(&S)) != '(')){ 
				if(IsEmpty(&S)) {
					printf("Input Error");
					return 1;				
				}
				Push(ngoac, &P);
			}
		}
	}	


//Output
	while(!IsEmpty(&S)) {
		char temp = Pop(&S);
		if(temp == '(' || temp == ')') {
			printf("Input Error");
			return 1;
		}
		Push(temp, &P);
	}
	while(!IsEmpty(&P)) Push(Pop(&P), &S);
	printf("\nOutput: ");
	while(!IsEmpty(&S)) {
		char temp = Pop(&S);
		if (temp>=0 && temp<=9) printf("-%d ", temp);
		
		else printf("%c ",temp);
		
	}
	printf("\n");

	return 0;
}