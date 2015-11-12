#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/*
La idea de este metodo es empezar en un punto aleatorio y recorrer el espacio con saltos aleatorios. Sin embargo estos saltos dependen del punto donde uno este parado. Se elige un punto nuevo alrededor de un punto actual a una distancia dada por una distribucion gausiana. Se compara P(x) con P(nuevo). Se mueve al nuevo punto con probabilidad 1-(P(x)-P(nuevo)). Es decir si P(nuevo) es mas probable, se cambia al nuevo punto. Si x es mas probable se cambia al nuevo punto con cierta probabilidad que depende de la diferencia.
*/


float *reserva(int n_puntos);
void print_array(float * array, int n_puntos, float delta_x);
void copy(float *origen, float *destino, int n_puntos);
float nastyFunction(float);
float newPoint(float);
float gaussian();



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

float gaussian(){
  float num=0;
  int j;
  for (j=0;j<12;j++)
    {
      num=num+rand(48)
    }
  return num-6;
}


void copy(float *origen, float *destino, int n_puntos){
  int i;
  for(i=0;i<n_puntos;i++){
    destino[i] = origen[i];
  }
}

void iteration(float *u_future, float *u_present, float *u_past, int n_puntos, float r){
  int i;
  for(i=1;i<(n_puntos-1);i++){
    u_future[i] = u_present[i] - delta_t/delta_x*(u_present[i+1]-u_present[i])
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

