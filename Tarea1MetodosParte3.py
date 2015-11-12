# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os
#from moviepy.editor import *

'''
Nota importante: este script requiere el modulo moviepy
Este se puede instalar con (sudo) pip install moviepy
'''


#Tamaño y numero de iteraciones en la simulacion del juego de la vida
tamano=100
iteraciones=50

#matriz del estado inicial de la simulacion
matriz=np.random.randint(2,size=[tamano,tamano])

#Este sera un contenedor de matrices, una para el estado en cada iteracion.
Supermat=[matriz]
plt.imshow(matriz, cmap='Greys', interpolation='nearest')
plt.savefig('conway0.jpg')

for k in range(iteraciones):
    print k
    matriz=Supermat[k]
    matrizNew=np.zeros(shape=([tamano,tamano]))
    
    #Iteracion sobre cada celda
    for i in np.arange(tamano)-1:
        for j in np.arange(tamano)-1:
            #numero de vecinos vivos. Se inicializa asi para no contarse a el mismo
            vecinos=-matriz[i][j]
           
           #Iteracion sobre cada vecino.
            for a in range(3):
                for b in range(3):
                    vecinos=vecinos+matriz[i+a-1][j+b-1]
            
            #Como la matriz donde se guardara la nueva iteracion esta en ceros solo se necesitan las siguientes condiciones
            if vecinos==2:
                matrizNew[i][j]=matriz[i][j]
            if vecinos==3:
                matrizNew[i][j]=1
                
    Supermat.append(matrizNew)
    plt.imshow(matriz, cmap='Greys', interpolation='nearest')
    plt.savefig('conway%s.jpg' %str(k+1))

os.system('convert -delay 40 -loop 0 conway*.jpg conway.gif')
