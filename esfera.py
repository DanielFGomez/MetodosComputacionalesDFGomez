# -*- coding: utf-8 -*-
 
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
 
def camino(thetaInicial, phiInicial, thetaFinal, phiFinal, nPoints=100):
    thetaInicial=thetaInicial*2*np.pi/360
    thetaFinal=thetaFinal*2*np.pi/360
    phiInicial=phiInicial*2*np.pi/360
    phiFinal=phiFinal*2*np.pi/360
     
     
    punto1=np.matrix([[np.cos(phiInicial)*np.sin(thetaInicial)],[np.sin(phiInicial)*np.sin(thetaInicial)],[np.cos(thetaInicial)]])
    punto2=np.matrix([[np.cos(phiFinal)*np.sin(thetaFinal)],[np.sin(phiFinal)*np.sin(thetaFinal)],[np.cos(thetaFinal)]])
    zAxis=np.cross(punto1,punto2,axis=0)
     
    if np.array_equal(punto1,punto2):
        caminoTheta,caminoPhi = ([thetaInicial]*nPoints, [phiInicial]*nPoints)
    elif np.linalg.norm(zAxis)==0:
        caminoTheta=thetaInicial+np.arange(nPoints)*np.pi/(nPoints-1)
        caminoPhi=np.array([phiInicial for x in range(nPoints)])
    else:    
        zAxis=zAxis/np.linalg.norm(zAxis)
        xAxis=punto1.copy()
        yAxis=np.cross(zAxis,xAxis,axis=0)
         
        matTransInv=np.c_[xAxis,yAxis,zAxis]
        matTrans=matTransInv.transpose()
         
        punto2Prima=matTrans*punto2
        phiFinalPrima=float(np.arctan2(punto2Prima[1],punto2Prima[0]))
         
         
        caminoPrima=np.arange(nPoints)*phiFinalPrima/(nPoints-1)
         
        coorCaminoPrima=np.matrix([np.cos(caminoPrima),np.sin(caminoPrima),np.zeros(nPoints)])
        coorCamino=matTransInv*coorCaminoPrima
         
        caminoTheta=np.array(np.arccos(coorCamino[2]))
        caminoPhi=np.arctan2(np.array(coorCamino[1])/np.sin(caminoTheta),np.array(coorCamino[0])/np.sin(caminoTheta))
         
         
    return caminoPhi, caminoTheta
         
         
 
 
fig = plt.figure()
ax = fig.gca(projection='3d')
    
 
phiInicial=0
phiFinal=180
thetaInicial=0
thetaFinal=180  
phi,theta=camino(thetaInicial,phiInicial,thetaFinal,phiInicial)

 
 
punto1=np.matrix([[np.cos(phiInicial)*np.sin(thetaInicial)],[np.sin(phiInicial)*np.sin(thetaInicial)],[np.cos(thetaInicial)]])
punto2=np.matrix([[np.cos(phiFinal)*np.sin(thetaFinal)],[np.sin(phiFinal)*np.sin(thetaFinal)],[np.cos(thetaFinal)]])
 
x=np.cos(phi)*np.sin(theta)
y=np.sin(phi)*np.sin(theta)
z=np.cos(theta)
 
'''
plt.scatter(theta*180/np.pi,phi*180/np.pi)
plt.scatter([30,10],[0,240],color='r')
plt.show()
'''
xp=[punto1[0,0],punto2[0,0]]
yp=[punto1[1,0],punto2[1,0]]
zp=[punto1[2,0],punto2[2,0]]
 
ax.scatter(xp,yp,zp,color='r')
ax.scatter(x,y,z)
ax.scatter(0,0,0,color='k')
ax.xlabel="x"
ax.ylabel="y"
ax.zlabel="z"
plt.show()
 
'''
u, v = np.mgrid[0:2*np.pi:20j, 0:np.pi:10j]
x=np.cos(u)*np.sin(v)
y=np.sin(u)*np.sin(v)
z=np.cos(v)
ax.plot_wireframe(x, y, z, color="r")
'''
