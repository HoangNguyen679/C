#include<stdio.h>
int main()
{
  int ma;
  printf("\n Go vao ma trinh do: ");
  scanf("%d",&ma);
  if(ma==1)
    printf("\n Trinh do trung cap ");
  else if (ma==2)
    printf("\n Trinh do cao dang");
  else if (ma==3)
    printf("\n Trinh do dai hoc ");
  else
    printf("\n Nhap ma sai ");
  return 0;
}
