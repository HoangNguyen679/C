/* Nguyen Duc Hoang - 9A */
// Date Create: 25/03/2015
#include<stdio.h>
main()
{
  int i,j,k,n;
  printf("Nhap n: ");
  scanf("%d",&n);
  printf("Hinh thoi co chieu cao 2%d-1 la\n",n);
  for ( i=1;  i<=n; i++)
    { for (k=1;k<=(n-i);k++) printf("  ");
      for (j=1;j<2*i;j++) printf("* ");
      printf("\n");
    }
  for ( i=n-1;  i>=1; i--)
    { for (k=1;k<=(n-i);k++) printf("  ");
      for (j=1;j<2*i;j++) printf("* ");
      printf("\n");
    }
  printf("Tam giac can co chieu cao %d la\n",n);
  for ( i=1;  i<=n; i++)
    { for (k=1;k<=(n-i);k++) printf("  ");
      for (j=1;j<2*i;j++) printf("* ");
      printf("\n");
    }
}
