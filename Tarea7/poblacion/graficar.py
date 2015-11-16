import numpy as np
import matplotlib.pylab as plt


def dX(a, b, x, y):
   	return x*(a-b*y)

def dY(c, d, x, y):
	return -y*(c-d*x)


def RungeKutta(a, b, c, d, x0, y0,iterRK):
 	dt=1.0/iterRK;
	x=np.zeros(iterRK)
	y=np.zeros(iterRK)
	x[0]=x0;
	y[0]=y0;
    	t=np.arange(iterRK)*dt

	print("a=%f  b=%f  c=%f  d=%f\n" %(a,b,c,d))
	for i in range(iterRK-1):

	        #/*Parte 1*/
	        xk1=dX(a,b,x[i],y[i])*dt
	        yk1=dX(c,d,x[i],y[i])*dt
	    
	        #/*Parte 2*/
	        xk2=dX(a,b,x[i]+0.5*xk1,y[i]+0.5*yk1)*dt
	        yk2=dY(c,d,x[i]+0.5*xk1,y[i]+0.5*yk1)*dt
	    
	        #/*Parte 3*/
	        xk3=dX(a,b,x[i]+0.5*xk2,y[i]+0.5*yk2)*dt
	        yk3=dY(c,d,x[i]+0.5*xk2,y[i]+0.5*yk2)*dt
	    
	        #/*Parte 4*/
	        xk4=dX(a,b,x[i]+xk3,y[i]+yk3)*dt
	        yk4=dY(c,d,x[i]+xk3,y[i]+yk3)*dt
	    
	        #/*Parte Final*/
	        x[i+1]=x[i]+(xk1+2*xk2+2*xk3+xk4)/6.0
	        y[i+1]=y[i]+(yk1+2*yk2+2*yk3+yk4)/6.0
	return t,x,y
	
data=np.genfromtxt("poblaciones.dat")
obs=np.genfromtxt("lotka_volterra_obs.dat")

t=obs[:,0]
x=obs[:,1]
y=obs[:,2]

chi=data[:,0]
a=data[:,1]
b=data[:,2]
c=data[:,3]
d=data[:,4]
print(chi[-1])
print("\n Ultimos a=%f  b=%f  c=%f  d=%f\n" %(a[-1],b[-1],c[-1],d[-1]))


tP,xP,yP=RungeKutta(np.mean(a),np.mean(b),np.mean(c),np.mean(d),x[0],y[0],1000)

#tU,xU,yU=RungeKutta(a[-1],b[-1],c[-1],d[-1],x[0],y[0],1000) #Prueba

fig1=plt.figure()
plt.subplot(3,1,1)
plt.scatter(t,x)
plt.plot(tP,xP)
#plt.plot(tU,xU,'r') #Prueba
plt.subplot(3,1,2)
plt.scatter(t,y)
plt.plot(tP,yP)
#plt.plot(tU,yU,'r') #Prueba
plt.subplot(3,1,3)
plt.plot(chi)

AB=np.histogram2d(a,b,bins=20)
AC=np.histogram2d(a,c,bins=20)
AD=np.histogram2d(a,d,bins=20)

BC=np.histogram2d(b,c,bins=20)
BD=np.histogram2d(b,d,bins=20)

CD=np.histogram2d(c,d,bins=20)

fig=plt.figure()
fig.subplots_adjust(hspace=.6)

plt.subplot(3,3,1)
plt.imshow(AB[0],cmap="gray_r")
plt.title("AB")
plt.ylabel("A")
plt.xlabel("B")


plt.subplot(3,3,2)
plt.imshow(AC[0],cmap="gray_r")
plt.title("AC")
plt.ylabel("A")
plt.xlabel("C")

plt.subplot(3,3,3)
plt.imshow(AD[0],cmap="gray_r")
plt.title("AD")
plt.ylabel("A")
plt.xlabel("D")

plt.subplot(3,3,5)
plt.imshow(BC[0],cmap="gray_r")
plt.title("BC")
plt.ylabel("B")
plt.xlabel("C")

plt.subplot(3,3,6)
plt.imshow(BD[0],cmap="gray_r")
plt.title("BD")
plt.ylabel("B")
plt.xlabel("D")

plt.subplot(3,3,9)
plt.imshow(CD[0],cmap="gray_r")
plt.title("CD")
plt.ylabel("C")
plt.xlabel("D")

plt.show()
