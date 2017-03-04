#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 81
//////////////////////////////////////////////////////////////// khai bao cay
typedef struct
{
   char word[MAX];
   int count;
}word_info;
typedef word_info  elementtype;
typedef struct node
{
  elementtype data;
  struct node *left,*right;
}node;
////////////////////////////////////////////////////////////////////////////////// khai bao queue
typedef node* qelementtytpe;
/*
typedef struct qnode{
  qelementtytpe e;
  struct qnode *next,*prev;
}qnode;
*/
typedef struct qnode{
  qelementtytpe e;
  struct qnode *next;
}qnode;

typedef struct
{
  qnode *front,*rear;
}queue;
///////////////////////////////////////////////////////////////////////////////////cac ham queue
void queueConstruct(queue *q)
{
  q->front = (qnode *)malloc(sizeof(qnode));
  q->front->next = NULL;
  q->rear = q->front;
}
int isEmpty_queue(queue q)
{ return (q.front == q.rear);}
void enqueue(queue *q,qelementtytpe x)
{
  qnode *new;
  new=(qnode*)malloc(sizeof(qnode));
  new->next=NULL;
  q->rear->e=x;
  q->rear->next=new;
  q->rear=new;
}
node * dequeue(queue *q)
{
  node * x= NULL;
  if(!isEmpty_queue(*q))
    {
      qnode *tmp;
      tmp = q->front;
      q->front = q->front->next;
      x=tmp->e;
      free(tmp);
      return x;
    } else printf("\n\nEMPTY QUEUE\n\n");
}
////////////////////////////////////////////////////////////////////////////// cac ham cua tree
///////////////////////////////////////////////////////////////////////////// duyet cay theo chieu rong
void breath_order(node * tree)
{
  queue q;
  // node *temp;
  queueConstruct(&q);
  if(tree != NULL)
    {
      enqueue(&q,tree);
      while(!isEmpty_queue(q))
        {
          tree = dequeue(&q);
          printf("%20s\t%6d\n",tree->data.word,tree->data.count);
          if(tree->left != NULL) enqueue(&q,tree->left);
          if(tree->right != NULL) enqueue(&q,tree->right);
        }
    }
}
/////////////////////////////////////////////////////////////////// duyet cay theo thu tu giua, truoc , sau
void inorder(node *tree)
{
  if(tree != NULL)
    {
      inorder(tree->left);
      printf("%20s\t%6d\n",tree->data.word,tree->data.count);
      inorder(tree->right);
    }
}
void preorder(node *tree)
{
  if(tree != NULL)
    {
      printf("%20s\t%6d\n",tree->data.word,tree->data.count);
      preorder(tree->left);
      preorder(tree->right);
    }
}
void postorder(node *tree)
{
  if(tree != NULL)
    {
      postorder(tree->left);
      postorder(tree->right);
      printf("%20s\t%6d\n",tree->data.word,tree->data.count);
    }
}
/*
void prettyprint(node* tree,char *prefix){
	char *prefixend=prefix+strlen(prefix);
	if (tree!=NULL)
      {
		printf("%04d",tree->data);
		if (tree->left!=NULL)
          if (tree->right==NULL)
            {
              printf("\304");
              strcat(prefix,"     ");
            }
          else
            {
              printf("\302");
              strcat(prefix,"\263    ");
            }
        prettyprint(tree->left,prefix);
		*prefixend='\0';
		if (tree->right!=NULL)
          if (tree->left!=NULL)
			{
              printf("\n%s",prefix);
              printf("\300");
            }
        else printf("\304");
		strcat(prefix,"     ");
		prettyprint(tree->right,prefix);
	}
}
*/

////////////////////////////////////////////////////////////////////////////////////////// tao nut moi
node *creat(elementtype x)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->data=x;
  new->left=NULL;
  new->right=NULL;
  return new;
}

node *merge(elementtype x,node *tree1,node *tree2)
{
  node *new;
  new=creat(x);
  new->left=tree1;
  new->right=tree2;
  return new;
}
int isEmptyTree(node* tree)
{ return tree == NULL;}

node* leftChild(node* tree)
{
  if(tree != NULL) return tree->left;
  return NULL;
}

node* rightChild(node* tree)
{
  if(tree != NULL) return tree->right;
  return NULL;
}

int isLeaf(node* tree)
{
  if(tree != NULL)
    return (leftChild(tree) == NULL) && (rightChild(tree) == NULL);
  return -1;
}
//////////////////////////////////////////////////////////////////////////////// number of tree node
int nofNode(node *tree)
{
  if(tree == NULL) return 0;
  return 1 + nofNode(tree->left) + nofNode(tree->right) ;
}

int nof_leaf(node *tree)
{
  if(tree == NULL) return 0;
  if(isLeaf(tree)) return 1;
  else return nof_leaf(tree->left) + nof_leaf(tree->right);
}
//////////////////////////////////////////////////////////////////////////// add phan tu vao la tan cung ben trai
node * add_left(node **tree,elementtype x)
{
  node *new = creat(x);
  if(new == NULL) return NULL;
  if(*tree == NULL) *tree = new;
  else
    {
      node *Lnode = *tree;
      while(Lnode->left != NULL)
        Lnode = Lnode->left;
      Lnode->left = new;
    }
  return new;
}
////////////////////////////////////////////////////////////////////////// add phan tu vao la tan cung ben phai
node * add_right(node **tree,elementtype x)
{
  node *new = creat(x);
  if(new == NULL) return NULL;
  if(*tree == NULL) *tree = new;
  else
    {
      node *Rnode = *tree;
      while(Rnode->right != NULL)
        Rnode = Rnode->right;
      Rnode->right = new;
    }
  return new;
}

int max(int a, int b)
{
  return a > b ? a : b ;
}

int min(int a, int b)
{
  return a < b ? a : b ;
}

int high(node *root)
{
  if(root == NULL) return 0;
  else return 1+ max(high(root->left),high(root->right));
}

int position(node *root, node *cur)
{
  if (cur == root || root == NULL) return 0;
  else return 1 + min(position(root->left,cur),position(root->right,cur));
}
void freetree(node *tree)
{
  if (tree == NULL) return;
  free(tree->left);
  free(tree->right);
  free(tree);
  return;
}
//////////////////////////////////////////////////////////////////////////Binary Search Tree 's Function
node *insert(node *tree,elementtype x)
{
  if(tree==NULL) return creat(x);
  if(tree!=NULL)
    if (strcmp(x.word,tree->data.word) == 0)
      {
        tree->data.count ++;
        return tree;
      }
    else if(strcmp(x.word,tree->data.word) < 0)
      tree->left=insert(tree->left,x);
    else
      tree->right=insert(tree->right,x);
  return tree;
}
/*
node *search(node *tree, elementtype x)
{
  if(tree != NULL)
    if(strcmp(x.word,tree->data.word)<0)
      tree = search(tree->left,x);
    else if (strcmp(x.word,tree->data.word)>0)
      tree = search(tree->right,x);
  return tree;
}

node *find_min(node *tree)
{
  if (tree == NULL) return NULL;
  if(tree->left == NULL) return tree;
  else return find_min(tree->left);
}

node *find_max(node *tree)
{
  if(tree != NULL)
    while(tree->right != NULL)
      tree = tree->right;
  return tree;
}

node * delete(node *tree,elementtype x)
{
  node *tmp;
  if(tree == NULL) printf("Not found\n");
  else if (x < tree->data)
    tree->left = delete(tree->left,x);
  else if (x > tree->data)
    tree->right = delete(tree->right,x);
  else
    if (tree->left && tree->right)
      {
        tmp = find_min(tree->right);
        tree->data = tmp->data;
        tree->right = delete(tree->right,tree->data);
      }
    else
      {
        tmp = tree;
        if (tree->left == NULL)
          tree = tree->right;
        else if (tree->right == NULL)
          tree = tree->left;
        free(tmp);
      }
  return tree;
}
*/
