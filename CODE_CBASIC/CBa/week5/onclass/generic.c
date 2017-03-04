#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef address elementtype;
typedef struct node node;
typedef struct node{
  elementtype element;
  node* next;
};

node* root;
node* cur;
node* prev;

typedef struct address_t{
  char name[30];
  char tel[12];
  char email[30];
}address;

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

node *insertFirst(elementtype e){
  node *new = makeNewNode(e);
  new->element = e;
  new->next = root;
  root = new;
  cur = new;
  return new;
} //het ham insertFirst

node *insertAfterCur(elementtype e){
  node *new = makeNewNode(addr);
  new->element = e;
  if(root == NULL) root = new;
  else{
    new->next = cur->next;
    prev = cur;
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

void freeList(){
  to_free = root;
  while(to_free != NULL) {
    root = root->next;
    free(to_free);
    to_free = root;
  }
}

void delList(){}

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
    printf("%-30s\t%-12s\t%-30s\n",(p->addr).name,(p->addr).tel,(p->addr).email);
} //het ham printNode

int main(){
  address tmp;
  int n=3;
  while(n){
    tmp=readNode();
    insertBeforeCur(tmp);
    n--;
  }
  printNode(root);
  freeList();
}//het ham main
