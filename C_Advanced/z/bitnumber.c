/* su dung phuong phap sinh liet ke day nhi phan
duyet day tu phai sang trai 
gap so 0 dau tien thi doi thanh 1
sau do tat ca nhung so ben trai so vua doi chuyen thanh 0
in ra so
 */

#include <stdio.h>
#include <string.h>

int main()
{
  int n;
  printf("\nDo dai day: ");
  scanf("%d",&n);
  
  int a[n]  ;
  int i,k = 0;
  memset(a,0,sizeof(a));
  while(k != 1)
    {
      for(i = 0; i < n ; i++)
	printf("%d",a[i]);
      printf("\n");

      {
	int j;
	j = n - 1;
	while(j >= 0 && a[j] == 1)	  
	    a[j--] = 0;
	if(j < 0)  k = 1;
	else a[j] = 1;
      }
      
    }
  return 0;
}
