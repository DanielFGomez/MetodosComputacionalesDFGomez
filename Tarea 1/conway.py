# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import os

#Tamaño y numero de iteraciones en la simulacion del juego de la vida
tamano=50
iteraciones=50

#matriz del estado inicial de la simulacion
matriz=np.random.randint(2,size=[tamano,tamano])

#Este sera un contenedor de matrices, una para el estado en cada iteracion.
fig=plt.figure()
plt.imshow(matriz, cmap='Greys', interpolation='nearest')

plt.savefig('conway0.png')


for k in range(iteraciones):
    print k
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
                
    matriz=matrizNew
    
    plt.imshow(matriz, cmap='Greys', interpolation='nearest')
    #La variable num es para asegurarse que se esta en orden alfabetico
    num='0000'+str(k+1)
    num=num[-4:]
    plt.savefig('conway%s.png' %num)

os.system('convert -delay 40 -loop 0 conway*.png conway.gif')
