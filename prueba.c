#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(){
  double x;
 
  srand48(time(NULL));
  x=drand48();

  printf("%f \n",x);
  x=drand48();
  printf("%f \n",x);
  return 0;
}
