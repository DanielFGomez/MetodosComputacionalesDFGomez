#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define USAGE "factorial a"

double integrando(double c, double z)
{
  return  exp(c*(log(c*z/(1-z))-z/(1-z)))*c*pow(1/(1-z),2);
}

int main(int argc, char **argv){
  float valor;

  if(argc!=2){
    printf("USAGE: %s\n", USAGE);
    exit(1);
  }
  
  valor = atof(argv[1]);
  double c=valor-1.0;
  double n=100000;
  double delta=1/n;
  double i;
  double respuesta=0;

  for (i=0;i<=1;i=i+delta)
  {
	respuesta=respuesta+delta*integrando(c,i);	
  }


  printf("Respuesta: %g\n", respuesta);

  return 0;
}
