typedef struct {
  char inf;} elmType;
typedef struct nodeType {
  elmType element;
  struct nodeType *left, *right;} ;
typedef struct nodeType *treetype;

void makenullTree(treetype *t) {
  (*t).element=NULL;}

nodeType *create_node(treetype N,elmType NewData) {
  N=(node_type*)malloc(sizeof(nodeType));
  if(N!=NULL) {
    N->left=NULL;
    N->right=NULL;
    N->element=NewData;}
  return N;}

int emptyTree(treetype t) {
  return t==NULL;}

treetype LeftChild(treetype n) {
  if(n!=NULL) return n->left;
  else return NULL;}

treetype RightChild(treetype n) {
  if(n!=NULL) return n->right;
  else return NULL;}

int isLeaf(treetype n) {
  if(n!=NULL) 
    return(LeftChild(n)==NULL && RightChild(n)==NULL);
  else return -1;}

int nb_nodes(treetype T) {
  if(emptyTree(T)) return 0;
  else
    return 1+nb_nodes(LeftChild(T))+nb_nodes(RightChild(T));}

treetype createfrom2(elmType v, treetype l, treetype r) {
  treetype N;
  N=(nodeType*)malloc(sizeof(nodeType));
  N->element=v;
  N->left=l;
  N->right=r;
  return N;}

treetype Add_Left(treetype *Tree, elmType NewData) {
  nodeType *NewNode=create_node(NewData);
  if(NewNode==NULL) return (NewNode);
  if(*Tree==NULL)
    *Tree=NewNode;
  else {
    nodeType *Lnode=*Tree;
    while(Lnode->left!=NULL) 
      Lnode=Lnode->left;
    Lnode->left=NewNode;}
  return NewNode;
}

treetype Add_Right(treetype *Tree, elmType NewData) {
 nodeType *NewNode=create_node(NewData);
  if(NewNode==NULL) return (NewNode);
  if(*Tree==NULL)
    *Tree=NewNode;
  else {
    nodeType *Lnode=*Tree;
    while(Lnode->right!=NULL) 
      Lnode=Lnode->right;
    Lnode->right=NewNode;}
  return NewNode;
}


void main() {
  treetype T1,T2,T3,T4;
  create_node(T4,-);
  Add_Left(T4,b);
  Add_Right(T4,c);
  create_node(T3,/);
  Add_Right(T3,d);
  Add_Left(T3,T4);
  create_node(T2,!);
  Add_Left(T2,a);
  create_node(T1,+);
  createfrom2(T1,T2,T3);
  return;}
 /*Bai1: bo sung ham: 1. Tinh chieu cao cua cay
                2.Tinh so nut la, so nut trong, so cac nut con phai
 Bai2: Tao cay bieu thuc nhu trong slide 
 Kiem tra cay co dung hay khong: in ra nut goc, cay con trai, cay con phai, roi lai in nut goc
 Bai3: Tao file van ban USopen.txt co noi dung: 
          Dong 1 chua 16 doi thu
          Xay dung cay mo ta kq thi dau cho toi tran chung ket. Ban dau 16 doi thu la cac nut la
          Lua chon nguoi choi thang trong mot tran dau la ngau nhien
          In kq ra file treegame.txt  (Lay cac vdv tennis)
