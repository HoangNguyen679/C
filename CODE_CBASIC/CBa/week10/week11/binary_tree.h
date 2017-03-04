typedef struct {
  char inf;} elmType;
typedef struct nodeType {
  elmType element;
  struct nodeType *left, *right;} ;
typedef struct nodeType *treetype;

void makenullTree(treetype *t) {
  (*t).element=NULL;}

nodeType *create_node(elmType NewData) {
  treetype N;
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

int hightTree(treetype *Tree) {
  if(*Tree==NULL) return 0;
  int lh=hightTree(Tree->left);
  int rh=hightTree(Tree->hight);
  return 1+(lh>rh?lh:rh);}

void inorderprint(treetype tree) {
  if(tree!=NULL) {
    inorderprint(tree->left);
    printf("%4d\n",tree->inf);
    inorderprint(tree->right);}}

void preorderprint(treetype tree) {
  if(tree!=NULL) {
    printf("%4d\n",tree->inf);
    preorderprint(tree->left);
    preorderprint(tree->right);}}

void postorderprintf(treetype tree) {
  if(tree!=NULL) {
    postorderprint(tree->left);
    postorderprint(tree->right);
    printf("%4d\n",tree->inf);}}

