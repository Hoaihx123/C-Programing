#include "stacks.h"
#include "stdio.h"
#include "stdlib.h"

void add_head(node **head){
  node *ptr=(node*)malloc(sizeof(node));
  if (*head==NULL){
    ptr->next=NULL;
    *head=ptr;
  }
  else{
    ptr->next=*head;
    *head=ptr;
  }
}
void gotoxy(int x,int y){
    printf("%c[%d;%df",0x1B,y,x);
}
void loadSnake(node *head){
  while (head!=NULL) {
    gotoxy(head->x,head->y);
    printf("@");
    head=head->next;
  }
}
int collisionSnake(int x, int y, node *head){
  while(head!=NULL){
    if((head->x==x)&&(head->y==y)) return 1;
    head=head->next;
  }
  return 0;
}

void move(node *head, char direction){
  gotoxy(head->x,head->y);
  printf(" ");
  while(head->next!=NULL){
    head->x=head->next->x;
    head->y=head->next->y;
    head=head->next;
  }
  gotoxy(head->x, head->y);
  printf("@");
  switch(direction){
      case 0x41:
          head->y--;
          break;
      case 0x42:
          head->y++;
          break;
      case 0x43:
          head->x++;
          break;
      case 0x44:
          head->x--;
          break;
  }
  gotoxy(head->x,head->y);
  printf("8");
  gotoxy(1,1);
  return;
}
