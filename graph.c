#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct node{
  int data;
  struct node *next;
} node;
typedef struct Queue{
  node *front;
  node *rear;
} queue;
void endqueue(queue *q, int data) {
  node *ptr=(node*)malloc(sizeof(node));
  ptr->next=NULL;
  ptr->data=data;
  if(q->front!=NULL) q->rear->next=ptr;
  else q->front=ptr;
  q->rear=ptr;
}
int dequeue(queue *q){
  node *ptr=q->front;
  int data=ptr->data;
  q->front=q->front->next;
  free(ptr);
  return data;
}


bool visited[1000];
node* adj[1000];

void add_last(node *head, int data){
  node *ptr=(node*)malloc(sizeof(node));
  ptr->next=NULL;

  while(head->next!=NULL) {
    head=head->next;
  }
  head->next=ptr;
  ptr->data=data;
}

void list(node *head){
  printf("head");
  while (head!=NULL) {
    printf("->[%d]",head->data);
    head=head->next;
  }
}
int read_graph(){
  FILE *fi;
  int a, b, length;
  if((fi=fopen("in.txt","r"))==NULL){
    printf("Open:\n");
    exit(1);
  }
  fscanf(fi,"%d %d", &length, &b);
  for(int i=1; i<=length; i++){
    node *ptr=(node*)malloc(sizeof(node));
    ptr->data=i;
    ptr->next=NULL;
    adj[i]=ptr;
  }

  while(fscanf(fi,"%d %d", &a, &b)!=EOF){
    add_last(*(adj+a),b);
    add_last(*(adj+b),a);
  }
  fclose(fi);
  return length;
}
void DFS(int u) {
  visited[u]=true;
  printf("%d\n",adj[u]->data);
  node *v=adj[u]->next;
  while (v!=NULL) {
    if(visited[v->data]==false) DFS(v->data);
    v=v->next;
  }
}
void BFS(int u){
  queue q;
  q.front=NULL; q.rear=NULL;
  endqueue(&q,u);
  visited[u]=true;
  while (q.front!=NULL) {
    int a=dequeue(&q);
    printf("%d ", a);
    node *v=adj[a]->next;
    while (v!=NULL) {
      if (visited[v->data]==false) {endqueue(&q,v->data); visited[v->data]=true;}
        v=v->next;
      }
    }
}


int main(){
  // adj=(node**)malloc(sizeof(node*));
  int length=read_graph();
  for(int i=1; i<=length;i++){
    visited[i]=false;
  }

  // DFS(5);
  // BFS(1);
  for(int i=1; i<=length;i++){
    list(adj[i]);
    printf("\n");
  }

  return(0);
}
