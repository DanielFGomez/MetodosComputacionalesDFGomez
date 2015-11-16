n_steps:=12000
n_burn:=4000
all:graficarSolar.py mcmc_solar.dat
	python graficarSolar.py

mcmc_solar.dat:mcmc_solar.x
	./mcmc_solar.x $(n_steps) $(n_burn)

mcmc_solar.x:mcmc_solar.c
	cc mcmc_solar.c -lgsl -lgslcblas -lm -o mcmc_solar.x
