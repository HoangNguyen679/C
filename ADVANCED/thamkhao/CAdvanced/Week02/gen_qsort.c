#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------- Jval API ------------------------------
typedef union{
  int i;
  long l;
  float f;
  double d;
  char c;
  char* str;
  void* v;
}Jval;

Jval new_jval_i(int i){Jval j; j.i = i; return j;}
Jval new_jval_l(long l){Jval j; j.l = l; return j;}
Jval new_jval_f(float f){Jval j; j.f = f; return j;}
Jval new_jval_d(double d){Jval j; j.d = d; return j;}
Jval new_jval_c(char c){Jval j; j.c = c; return j;}
Jval new_jval_str(char* str){Jval j; strcpy(j.str, str); return j;}
//Jval new_jval_v(void* v, size_t size){Jval j; memcpy(j.v, v, size); return j;}

int jval_i(Jval j){return j.i;} 
long jval_l(Jval j){return j.l;}
float jval_f(Jval j){return j.f;}
double jval_d(Jval j){return j.d;}
char jval_c(Jval j){return j.c;}
char* jval_str(Jval j){return j.str;}
void* jval_void(Jval j){return j.v;}

//-------- Functions ---------------------------------------------
void qsort_jval(Jval[], int, int, int(*cmp_fn)(Jval*, Jval*));
int bin_search(Jval[], int, int, int(*cmp_fn)(Jval*, Jval*), Jval);
void swap(Jval[], int, int);

int cmp_int(Jval*, Jval*);
int cmp_long(Jval*, Jval*);
int cmp_float(Jval*, Jval*);
int cmp_double(Jval*, Jval*);
int cmp_char(Jval*, Jval*);
int cmp_str(Jval*, Jval*);

void showArray(Jval[], int);

int main(){
  const int n = 10;
  Jval* buf = (Jval*)malloc(n * sizeof(Jval));
  Jval key;
  char tmp;
  int result;

  srand(time(NULL));
  int i;
  for(i = 0; i < n; i++){
    char c = rand()%('z'-'a')+'a';
    buf[i] = new_jval_c(c);
  }
    
  showArray(buf, n);

  printf("After sorted: \n");
  qsort_jval(buf, 0, n-1, cmp_char);
  showArray(buf, n);

  printf("Enter key: ");
  scanf("%c",&tmp);

  key = new_jval_c(tmp);
  result = bin_search(buf, 0, n-1, cmp_char, key);
  if(result == -1) printf("Not found!\n");
  else printf("Found at position %d\n", result+1);

  free(buf);
  return 0;
}

void qsort_jval(Jval buf[], int L, int R, int(*cmp_fn)(Jval*, Jval*)){
  if (R <= L) return;
  int i = L-1, j = R;
  int p = L-1, q = R;
  while(1){
    while(cmp_fn(&buf[++i], &buf[R]) < 0);
    while(cmp_fn(&buf[R], &buf[--j]) < 0) if(j == L) break;
    if( i >= j) break;
    swap(buf, i, j);
    if(cmp_fn(&buf[i], &buf[R]) == 0) swap(buf, ++p, i);
    if(cmp_fn(&buf[j], &buf[R]) == 0) swap(buf, --q, j);
  }
  swap(buf, i, R);
  j = i - 1;
  i = i + 1;
  int k;
  for( k = L; k <= p; k++) swap(buf, k, j--);
  for(k = R-1; k >= q; k--) swap(buf, k, i++);
  qsort_jval(buf, L, j, cmp_fn);
  qsort_jval(buf, i, R, cmp_fn);
}

void swap(Jval buf[], int i, int j){
  Jval tmp = buf[i];
  buf[i] = buf[j];
  buf[j] = tmp;
}

int cmp_int(Jval* j_1, Jval* j_2){
  if(j_1->i == j_2->i) return 0;
  return j_1->i > j_2->i ? 1 : -1;
}

int cmp_long(Jval* j_1, Jval* j_2){
  if(j_1->l == j_2->l) return 0;
  return j_1->l > j_2->l ? 1 : -1;
}

int cmp_float(Jval* j_1, Jval* j_2){
  if(j_1->f == j_2->f) return 0;
  return j_1->f > j_2->f ? 1 : -1;
}

int cmp_double(Jval* j_1, Jval* j_2){
  if(j_1->d == j_2->d) return 0;
  return j_1->d > j_2->d ? 1 : -1;
}

int cmp_char(Jval* j_1, Jval* j_2){
  if(j_1->c == j_2->c) return 0;
  return j_1->c > j_2->c ? 1 : -1;
}

void showArray(Jval buf[], int n){
  int i;
  for(i = 0; i < n; i++)
    printf("%c  ", jval_c(buf[i]));
  printf("\n");
}

int bin_search(Jval buf[], int L, int R, int(*cmp_fn)(Jval*, Jval*), Jval key){
  if(L > R) return -1;
  int mid = (L + R)/2;
  if(cmp_fn(&buf[mid], &key) < 0) bin_search(buf, mid+1, R, cmp_fn, key);
  else if(cmp_fn(&buf[mid], &key) > 0) bin_search(buf, L, mid-1, cmp_fn, key);
  else if(cmp_fn(&buf[mid], &key) == 0) return mid;
}
