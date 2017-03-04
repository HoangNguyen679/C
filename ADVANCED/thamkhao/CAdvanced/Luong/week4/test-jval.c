#include<stdio.h>
#include<stdlib.h>
#include"jval.h"
#include"jrb.h"
#include"luong.h"

int main()
{
  JRB myJ = make_jrb();
  JRB nod;
  Jval tmp = new_jval_i(5);
  char *key = "luong";
  jrb_insert_str(myJ, key, tmp);
  tmp = new_jval_i(4);
  jrb_insert_str(myJ, key, tmp);
  jrb_traverse(nod, myJ){
    printf("%d ", jval_i(nod->val));
  }
}
