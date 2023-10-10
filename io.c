#include "stdio.h"
#include "stdlib.h"


int main(){
  FILE *fi, *fo;
  int a, b;
  if((fi=fopen("in.txt","r"))==NULL){
    printf("Open:\n");
    exit(1);
  }
  fo=fopen("out.txt","w");
  fscanf(fi,"%d %d", &a, &b);
  printf("%d %d\n", a, b);
  fprintf(fo, "%d\n",b );
  // while((b=getc(fi))!=EOF){
  //   fprintf(fo,"%c",b);
  // }
  fclose(fi);
  fclose(fo);
  return(0);
}
