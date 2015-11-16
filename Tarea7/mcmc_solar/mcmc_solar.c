#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#define USAGE "./mcmc_solar.x n_steps n_burn"

double *reserva(int n_puntos);
void print_array(double * array, int n_puntos, double delta_x);
void copy(double *origen, double *destino, int n_puntos);
int importarDatos(double *t, double *x, char *filename);
void guardar(double *chi,double *a, double *b,double *c, double *d, int n_burn, int n_iteraciones);
void guardarLectura(double *x, double *t, int n_iteraciones);

void mcmc(double *chi, double *a, double *b, double *c, double *d, double *x, double *t, int numT,int iterMCMC);
double chi2(double a, double b, double c, double d, double *x, double *t, int numT);

double funcion(double a, double b, double c, double d, double t);

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
  iterMCMC=n_iterations+n_burn;  
  
  double *x,*t;
  double *a,*b,*c,*d,*chi;
  t=reserva(3000);
  x=reserva(3000);//Se usa mucho mas espacio del necesario para no tener problemas con el numero de datos
  a=reserva(iterMCMC);
  b=reserva(iterMCMC);
  c=reserva(iterMCMC);
  d=reserva(iterMCMC);
  chi=reserva(iterMCMC);

  a[0]=0;
  b[0]=0;
  c[0]=0;
  d[0]=1;

  numT=importarDatos(t,x,"monthrg.dat");

  mcmc(chi,a,b,c,d,x,t,numT,iterMCMC);

  imprimirResultados("a",a,n_burn,n_iterations);
  imprimirResultados("b",b,n_burn,n_iterations);
  imprimirResultados("c",c,n_burn,n_iterations);
  imprimirResultados("d",d,n_burn,n_iterations);

  guardar(chi,a,b,c,d,n_burn,n_iterations); 
  guardarLectura(x,t,numT);

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

void guardar(double *chi, double *a, double *b,double *c, double *d, int n_burn, int n_iteraciones){
  FILE *in;
  int n;
  int i;
  char filename[100]="mcmc_solar.dat";
  in = fopen(filename,"w");
  for(n=0;n<n_iteraciones;n++){
    i=n+n_burn;
    fprintf(in,"%f %f %f %f %f\n",chi[i], a[i], b[i], c[i], d[i]);
  }
  fclose(in);
}
//Guarda los datos obsevados que se usan
void guardarLectura(double *x, double *t, int n_iteraciones){
  FILE *in;
  int n;
  char filename[100]="datosLeidos.dat";
  in = fopen(filename,"w");
  for(n=0;n<n_iteraciones;n++){
    fprintf(in,"%f %f\n", t[n], x[n]);
  }
  fclose(in);
}

int importarDatos(double *t, double *x, char *filename){
	FILE *in;
	int i=0;
	int j;
	in = fopen(filename,"r");	
	double b1,b2,b3,b4; //Variables basura
	
	for (j=0;j<190*12;j++){
	fscanf(in,"%*[^\n]\n");	//Saltar primeros 190 annos para empezar desde 1800
	}
	while(!feof(in)){
		t[i]=i*1.0/12.0;
		fscanf(in,"%lf %lf %lf %lf %lf\n",&b1,&b2,&b3,&x[i],&b4);
		i++;
	}
	fclose(in);
	return i;
}
/*Funcion
-----------------------------------------------------------------------------*/

double funcion(double a, double b, double c, double d, double t){
	return a*cos((2.0*3.14159/d)*t+b)+c;
}
    
/* Metodos del MCMC
-----------------------------------------------------------------------------*/
    
void mcmc(double *chi, double *a, double *b, double *c, double *d, double *x, double *t, int numT, int iterMCMC){
    /*Inicializa el RNG gausiano y el uniforme*/
    const gsl_rng_type * T;
    gsl_rng * r;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
    
    srand48(time(NULL));
    
    /*Otras variables*/
    double aNew,bNew,cNew,dNew, chiNew;
    double step=0.7;
    int i;
    
    for(i=0;i<iterMCMC-1;i++){
	aNew=a[i]+gsl_ran_gaussian(r, step);
        bNew=b[i]+gsl_ran_gaussian(r, step);
        cNew=c[i]+gsl_ran_gaussian(r, step);
        dNew=d[i]+gsl_ran_gaussian(r, step);
       
        chi[i]=chi2(a[i],b[i],c[i],d[i],x,t,numT);
        chiNew=chi2(aNew,bNew,cNew,dNew,x,t,numT);
	
        
	if(chiNew<chi[i]){
	    a[i+1]=aNew;
            b[i+1]=bNew;
            c[i+1]=cNew;
            d[i+1]=dNew;
	}
	else{
		double p=exp(chi[i]-chiNew);
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
  chi[i]=chi2(a[i],b[i],c[i],d[i],x,t,numT);
}

        
double chi2(double a, double b, double c, double d, double *x, double *t, int numT){
    
    double chi=0;
    int i;
    for(i=0;i<numT;i++){
        chi=chi+pow(funcion(a,b,c,d,t[i])-x[i],2);
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




