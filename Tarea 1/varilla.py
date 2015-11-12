import numpy as np
import matplotlib.pyplot as plt

#L es la longitud de la varilla
#resolucion es la cantidad de puntos para el plot
L=10.
resolucion=100
#La trayectoria del cm de la varilla es un cuarto de circulos de radio L/2 de modo que se utilizara un angulo como parametro para calcular x y
theta=np.arange(resolucion)*(np.pi/2)/resolucion
for i in theta:
    #Ecuacion parametrica del circulo de radio L/2
    x=L/2*np.cos(theta)
    y=L/2*np.sin(theta)
#Se grafica y muestra la imagen
fig, ax=plt.subplots(nrows=1, ncols=1)
ax.plot(x,y)
plt.axis('equal')
plt.show()
