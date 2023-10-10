#include "stdio.h"
#include "stdlib.h"
#include "stacks.h"

void push(node1 **stack, float data){
  node1 *ptr=(node1*)malloc(sizeof(node1));
  if (stack==NULL){
    ptr->data=data;
    ptr->next=NULL;
    *stack=ptr;
  }
  else{
    ptr->data=data;
    ptr->next=*stack;
    *stack=ptr;
  }
}
int is_empty(node1 *stack){
  return stack==NULL;
}
float pop(node1 **stack){
  float item;
  node1 *ptr=(node1*)malloc(sizeof(node1));
  if (is_empty(*stack)){
    printf("stack is empty\n");
  }
  else{
    ptr=*stack;
    item=(*stack)->data;
    *stack=(*stack)->next;
    free(ptr);
    return item;
  }
  return 0;
}
float top(node1 *stack){
  return stack->data;
}

void drop(node1 **stack) {
  node1 *ptr=(node1*)malloc(sizeof(node1));
  ptr=*stack;
  *stack=(*stack)->next;
  free(ptr);
}
