#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"luong.h"

typedef struct {
  char name[50];
  char phone[12];
}PhoneBook;

void exch(void *base, int p, int q, size_t size)
{
  int i;
  char *base2 = (char *) base;

  for(i=0;i<size;i++){ 
    char tmp=base2[size*p+i];
    base2[size*p+i]=base2[size*q+i];
    base2[size*q+i]=tmp; 
  }
}

int cmp_name(const void *a, const void *b)
{
  return strcmp(((PhoneBook*)a) -> name, ((PhoneBook*)b) -> name);
}

int cmp_phone(const void *a, const void *b)
{
  return strcmp(((PhoneBook*)a) -> phone, ((PhoneBook*)b) -> phone);
}

void sort3way(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
{
  int r = nmemb/size-1; /* offset of the last element from base */
  int l = 0;
  if (nmemb <= size) return;

  char *base2 = (char *) base;
  int i = l - 1, j = r;
  int p = l - 1, q = r;
  int k;

  while(1){
    /* look for one that is greater than the last one */
    while((*cmp)(&base2[++i*size], &base2[r*size]) < 0);
    /* look for one that is smaller than the last one */
    while((*cmp)(&base2[r*size], &base2[--j*size]) < 0) if (j == l) break;
    if(i >= j) break; /* no pair found */
    /* exchange element i and j */
    exch(base2, i, j, size);
    /* if element i is equal the last element, exchange it to the begining of the array */
    if(cmp(&base2[i*size], &base2[r*size]) == 0) exch(base2, ++p, i, size);
    /* if element j is equal the last element, exchange it  to the r-1 th position */
    if(cmp(&base2[j*size], &base2[r*size]) == 0) exch(base2, --q, j, size);
  }

  /* put r-th element to the right position */
  exch(base2, i, r, size);
  j = i - 1;
  i = i + 1;
  /* move the elements that are equal to pivot to the middle */
  for(k = l; k <= p; k++) exch(base2, k, j--, size);
  for(k = r-1; k >= q; k--) exch(base2, k, i++, size);
  /* recursively call function */
  sort3way(base2, (j+1)*size, size, cmp);
  /* move base2 to i+1-th positon */
  sort3way(&base2[(i)*size], (r-i+1)*size, size, cmp);

}

int loadData(PhoneBook **b, char *fileName)
{
  FILE *f;
  int i;
  char buffer[500];
  char tokens[2][200];
  /* count the number of lines in the file */
  int nline = countLine(fileName);
  /* allocate memory for the phonebook */
  PhoneBook *book =  (PhoneBook *) malloc(sizeof(PhoneBook)*nline);

  f = fopen(fileName, "r");
  for(i = 0; i< nline; i++){
    fgets(buffer, 500, f);
    getTokens(buffer, tokens, '-');
    strcpy(book[i].name, tokens[0]);
    strcpy(book[i].phone, tokens[1]);
  }
  
  fclose(f);

  *b = book;
  
  return nline;
}

void displayBook(PhoneBook *b, int len)
{
  int i;
  printf("%-30s%-15s\n", "Name", "Phone");
  for(i = 0; i < len; i++){
    printf("%-30s%-15s\n", b[i].name, b[i].phone);
  }
}

int main()
{
  PhoneBook *book;
  int choice;
  int len = loadData(&book, "contact.txt");
  //Display the phonebook
  displayBook(book, len);
  //size of phonebook
  printf("Choose 1 to sort the record by name, 2 to sort the record by phone number\n");
  scanf("%d", &choice);

  if(choice == 1)
    sort3way(book, len*sizeof(PhoneBook), sizeof(PhoneBook), cmp_name);
  else
    sort3way(book, len*sizeof(PhoneBook), sizeof(PhoneBook), cmp_phone);
  
  displayBook(book, len);
}
