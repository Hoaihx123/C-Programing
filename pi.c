#include "stdio.h"

float pi(int n){
  float pi=0;
  for(int i=0;i<n;i++){
     pi=pi+4.0/(1+4*i)-4.0/(3+4*i);
  }
  return pi;
}

int main(int argc, char const *argv[]) {
  printf("%.10f\n",pi(100000));
  return 0;
}
