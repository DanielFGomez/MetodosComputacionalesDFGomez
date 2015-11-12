import numpy as np

def ajuste(archivo,min=1900,max=2000):
    data=np.genfromtxt(archivo)
    manchas=np.zeros(shape=(max-min+1,3))
    
    #se crea un array con los annos que nos interesan, el total de manchas observadas, y el numero de observaciones
    for i in data:
        if i[0]>=min and i[0]<=max and i[-1]!=-99:
            manchas[i[0]-min,0]=i[0]
            manchas[i[0]-min,1]+=i[2]*i[3]
            manchas[i[0]-min,2]+=i[2]
            
    #Se definen las matrices para hacer el ajuste por minimos cuadrados        
    x=np.delete(manchas,np.where(manchas[:,2]==0),0)
    y=np.matrix(x[:,1]*1.0/x[:,2]).T
    X=np.matrix(np.c_[np.ones(len(x)),np.sin(x[:,0]*2*np.pi/11),np.cos(x[:,0]*2*np.pi/11)])
    par=np.linalg.inv(X.T*X)*X.T*y
    
    #se cambian los coeficientes encontrados para ir con el formato del enunciado
    a=np.sqrt(par[1,0]**2+par[2,0]**2)
    b=np.arctan2(-par[1,0],par[2,0])
    c=par[0,0]
    
    return a,b,c

def datos(archivo,min=1900,max=2000):
    data=np.genfromtxt(archivo)
    manchas=np.zeros(shape=(max-min+1,3))
    
    #se crea un array con los annos que nos interesan, el total de manchas observadas, y el numero de observaciones
    for i in data:
        if i[0]>=min and i[0]<=max and i[-1]!=-99:
            manchas[i[0]-min,0]=i[0]
            manchas[i[0]-min,1]+=i[2]*i[3]
            manchas[i[0]-min,2]+=i[2]
            
    #Se definen las matrices para hacer el ajuste por minimos cuadrados        
    x=np.delete(manchas,np.where(manchas[:,2]==0),0)
    y=(x[:,1]*1.0/x[:,2]).T
    anno=x[:,0]
    return anno,y
'''
def datosMes(archivo,min=1900,max=2000):
    data=np.genfromtxt(archivo)
    mes=np.arange(max-min+1)
    sol=np.zeros(max-min+1)
    for i in data:
        if i[0]>=min and i[0]<=max and i[-1]!=-99:
            sol=i[3]
            
 '''        
    
    
