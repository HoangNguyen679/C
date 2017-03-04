#include<stdio.h>
#define Max 50
typedef int Eltype;
typedef Eltype StackType[Max];
int top;

void Initialize(StackType stack) {
  top=0;}
int empty(StackType stack) {
  return top==0;}
int full(StackType stack) {
  return top==Max;}
void push(Eltype el, StackType stack) {
  if(full(stack))
    printf("stack overflow");
  else stack[top++]=el;}
Eltype pop(StackType stack) {
  if(empty(stack)) 
    printf("Stack overflow");
  else return stack[--top];}
//Eltype top(StackType stack);

void main() {
  StackType stack;
  Eltype el;
  Initialize(stack);
  int i,x;
  for(i=1;i<=5;i++){
    printf("phan tu thu %d: ",i);
    scanf("%d",&el);
    push(el,stack);}
  for(i=1;i<=5;i++){
    x=pop(stack);
    printf("%d\t",x);}
  printf("\n");
  return;}
/* cai dat stackarray.h, stackstruct.h, stacklist.h
   BT cong so lon*/
