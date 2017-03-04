#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[]){
  double width,height;
  if(argc != 3){
    printf("Wrong number of argument\n");
    return 1;
  }
  width=atof(argv[1]);
  height=atof(argv[2]);
  printf("%g\n%g\n",width,height);
  printf("The rectangle's area is %g\n",width*height);
  printf("The rectangle's perimeter is %g\n",2*(width+height));
  return 0;
}
