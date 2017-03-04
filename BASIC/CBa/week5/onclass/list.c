#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct address_t{
  char name[30];
  char tel[12];
  char email[30];
}address;

struct list_el{
  struct list_el *next;
  address addr;
};

typedef struct list_el node_addr;

node_addr *root = NULL,
  *cur = NULL,
  *prev = NULL;

// thiet ke ham tao ra nut moi
node_addr *makeNewNode1() {
  node_addr* new =(node_addr *)malloc(sizeof(node_addr));
  strcpy((new->addr).name,"Nguyen Duc Hoang");
  strcpy((new->addr).tel,"0978576569");
  strcpy((new->addr).email,"ndhoang96@gmail.com");
  new->next = NULL;
  return new;
} // het ham makeNewNode1

node_addr *makeNewNode(address addr){
  node_addr *new = (node_addr *)malloc(sizeof(node_addr));
  new->addr = addr;
  new->next = NULL;
  return new;
} // het ham makeNewNode

address readNode(){
  address tmp;
  printf("Nhap ten: ");gets(tmp.name);
  printf("Nhap so dien thoai: ");gets(tmp.tel);
  printf("Nhap email: ");gets(tmp.email);
  return tmp;
}

node_addr *insertFirst(address addr){
  node_addr *new = makeNewNode(addr);
  new->addr = addr;
  new->next = root;
  root = new;
  cur = new;
  return new;
} //het ham insertFirst

node_addr *insertAfterCur(address addr){
  node_addr *new = makeNewNode(addr);
  new->addr = addr;
  if(root == NULL) root = new;
  else{
    new->next = cur->next;
    prev = cur;
    cur->next = new;
  }
} //het ham insertAfterCur

node_addr *insertBeforeCur(address addr){
  node_addr *new = makeNewNode(addr);
  if(root == NULL) {
    root = new;
    cur = root;
    prev = NULL;
  }
  else {
    if(cur==root) insertFirst(addr);
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
  node_addr *del;
  del = root;
  root = del->next;
  free(del);
  cur = root;
  prev = NULL;
}

void delCur(){
  if (root == NULL) printf("Danh sach rong\n");
  else {
    if(cur = root) delFirst;
    else {
      prev->next = cur->next;
      free(cur);
      cur = prev->next;
    }
  }
}

void printNode(node_addr *p){
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
