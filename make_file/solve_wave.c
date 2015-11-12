#include <stdio.h>
#include <stdlib.h>
#include <math.h>
float *reserva(int n_puntos);
void print_array(float * array, int n_puntos, float delta_x);
void set_initial(float *array, int n_puntos, float delta_x);
void first_iteration(float *u_future, float *u_initial, int n_puntos, float r);
void iteration(float *u_future, float *u_present, float *u_past, int n_puntos, float r);
void copy(float *origen, float *destino, int n_puntos);
int main(){
  float *u_initial;
  float *u_past;
  float *u_present;
  float *u_future;
  int n_points=1000;
  int n_time=1000;
  float delta_t=0.0005;
  float delta_x=1.0/n_points; 
  float r=delta_t / delta_x;
  int j;
  u_initial = reserva(n_points);
  u_past = reserva(n_points);
  u_present = reserva(n_points);
  u_future = reserva(n_points);
  set_initial(u_initial, n_points, delta_x);
  first_iteration(u_future, u_initial, n_points, r);

  copy(u_initial, u_past, n_points);
  copy(u_future, u_present, n_points);

  for(j=1;j<n_time;j++){
    iteration(u_future, u_present, u_past, n_points, r);
    copy(u_present, u_past, n_points);
    copy(u_future, u_present, n_points);
  }
    print_array(u_future, n_points, delta_x);

  return 0;
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
    u_future[i] = (2.0*(1.0-r*r))*u_present[i] - u_past[i] + 
      (r*r)*(u_present[i+1] +  u_present[i-1]);
  }
}

void first_iteration(float *u_future, float *u_initial, int n_puntos, float r){
  int i;  
  for(i=1;i<(n_puntos-1);i++){
    u_future[i] = u_initial[i] + 
      (r*r/2.0) * (u_initial[i+1] - 2.0 * u_initial[i] + u_initial[i-1]);
  }
}
void set_initial(float *array, int n_puntos, float delta_x){
  int i;
  float x;
  for(i=0;i<n_puntos;i++){
    x = i * delta_x;
    array[i] = exp(-((x-0.3)*(x-0.3))/0.01);
  }
  array[0] = 0.0;
  array[n_puntos-1] = 0.0;
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
