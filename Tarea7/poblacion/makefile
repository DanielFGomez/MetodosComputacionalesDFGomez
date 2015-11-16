n_steps:=75000
n_burn:=15000
all:graficar.py poblaciones.dat
	python graficar.py
poblaciones.dat:mcmc_lotkavolterra.x
	./mcmc_lotkavolterra.x $(n_steps) $(n_burn)

mcmc_lotkavolterra.x:poblaciones.c
	cc poblaciones.c -lgsl -lgslcblas -lm -o mcmc_lotkavolterra.x
