#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "stacks.h"

/* приоритет */
int priority(char x){
  if (x=='.') return 4;
  else if (x=='^') return 3;
  else if (x=='*'||x=='/'||x=='%') return 2;
  else if (x=='+'||x=='-') return 1;
  else if (x=='(') return 0;
  else return -1;
}
float calculateValue(float a, char x, float b){
  float result;
  if(x=='.')  return a+b;
  if(x=='^') result=pow(a,b);
  if (x=='*') result=a*b;
  if (x=='/') result=a/b;
  if (x=='%') result=(int)a%(int)b;
  if (x=='+') result=a+b;
  if (x=='-') result=a-b;
  printf("%f%c%f=%f\n",a,x,b,result);
  return result;
}
int check(char x){
  if(x=='+'||x=='-'||x=='*'||x=='%'||x=='/'||x=='^'||x=='.') return 2;
  else if((x-'0'<10)&&(x-'0')>=0) return 1;
  else if(x=='('||x==')') return 0;
  else{
    printf("syntax incorrect input expression\n");
    exit(1);
  }
}
/*----------------------------------*/

float calculate(int n, char c[]){
  node1 *stack1=NULL;
  node2 *stack2=NULL;
  if(check(c[n-1])==2||c[n-1]=='(') printf("syntax incorrect input expression\n");
  for (int i=0;i<n;i++) {
    if(check(c[i])==1){
      int count =10;
      push(&stack1,c[i]-'0');
      if(i+1<n){
         i++;
         while (check(c[i])==1) {
           count=10*count;
           push(&stack1,pop(&stack1)*10+c[i]-'0');
           if(i+1<n) i++;
           else break;
         }
      }
      if(!is_empty2(stack2)){
        if(top2(stack2)=='.') push(&stack1,pop(&stack1)/count);
      }
    }
    if(c[i]=='(') push2(&stack2,c[i]);
    if(check(c[i])==2){
      while (!is_empty2(stack2)&&priority(c[i])<=priority(stack2->c)) {
        float a = pop(&stack1);
        float x =calculateValue(pop(&stack1),pop2(&stack2),a);
        push(&stack1,x);
      }
      push2(&stack2,c[i]);
    }
    if (c[i]==')') {
      while (stack2->c!='(') {
        float a=pop(&stack1);
        push(&stack1,calculateValue(pop(&stack1),pop2(&stack2),a));
      }
      pop2(&stack2);
    }
  }
  while (!is_empty2(stack2)) {
    if(top2(stack2)=='(') pop2(&stack2);
    else{ float a=pop(&stack1);
    float x=calculateValue(pop(&stack1),pop2(&stack2),a);
    push(&stack1,x);}
  }
  return pop(&stack1);
}


int main(int argc, char const *argv[]) {
  char c[256];

  while (1) {
    fgets(c,256,stdin);
    int n=0;
    while (c[n]!='\0') {
      n++;
    }
    if (n==1) break;
    printf("=>result=%f\n", calculate(n-1,c));
   }

  return 0;
}
