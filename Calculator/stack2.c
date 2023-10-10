#include "stacks.h"
#include "stdio.h"
#include "stdlib.h"

void push2(node2 **stack, char c){
  node2 *ptr=(node2*)malloc(sizeof(node2));
  if (stack==NULL){
    ptr->c=c;
    ptr->next=NULL;
    *stack=ptr;
  }
  else{
    ptr->c=c;
    ptr->next=*stack;
    *stack=ptr;
  }
}
int is_empty2(node2 *stack){
  return stack==NULL;
}
char pop2(node2 **stack){
  int item;
  node2 *ptr=(node2*)malloc(sizeof(node2));
  if (is_empty2(*stack)){
    printf("stack is empty\n");
    return (*stack)->c;
  }
  else{
    ptr=*stack;
    item=(*stack)->c;
    *stack=(*stack)->next;
    free(ptr);
    return item;
  }
}
char top2(node2 *stack){
  return stack->c;
}

void drop2(node2 **stack) {
  node2 *ptr=(node2*)malloc(sizeof(node2));
  ptr=*stack;
  *stack=(*stack)->next;
  free(ptr);
}
