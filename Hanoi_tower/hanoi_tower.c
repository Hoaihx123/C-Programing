#include "stdio.h"
#include "stdlib.h"
#include "stacks.h"

typedef struct pow{
  char name;
  node* stack;
} pow;

void creat_power(int n, pow *power) {
  for(int i=n;i>0;i--){
    push(&(power->stack),i);
  }
}

void power(int n, pow *power1, pow *power2, pow *power3){
  if(n==1){
    printf("[%c]->[%c]\n",power1->name,power3->name);
    push(&(power3->stack),pop(&(power1->stack)));
    return ;
  }
  else{
    power(n-1,power1,power3,power2);
    power(1,power1,power2,power3);
    power(n-1,power2,power1,power3);
  }
}


int main(int argc, char const *argv[]) {
  pow *power1=(pow*)malloc(sizeof(pow));
  pow *power2=(pow*)malloc(sizeof(pow));
  pow *power3=(pow*)malloc(sizeof(pow));
  power1->name='A';
  power2->name='B';
  power3->name='C';
  int n;
  printf("Input n =");
  scanf("%d",&n);
  creat_power(n, power1);
  printf("----stack1-------\n");
  list(power1->stack);
  power(n, power1,power2,power3);
  printf("----stack1-------\n");
  list(power1->stack);
  printf("----stack2-------\n");
  list(power2->stack);
  printf("----stack3-------\n");
  list(power3->stack);
  return 0;
}
