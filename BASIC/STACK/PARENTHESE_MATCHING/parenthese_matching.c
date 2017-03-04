#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack_list.h"
#define MAX 81

int main(int argc, char *argv[]){
  if (argc != 2){printf("Wrong argument!\nStruct: ./p filename");return 1;}
  stack *s= stackConstruct();
  FILE *f,*f_temp;
  char filename[MAX];
  strcpy(filename,argv[1]);
  f = fopen(filename,"r");
  f_temp = fopen(filename,"r");
  int c,n,i=1,c_temp;
  char str[MAX];
  while((c=fgetc(f)) != EOF){
    if (c == '(' || c== '[' || c == '{') push(s,c);
    else if (c == ')' || c== ']' || c == '}'){
      if (isEmpty_stack(s)){
        printf("\n\nparentheses NOT match\n\n");
        printf("there is not enough parenthesis\n\n");
        return 1;
      }
      if (c == ')' && pop(s) != '('){
        printf("\n\nparentheses NOT match\n\n");
        n=ftell(f);
        while(ftell(f_temp) != n){
          c_temp=fgetc(f_temp);
          if(c_temp == '\n') i++;
        }
        printf("Wrong in line: %i\n\n",i);
        return 1;
      }
      if (c == ']' && pop(s) != '['){
        printf("\n\nparentheses NOT match\n\n");
        n=ftell(f);
        while(ftell(f_temp) != n){
          c_temp=fgetc(f_temp);
          if(c_temp == '\n') i++;
        }
        printf("Wrong in line: %i\n\n",i);
        return 1;
      }
      if (c == '}' && pop(s) != '{'){
        printf("\n\nparentheses NOT match\n\n");
        n=ftell(f);
        while(ftell(f_temp) != n){
          c_temp=fgetc(f_temp);
          if(c_temp == '\n') i++;
        }
        printf("Wrong in line: %i\n\n",i);
        return 1;
      }
    }
  }
  if (isEmpty_stack(s)) printf("\n\nPARENTHESES MATCHING\n\n");
  else {
    printf("\n\nparentheses NOT match\n\n");
    printf("there is not enough CLOSING parenthesis\n\n");
    return 1;
  }
  return 0;
}
