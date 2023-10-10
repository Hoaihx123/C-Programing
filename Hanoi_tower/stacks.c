#include "stacks.h"
#include "stdio.h"
#include "stdlib.h"

void push(node **stack, int data){
  node *ptr=(node*)malloc(sizeof(node));
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
int is_empty(node *stack){
  return stack==NULL;
}
int pop(node **stack){
  int item;
  node *ptr=(node*)malloc(sizeof(node));
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
  return -1;
}
int top(node *stack){
  printf("top->data=%d\n",stack->data);
  return stack->data;
}

void drop(node **stack) {
  node *ptr=(node*)malloc(sizeof(node));
  ptr=*stack;
  *stack=(*stack)->next;
  free(ptr);
}
void list(node *stack){
  if(stack==NULL){
    printf("stack is empty\n");
    return;
  }
  while(stack!=NULL){
    printf("data %d\n", stack->data);
    stack=stack->next;
  }
}
