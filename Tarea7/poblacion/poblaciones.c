#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#define USAGE "./mcmc_lotkavolterra.x n_steps n_burn"

double *reserva(int n_puntos);
void print_array(double * array, int n_puntos, double delta_x);
void copy(double *origen, double *destino, int n_puntos);
int importarDatos(double *t, double *x, double *y, char *filename);
void guardar(double *a, double *b,double *c, double *d, int n_burn, int n_iteraciones);


void mcmc(double *a, double *b, double *c, double *d, double *x, double *y, double *t, int numT,int iterMCMC);
double chi(double a, double b, double c, double d, double *x, double *y, double *t, int numT);

void RungeKutta(double a, double b, double c, double d, double *x, double *y, double x0, double y0, int iterRK);
double dX(double a, double b, double x, double y);
double dY(double c, double d, double x, double y);

double darPromedio(double *a,int n_burn, int n_iterations);
double darDesviacion(double *a,int n_burn, int n_iterations);
void imprimirResultados(char *nom, double *a, int n_burn, int n_iterations);

int main(int argc, char **argv){


  if(argc!=3){
    printf("USAGE: %s\n", USAGE);
    exit(1);
  }
  
  int n_iterations=atoi(argv[1]);
  int n_burn=atoi(argv[2]);
  int iterMCMC;
  int numT;
  int iterRK=1000;
  iterMCMC=n_iterations+n_burn;  

  printf("Logro leer entradas");
  
  double *x,*y,*t;
  double *a,*b,*c,*d;
  t=reserva(1000);
  x=reserva(1000);
  y=reserva(1000);//Se usa mucho mas espacio del necesario para no tener problemas con el numero de datos
  a=reserva(iterMCMC);
  b=reserva(iterMCMC);
  c=reserva(iterMCMC);
  d=reserva(iterMCMC);

  printf("Logro inciar arrays");

  numT=importarDatos(t,x,y,"lotka_volterra_obs.dat");
  printf("importo todo y no se quejo");

  mcmc(a,b,c,d,x,y,t,numT,iterMCMC);
  printf("Hizo mcmc y no se quejo");

  imprimirResultados("a",a,n_burn,n_iterations);
  imprimirResultados("b",b,n_burn,n_iterations);
  imprimirResultados("c",c,n_burn,n_iterations);
  imprimirResultados("d",d,n_burn,n_iterations);
  //print_array(a,iterMCMC,1);

  guardar(a,b,c,d,n_burn,n_iterations);  

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
  double *array=malloc(n_puntos*sizeof(double));
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

void guardar(double *a, double *b,double *c, double *d, int n_burn, int n_iteraciones){
  FILE *in;
  int n;
  int i;
  char filename[100]="poblaciones.dat";
  in = fopen(filename,"w");
  for(n=i;n<n_iteraciones;n++){
    i=n+n_burn;
    fprintf(in,"%f, %f, %f, %f\n",a[i], b[i], c[i], d[i]);
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
    for(i=0;i<iterRK-1;i++){

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
    
    for(i=0;i<iterMCMC-1;i++){
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
    xNew=reserva(iterRK);
    yNew=reserva(iterRK);
    RungeKutta(a,b,c,d,xNew,yNew,x[0],y[0],iterRK);
    
    double chi=0;
    int i;
    int j;
    for(i=0;i<numT;i++){
        j=(int)floor(t[i]*iterRK);
        chi=chi+pow(xNew[j]-x[i],2)+pow(yNew[j]-y[i],2);
    }
    return chi;
}
   
/*Metodos que retornan los resultados
--------------------------------------------------------------------------*/
double darPromedio(double *a, int n_burn, int n_iterations){
	double prom=0;
	int i;
	for (i=0;i<n_iterations;i++){
		prom=prom+a[i+n_burn];
	}
	return prom/n_iterations;
}

double darDesviacion(double *a, int n_burn, int n_iterations){
	double var=0;
	double prom=darPromedio(a, n_burn, n_iterations);	
	int i;
	for (i=0;i<n_iterations;i++){
		var=var+pow(a[i+n_burn]-prom,2);
	}
	var=var/n_iterations;	
	return sqrt(var);
}

void imprimirResultados(char *nom, double *a, int n_burn, int n_iterations){
	double prom=darPromedio(a,n_burn,n_iterations);
	double desv=darDesviacion(a,n_burn,n_iterations);

	printf("Valor optimo del parametro %s: %f   Incertidumbre: %f\n",nom,prom,desv);
}  




