solucion.pdf : simple_matplotlib.py salida.dat
	python simple_matplotlib.py

salida.dat : a.out
	./a.out > salida.dat

a.out : solve_wave.c
	cc solve_wave.c -lm

clean:
	rm -f a.out salida.dat solucion.pdf

#comentarios
