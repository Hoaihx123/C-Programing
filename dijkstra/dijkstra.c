#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define INT_MAX 2147483647
typedef struct node{
  int data;
  int weight;
  bool unmaked;
  struct node *next;
} node;


node* adj[1000];

void add_last(node *head, int data, int weight){
  node *ptr=NULL;
  if((ptr=(node*)malloc(sizeof(node)))==NULL){
    perror("malloc");
    exit(1);
  };
  ptr->next=NULL;

  while(head->next!=NULL) {
    head=head->next;
  }
  head->next=ptr;
  ptr->data=data;
  ptr->weight=weight;
}
void list(node *head){
  printf("head");
  while (head!=NULL) {
    printf("->[%d]:length: %d",head->data,head->weight);
    head=head->next;
  }
}
int read_graph(char file[]){
  FILE *fi;
  int a, b, length, c;
  if((fi=fopen(file,"r"))==NULL){
    printf("Open:\n");
    exit(1);
  }
  fscanf(fi,"%d", &length);
  for(int i=1; i<=length; i++){
    node *ptr=(node*)malloc(sizeof(node));
    ptr->data=i;
    ptr->weight=0;
    ptr->unmaked=true;
    ptr->next=NULL;
    adj[i]=ptr;
  }
  while(fscanf(fi,"%d %d %d", &a, &b, &c)!=EOF){
    add_last(*(adj+a),b,c);
    add_last(*(adj+b),a,c);
  }
  fclose(fi);
  return length;
}
int min(int a[], int length){
  int min=INT_MAX;
  int index=-1;
  for(int i=0;i<length;i++){
    if((a[i]<min)&&(adj[i+1]->unmaked)) {min=a[i];index=i;}
  }
  return index;
}
void dijsktra(int length, int u, int v){
  int distance[length];
  for(int i=0; i<length;i++){
    distance[i]=INT_MAX;
  }
  distance[u-1]=0;
  int ticks[length];
  ticks[u-1]=0;
  int a;
  while (((a=min(distance,length))!=-1)&&(a!=v-1)) {
    adj[a+1]->unmaked=false;
    node *ptr=adj[a+1]->next;
    while (ptr!=NULL) {
      if(adj[ptr->data]->unmaked){
        if(distance[ptr->data-1]>distance[a]+ptr->weight){
          distance[ptr->data-1]=distance[a]+ptr->weight;
          ticks[ptr->data-1]=a+1;
        }
      }
      ptr=ptr->next;
    }
  }
  if(a==v-1){
    int i=v;
    printf("%d <- ",v );
    while (i!=u) {
      i=ticks[i-1];
      printf("%d <- ", i);
    }
    printf("с наименьшей длиной: %d\n", distance[v-1]);
  }
  else{
    printf("несвязный граф");
  }
}

int main(int argc, char *argv[]) {
  if(argc>1){
    int length=read_graph(argv[1]);
    int m, n;
    printf("введите 2 вершины m,n\n");
    scanf("%d %d",&m,&n);
    if(m>length||n>length){printf("такого вершины нет"); exit(1);}
    dijsktra(length, m,n);
  }
  else printf("нужно ввести адрес входного файла\n");

  return(0);
}
