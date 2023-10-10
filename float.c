#include "stdio.h"
union num{
  unsigned int inum;
  float fnum;
};
void printb(unsigned int a){
  for(int i=31;i>=0;i--){
    (a&(unsigned int)1<<i)!=0?printf("1"):printf("0");
    if(i==31||i==23) printf(" ");
  }
}
int main(int argc, char const *argv[]) {
  union num n1;
  n1.fnum=3.14;
  printf("%d\n",n1.inum );
  printb(n1.inum);
  return 0;
}
