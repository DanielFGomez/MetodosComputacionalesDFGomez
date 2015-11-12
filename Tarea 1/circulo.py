import numpy as np
import matplotlib.pyplot as plt
import sys

#numero de datos en el plot
resolucion=100

#Se abre el archivo y se lee su contenido
infile = open(sys.argv[1], 'r')
lineas =infile.readlines()

#Se crea una matriz de ceros para anotar ahi los puntos leidos
puntos=np.zeros([3,2])

try:
    #prueba que sean 3 lineas
    if len(lineas)!=3:
        raise NameError('El archivo no tiene 3 puntos')
     
    i=np.zeros(2)
    for linea in lineas:
        punto=linea.split()
        
        #Prueba que sean 2 coordenadas en la linea
        if len(punto)!=2:
            raise NameError('No estan bien definidos los puntos')
            
        #Agrega cada coordenada de los puntos en la matriz quitando '\n'
        for j in punto:
            puntos[i[0],i[1]]=float(j.split('//', 1)[0])
            i=i+[0,1]
        i=i+[1,-2]
        
    #prueba si los puntos son colineales
    matrizPrueba=puntos-puntos[-1]
    matrizPrueba=np.delete(matrizPrueba,2,0)
    
    if np.linalg.det(matrizPrueba)==0:
        raise NameError('Los puntos son colineales')
    
    #Recoge el error si se escribio por ejemplo un string en vez de un numero
except ValueError:
    raise NameError('Error al leer los numeros')


#Lee da nombres a cada uno de las coordenadas de los puntos
[x1, y1, x2, y2, x3, y3]= np.asarray(puntos).reshape(-1)

#Se crea la matriz y el vector del sistema de ecuaciones que encuentra el centro del circulo
M=2*np.matrix([[x1-x2 , y1-y2],[x1-x3 , y1-y3]])
y=np.matrix([[x1**2 - x2**2 + y1**2 - y2**2 ],[ x1**2 - x3**2 + y1**2 - y3**2]])

#Se resuelve el sistema y se encuentra el centro y el radio
[x0,y0]=np.linalg.inv(M)*y
r=float(np.sqrt((x1-x0)**2 + (y1-y0)**2))

x=np.zeros(resolucion+1)
y=np.zeros(resolucion+1)

#Ecuacion parametrica del circulo
for i in range(resolucion + 1):
    t=i*2*np.pi/resolucion
    x[i]=r*np.cos(t)+float(x0)
    y[i]=r*np.sin(t)+float(y0)
    
#Crea y muestra la grafica 
fig, ax=plt.subplots(nrows=1, ncols=1)    
ax.plot(x,y)
ax.scatter([x1,x2,x3],[y1,y2,y3])
plt.axis('equal')
plt.show()
