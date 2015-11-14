#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

double *reserva(int n_puntos);
void print_array(double * array, int n_puntos, double delta_x);
void copy(double *origen, double *destino, int n_puntos);
void importarDatos(double *t, double *x, double *y, char *filename);
void guardar(double *x, double *y);


void mcmc(double *a, double *b, double *c, double *d, double *x, double *y, double *t, int numT,int iterMCMC);
double chi(double a, double b, double c, double d, double *x, double *y, double *t, int numT);

void RungeKutta(double a, double b, double c, double d, double *x, double *y, double x0, double y0, int iterRK);
double dX(double a, double b, double x, double y);
double dY(double c, double d, double x, double y);


int numT;

int main(int argc, char **argv){


  int n_iterations=atoi(argv[1]);
  int n_burn=atoi(argv[2]);
  double *x,*y;
  double a,b,c,d;
  importarDatos(x,y,"lotka_volterra_obs.dat");
  a=b=c=d=1;
  x=reserva(1000);
  y=reserva(1000);
  RungeKutta(a,5,12,6,x,y,13,16,1000);
  print_array(y,22,1);

  guardar(x,y);

  
}

/*Metodos Auxiliares
-----------------------------------------------------------------------------*/
void copy(double *origen, double *destino, int n_puntos){
  int i;
  for(i=0;i<n_puntos;i++){
    destino[i] = origen[i];
  }
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
/*OJO cambiar despues de probar que funcione la EQdiff*/
void guardar(double *x, double *y){
  FILE *in;
  int n;
  char filename[100]="poblaciones.dat";
  in = fopen(filename,"w");
  double t;
  for(n=0;n<=1000;n++){
    t=n*0.001;
    fprintf(in,"%f, %f, %f\n",t, x[n],y[n]);
  }
  fclose(in);
}

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
/*Metodos de la ecuacion diferencial
-----------------------------------------------------------------------------*/

double dX(double a, double b, double x, double y){
    return x*(a-b*y);   
}
double dY(double c, double d, double x, double y){
    return -y*(c-d*x);
}

void RungeKutta(double a, double b, double c, double d, double *x, double *y, double x0, double y0, int iterRK){
    double xk1,xk2,xk3,xk4,yk1,yk2,yk3,yk4;
    double dt=1.0/iterRK;
    x[0]=x0;
    y[0]=y0;
    
    int i;
    for(i=0;i<iterRK;i++){

        /*Parte 1*/
        xk1=dX(a,b,x[i],y[i])*dt;
        yk1=dX(c,d,x[i],y[i])*dt;
    
        /*Parte 2*/
        xk2=dX(a,b,x[i]+0.5*xk1,y[i]+0.5*yk1)*dt;
        yk2=dY(c,d,x[i]+0.5*xk1,y[i]+0.5*yk1)*dt;
    
        /*Parte 3*/
        xk3=dX(a,b,x[i]+0.5*xk2,y[i]+0.5*yk2)*dt;
        yk3=dY(c,d,x[i]+0.5*xk2,y[i]+0.5*yk2)*dt;
    
        /*Parte 4*/
        xk4=dX(a,b,x[i]+xk3,y[i]+yk3)*dt;
        yk4=dY(c,d,x[i]+xk3,y[i]+yk3)*dt;
    
        /*Parte Final*/
        x[i+1]=x[i]+(xk1+2*xk2+2*xk3+xk4)/6.0;
        y[i+1]=y[i]+(yk1+2*yk2+2*yk3+yk4)/6.0;
    }
  print_array(y,22,1);
}
    
/* Metodos del MCMC
-----------------------------------------------------------------------------*/
    
void mcmc(double *a, double *b, double *c, double *d, double *x, double *y, double *t, int numT, int iterMCMC){
    /*Inicializa el RNG gausiano y el uniforme*/
    const gsl_rng_type * T;
    gsl_rng * r;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
    
    srand48(time(NULL));
    
    /*Otras variables*/
    double aNew,bNew,cNew,dNew,chiOld, chiNew;
    double step=0.1;
    int i;
    
    for(i=0;i<=iterMCMC;i++){
        aNew=a[i]+gsl_ran_gaussian(r, step);
        bNew=b[i]+gsl_ran_gaussian(r, step);
        cNew=c[i]+gsl_ran_gaussian(r, step);
        dNew=d[i]+gsl_ran_gaussian(r, step);
        
        chiOld=chi(a[i],b[i],c[i],d[i],x,y,t,numT);
        chiNew=chi(aNew,bNew,cNew,dNew,x,y,t,numT);
        
        double p=exp(chiOld-chiNew);
        if(p>drand48()){
            a[i+1]=aNew;
            b[i+1]=bNew;
            c[i+1]=cNew;
            d[i+1]=dNew;
        }
        else{
            a[i+1]=a[i];
            b[i+1]=b[i];
            c[i+1]=c[i];
            d[i+1]=d[i];
	}
    }
}

        
double chi(double a, double b, double c, double d, double *x, double *y, double *t, int numT){
    double *xNew, *yNew;
    int iterRK=1000;
    RungeKutta(a,b,c,d,xNew,yNew,x[0],y[0],iterRK);
    
    double chi=0;
    int i;
    int j;
    for(i=0;i<=numT;i++){
        j=(int)floor(t[i]*iterRK);
        chi=chi+pow(xNew[j]-x[i],2)+pow(yNew[j]-y[i],2);
    }
    return chi;
}
    
