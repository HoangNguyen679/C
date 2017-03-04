/* phuong phap sinh ra tap con m phan tu tu tap n phan tu
tap n phan tu lien tiep tu 1 -> n
tap m phan tu 1 -> m
tim tu ben phai sang
tim phan tu a[i] != n - m + i
a[i] = a[i] + 1
j chay tu i + 1 -> m, a[j] = a[j] + j - i
*/

#include <stdio.h>
#include <string.h>

int main()
{
  int n,m;
  printf("Nhap n: ");scanf("%d",&n);
  printf("Nhap m: ");scanf("%d",&m);

  int i,t = 1;
  int a[n];
  for(i = 0; i < m; i++)
    a[i] = t++;
  printf("\n");

  int k = 0;
  while(k != 1)
    {
      for(i = 0; i < m; i++)
	printf("%d\t",a[i]);
      printf("\n");
      {
	int j,r;
	j = m - 1;
	while(a[j] == n - m + j) j--;
	if(j < 0) k = 1;
	else
	  {
	    a[j]++;
	    for(r = j + 1; r < m; r++)
	      a[r] = a[r] + r - j;
	  }
	
      }
      
    }
  return 0;
}
