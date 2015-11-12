#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define USAGE "./montecarlo valor"

double integrando(double x)
{
  return  exp(-1*pow(x,2));
}

int main(int argc, char **argv){
  float h;

  if(argc!=2){
    printf("USAGE: %s\n", USAGE);
    exit(1);
  }
  
  h = atof(argv[1]);
  double n=0.0;
  double respuesta=0.0;
  double mu=0.0;
  double varia=0.0;
  time_t t;
  srand((unsigned) time(&t));


  while(varia>=pow(h,2) || n<100)
   {
     double x=5*(((double)rand()/(double)RAND_MAX));
    respuesta=(respuesta*n+10*integrando(x))/(n+1);
    varia=((varia+pow(mu,2))*n+pow(respuesta,2))/(n+1)-	pow((mu*n+respuesta)/(n+1),2);
    mu=(mu*n+respuesta)/(n+1);
    n+=1;
    
   }

  printf("Numero de iteraciones: %g Respuesta: %g\n",n, respuesta);

  return 0;
}
