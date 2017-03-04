#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef union{
  int i;
  long l;
  float f;
  double d;
  void *v;
  char *s;
  char c;
} Jval;

Jval new_jval_i(int);
Jval new_jval_l(long);
Jval new_jval_f(float);
Jval new_jval_d(double);
Jval new_jval_s(char *);
Jval new_jval_c(char);
Jval new_jval_v(void *);


/*====================== define functions ==========================*/
Jval new_jval_i(int i)
{
  Jval j;
  j.i = i;
  return j;
}

Jval new_jval_l(long l)
{ 
  Jval j;
  j.l = l;
  return j;
}

Jval new_jval_f(float f)
{
  Jval j;
  j.f = f;
  return j;
}

Jval new_jval_d(double d)
{
  Jval j;
  j.d = d;
  return j;
}

Jval new_jval_s(char * s)
{
  Jval j;
  j.s = s;
  return j;
}

Jval new_jval_c(char c)
{
  Jval j;
  j.c = c;
  return j;
}

Jval new_jval_v(void * v)
{
  Jval j;
  j.v = v;
  return j;
}

int jval_i(Jval j) { return j.i; }
long jval_l(Jval j) { return j.l; }
float jval_f(Jval j) { return j.f; }
double jval_d(Jval j) { return j.d; }
void *jval_v(Jval j) { return j.v; }
char jval_c(Jval j) { return j.c; }
char *jval_s(Jval j) { return j.s; }

void exch(Jval *a, int i, int j)
{
  Jval tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

int cmp_i(Jval *a, Jval *b)
{
  return (a->i-b->i);
}

void sort_gen(Jval a[], int l, int r, int (*cmp)(Jval*, Jval*))
{
  
  if (r <= l) return;

  int i = l - 1, j = r;
  int p = l - 1, q = r;

  while(1){
    while((*cmp)(&a[++i], &a[r]) < 0);
    while((*cmp)(&a[r], &a[--j]) < 0) if (j == l) break;
    if(i >= j) break;
    exch(a, i, j);
  }

  exch(a, i, r);
  j = i - 1;
  i = i + 1;
  sort_gen(a, l, j, cmp);
  sort_gen(a, i, r, cmp);

}

int search_gen(Jval a[], int l, int r, Jval item, int (*cmp)(Jval*, Jval*))
{
  int i;
  for(i = l; i <= r; i++){
    if((*cmp)(&a[i], &item) == 0) return i;
  }

  return -1;
}

void create_array_i(Jval *p, int len)
{
  int i;
  int k;
  
  srand(time(NULL));

  for(i = 0; i < len; i++){
    k = rand()%1000;
    (p)[i] = new_jval_i(k);
    //printf("%d ", Ji[i].i);
  }
  //printf("%p\n", Ji);
  //*p = Ji;
}

int main()
{
  int len = 1000;
  int key;
  int i;
  Jval Ji[len];
  create_array_i(Ji, len);
  //printf("%p\n", Ji);
  sort_gen(Ji, 0, len-1, cmp_i);
  for(i = 0; i < len; i++) printf("%d ", Ji[i].i);
  printf("\n");
  printf("Enter the number you want to search: ");
  scanf("%d", &key);
  Jval item = new_jval_i(key);
  int result = search_gen(Ji, 0, len-1, item, cmp_i);
  if(result == -1) printf("%d not found\n", key);
  else printf("%d found at %d\n", key, result);
}
