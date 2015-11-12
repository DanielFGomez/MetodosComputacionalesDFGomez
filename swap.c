#include <stdio.h>

void swap(int *a,int *b){
  int temp=*a;
  *a=*b;
  *b=temp;
}


int main(){
  int a=5;
  int b=1;
  printf("a= %d b= %d\n",a,b);
  swap(&a,&b);

  printf("a= %d b= %d\n",a,b);
}
