import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('salida.dat')

#make a simple figure
fig = plt.figure()
ax = plt.axes()
ax.set_xlabel("x")
ax.set_ylabel("f(x)")
ax.set_title("Soluciones")

plt.scatter(data[:,0],data[:,1], label="Ultimo timestep")
ax.legend()

filename = 'solucion' 
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()
