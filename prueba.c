#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int importarDatos(double *t, double *x, double *y, char *filename){
	FILE *in;
	int i=0;
	in = fopen(filename,"r");
	
	fscanf(in,"%*[^\n]\n");	//Saltar primera linea
	while(!feof(in)){
		fscanf(in,"%lf %lf %lf\n",&t[i],&x[i],&y[i]);
		i++;
	}
	fclose(in);
	return i;
}

void print_array(double * array, int n_puntos, double delta_x){
  int i;
  for(i=0;i<n_puntos;i++){
    printf("%f %f\n", delta_x*i, array[i]);
  }
}

double *reserva(int n_puntos){
  double *array;
  int i;
  if(!(array = malloc(n_puntos * sizeof(double)))){
    printf("Problema en reserva\n");
    exit(1);
  }
  for(i=0;i<n_puntos;i++){
    array[i] = 0.0;
  }
  return array;
}
int main(){
  double *x,*y,*t;
  x=reserva(1100);
  y=reserva(1100);
  t=reserva(1100);
  int i;
  i=importarDatos(t,x,y,"lotka_volterra_obs.dat");
  print_array(x,11,1);
  printf("%d",i);

  return 0;
}

