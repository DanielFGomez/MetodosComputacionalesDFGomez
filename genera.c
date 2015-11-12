#include <stdio.h>
#include <stdlib.h>

void genera_puntos(float *x,int n_points)
{
  int i;
  for(i=0;i<n_points;i++)
    {
      x[i]=drand48();
    }
}

void imprime_puntos(*x)
{
  int i;
  for (i=0;i<n_points;i++)
     {
       printf(x[i]);
     }
}


main()
{
  int n_points=100;
  float *x;
  x=malloc(n_points * sizeof(float));
  genera_puntos(&x,n_points);
  imprime_puntos(&x,n_points);
  return 0;
}

