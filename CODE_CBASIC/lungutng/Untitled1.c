#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct address_t{
  char name[30];
  char tel[12];
  char email[30];
}address;

typedef address elementtype;

typedef struct node{
  elementtype element;
  struct node* next;
};
typedef struct node node;
node *root,*root2;
node* cur;
node* prev;

node *makeNewNode(elementtype e){
  node *new = (node *)malloc(sizeof(struct node));
  new->element = e;
  new->next = NULL;
  return new;
} // het ham makeNewNode

elementtype readNode(){
  elementtype tmp;
  printf("Nhap ten: ");gets(tmp.name);
  printf("Nhap so dien thoai: ");gets(tmp.tel);
  printf("Nhap email: ");gets(tmp.email);
  return tmp;
}

node *insertFirst(elementtype e){
  node *new = makeNewNode(e);
  new->element = e;
  new->next = root;
  root = new;
  cur = new;
  return new;
} //het ham insertFirst
void printNode(node *p) {
  if(p == NULL) printf("Loi con tro NULL\n");
  for(p ; p!=NULL ; p = p->next)
    printf("%-30s\t%-15s\t%-30s\n",(p->element).name,(p->element).tel,(p->element).email);
}
void splitList(int n,int m) {
  if(n < 0 || n == 0 || root == NULL) {
    printf("Loi!/n");
    return ;
  }

  int i,j=0;
  node *tmp,*tmp2;
  for(tmp = root ; tmp != NULL ; tmp = tmp->next) j++;
  if(n+m > j || m > (j-n+1)) {
    printf("Danh sach co %d phan tu",j);
    return ;
  }

  tmp=root;
  for(i = 0 ; i < n-1 ; i++) tmp = tmp->next;
  root2 = tmp->next;
  tmp2=root2;
  for(i = 0 ; i < m-1 ; i++) tmp2 = tmp2->next;
  tmp->next = tmp2->next;
  return;
}
void splitList2(int n) {
  if(n < 0 || root == NULL) {
    printf("Loi!/n");
    return ;
  }
  int i,j=0;
  node *tmp,*tmp2;
  for(tmp = root ; tmp != NULL ; tmp = tmp->next) j++;
  if(n > j) {
    printf("Danh sach co it hon %d phan tu",n);
    return ;
  }
  tmp = root;
  for(i = 0 ; i < n-1 ; i++) tmp = tmp->next;
  root2 = tmp->next;
  tmp2 = root2;
  tmp->next = NULL;
  return;
}
int main() {
  root=NULL;
  address tmp;
  int n=8;
  while(n){
    tmp=readNode();
    insertFirst(tmp);
    n--;
  }
  printNode(root);
  splitList2(3);
  printf("\n");
  printNode(root);
  printf("\n");
  printNode(root2);
}
