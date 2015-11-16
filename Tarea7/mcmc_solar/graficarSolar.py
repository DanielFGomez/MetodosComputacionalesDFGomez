import numpy as np
import matplotlib.pylab as plt
	
data=np.genfromtxt("mcmc_solar.dat")
obs=np.genfromtxt("datosLeidos.dat")


x=obs[:,1]
t=obs[:,0]

chi=data[:,0]
a=data[:,1]
b=data[:,2]
c=data[:,3]
d=data[:,4]
print(chi[-1])

xP=np.mean(a)*np.cos((2*np.pi/np.mean(d))*t+np.mean(b))+np.mean(c)

fig1=plt.figure()
plt.subplot(2,1,1)
plt.scatter(t,x)
plt.plot(t,xP)
plt.subplot(2,1,2)
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
