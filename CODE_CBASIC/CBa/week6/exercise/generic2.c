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
  node* next;
};
typedef node *node;

void MakeNullList (node *root,node *prev,node *cur) {
  (*root) = NULL;
  (*prev) = NULL;
  (*cur) = NULL;
}

int isEmpty (node root) {
  return (root == NULL);
}


node *makeNewNode(elementtype e){
  node *new = (node *)malloc(sizeof(node));
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

void displayNode(node *p) {
  elementtype tmp;
  tmp =
  if(p == NULL) {
    printf("Mistake pointer NULL\n");
    return;
  }
  printf("%-30s\t%-12s\t%-30s\n",tmp.name,tmp.tel,tmp.email);
}

node *insertFirst(elementtype e){
  node *new = makeNewNode(e);
  new->element = e;
  new->next = root;
  root = new;
  cur = new;
  return new;
} //het ham insertFirst

node *insertAfterCur(elementtype e){
  node *new = makeNewNode(e);
  if(root == NULL) cur=root = new;
  else{
    new->next = cur->next;
    //prev = cur;
    cur->next = new;
  }
} //het ham insertAfterCur

node *insertBeforeCur(elementtype e){
  node *new = makeNewNode(e);
  if(root == NULL) {
    root = new;
    cur = root;
    prev = NULL;
  }
  else {
    if (cur == root) insertFirst(e);
    else {
      new->next=cur;
      prev->next=new;
      cur=new;
    }
  }
}

node* insertAtPosition(node* root,elementtype ad,int n) {
  if(n == 0) {
    insertFirst(ad);
    return root;
  }
  if(n < 0 || root == NULL) {
    printf("Loi!/n");
    return root;
  }
  int i,j=0;
  node * tmp;
  for(tmp = root ; tmp != NULL ; tmp = tmp->next) j++;
  if(n > j) {
    printf("Danh sach co it hon %d phan tu",n);
    return root;
  }
  tmp = root;
  for(i = 0; i < n ; i++) tmp = tmp->next;
  node* new = makeNewNode(ad);
  new->next = tmp->next;
  tmp->next = new;
  return new;
}

node* delAtPosition(node *root,int n) {
  if(root == NULL) {
    printf("Danh sach rong/n");
    return root;
  }
  int i,j=0;
  node * tmp,*tmpprev;
  for(tmp = root ; tmp != NULL ; tmp = tmp->next) j++;
  if(n > j) {
    printf("Danh sach co it hon %d phan tu",n);
    return root;
  }
  tmp = root;
  tmpprev = root;
  for(i = 0; i < n ; i++) tmp = tmp->next;
  for(i = 0; i < (n-1) ; i++) tmpprev = tmpprev->next;
  node* del;
  if(tmp == root) {
    del = root;
    root = del->next;
    free(del);
    return root;
  }
  tmpprev->next = tmp->next;
  free(tmp);
  free(del);
  return root;
}


void freeList(){
  node* to_free;
  to_free = root;
  while(to_free != NULL) {
    root = root->next;
    free(to_free);
    to_free = root;
  }
}

void delFirst(){
  if(root == NULL) printf("Danh sach rong\n");
  node *del;
  del = root;
  root = del->next;
  free(del);
  cur = root;
  prev = NULL;
}

void delCur(){
  if (root == NULL) printf("Danh sach rong\n");
  else {
    if(cur == root) delFirst;
    else {
      prev->next = cur->next;
      free(cur);
      cur = prev->next;
    }
  }
}

void printNode(node *p){
  if(p==NULL) printf("Loi con tro NULL\n");
  for(p;p!=NULL;p=p->next)
    printf("%-30s\t%-15s\t%-30s\n",(p->element).name,(p->element).tel,(p->element).email);
} //het ham printNode

int main(){
  address tmp;
  int n=3;
  while(n){
    tmp=readNode();
    insertAfterCur(tmp);
    n--;
  }
  printNode(root);
  insertAtPosition(root,tmp,2);
  printf("\n");
  printNode(root);
  delAtPosition(root,3);
  printf("\n");
  printNode(root);
  freeList();
}//het ham main
