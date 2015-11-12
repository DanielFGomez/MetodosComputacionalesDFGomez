#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


float *reserva(int n_puntos);
void print_array(float * array, int n_puntos, float delta_x);
void copy(float *origen, float *destino, int n_puntos);
float fun(float);
float newPoint(float);
float gaussian();
float chi(double a, double b, double c, double d);
void iterar()


int main(){
  int n_iterations=100;
  float *camino;
  srand48(time(NULL));

  camino = reserva(n_iterations+1);
  camino[0] = rand48()*8.0-4.0;
  

  double xNew;
  double alpha;
  double beta;
  int i;
  for (i=0; i<n_iterations; i++){
    xNew=newPoint(camino[i]);
    alpha=nastyFunction(xNew)/nastyFunction(camino[i]);
    if(alpha>=1){
      camino[i+1]=xNew;
    }
    else{
      beta=rand48();
      if(beta<=alpha){
	camino[i+1]=xNew;
      }
      else{
	camino[i+1]=camino[i];
      }
    }


  }


  return 0;
}

void copy(float *origen, float *destino, int n_puntos){
  int i;
  for(i=0;i<n_puntos;i++){
    destino[i] = origen[i];
  }
}


void print_array(float * array, int n_puntos, float delta_x){
  int i;
  for(i=0;i<n_puntos;i++){
    printf("%f %f\n", delta_x*i, array[i]);
  }
}

float *reserva(int n_puntos){
  float *array;
  int i;
  if(!(array = malloc(n_puntos * sizeof(float)))){
    printf("Problema en reserva\n");
    exit(1);
  }
  for(i=0;i<n_puntos;i++){
    array[i] = 0.0;
  }
  return array;
}

float *importarDatos(){
  FILE *in;
  int i;
  int var;
  int N;

  in=fopen(filename,"w");
  if(!in){
    printf("problems opening the file %s\n", filename);
    exit(1);
  }

  for (i=0;i<N;i++){
    fscanf(in,"%d\n",&var);
   }

  fclose(in);

}

float gaus(){
  int i;
  float random;
  const gsl_rng_type * T;
  gsl_rng * r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);
  random = gsl_ran_gaussian(r, 0.1);
  gsl_rng_free (r);
  return random;
}

void iterar(){
  int i;
  for (i=0;i<nIteraciones+nBurn;n++)
    {
      float new=x+gaus();
      if(chi

}
