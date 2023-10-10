#include "stdio.h"
#include "stdlib.h"
typedef struct Node{
  unsigned int k;
  struct Node *next;
} type_L;

void add_head(type_L **L, unsigned int k){
  type_L *p = NULL;
  if((p=(type_L*)malloc(sizeof(type_L)))==NULL){
    perror("malloc");
    exit(1);
  }
  p->k=k;
  if(*L==NULL) p->next=NULL;
  else p->next=*L;
  *L=p;
}
void swapl(char *s){
  while (*s!='\0') {
    if(*s>=97&&*s<=122) *s-=32;
    else if(*s>=65&&*s<=90) *s+=32;
    s++;
  }
}

unsigned long int amean(type_L *L){
  unsigned long int s = 0;
  int i=0;
  if(L==NULL) return -1;
  while (L!=NULL) {
    s=s+L->k;
    L=L->next;
    i++;
  }
  return s/i;
}
int main(int argc, char const *argv[]) {
  // type_L *L=NULL;
  // add_head(&L,5);
  // add_head(&L,50);
  // printf("%ld\n", amean(L));


int c[]= {1,2,3,5};
// swapl(c);
printf("%d\n",*(c+2));

}
