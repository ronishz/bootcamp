import multiprocessing as mp
import cmath
import matplotlib.pyplot as plt


import numpy as np

from matplotlib import patches
#from matplotlib.pyplot
from collections import defaultdict

output = mp.Queue()
def getRoots(a,b,c):
	d = b**2-4*a*c 

	#if d < 0:
    		#print "This equation has no real solution"
	if d == 0:
    		x = (-b+cmath.sqrt(d))/(2*a)
	    	print "This equation has one solutions: ", x
		output.put(x)		
		#ans[i]=x
		#ans[i+1]=x
		#i=i+2
	else:
		x1 = (-b+cmath.sqrt(d))/(2*a)
		x2 = (-b-cmath.sqrt(d))/(2*a)
		print "This equation has two solutions: ", x1, " and", x2
		output.put(x1)
		output.put(x2)		
		#ans[i]=x1
		#ans[i+1]=x2
		#i=i+2

i=0
ans = []
print("Enter the coefficient of first quadratic equation")
a=float(input("Enter a:"))
b=float(input("Enter b:"))
c=float(input("Enter c:"))

print ("Enter the coefficient of second quadratic equation")
x=float(input("Enter x:"))
y=float(input("Enter y:"))
z=float(input("Enter z:"))
#getRoots(a,b,c)
#output1=mp.Queue()
p = mp.Process(target=getRoots, args=(a,b,c,))
p1 = mp.Process(target=getRoots, args=(x,y,z,))
p.start()
p1.start()
p.join()
p1.join()
#results = [output.get() for px in p]
#results += [output.get() for px in p1]
r1=output.get()
r2=output.get()
r3=output.get()
r4=output.get()
plt.axis([-8,8,-8,8])
#unit_circle = patches.Circle((0,0), radius=1, fill=False,color='black', ls='solid', alpha=0.1)
#plt.add_patch(unit_circle)
fig = plt.gcf()
plt.grid(True, color='0.9', linestyle='-', which='both', axis='both')
mycircle = plt.Circle((0,0),1,color='black',fill=False)
fig.gca().add_artist(mycircle)
'''x = []
x.append(r1.real)
x.append(r2.real)
y =[]
y.append(r1.imag)
y.append(r2.imag)'''

plt.plot((0,0),(-8,8))
plt.plot((8,-8),(0,0))

#plt.text(2, 7, r'Pole-Zero Plot', fontsize=15)
plt.title('Pole-Zero Plot')
plt.xlabel('Real')
plt.ylabel('Img')

plt.plot([r1.real,r2.real],[r1.imag,r2.imag],'x')
plt.plot([r3.real,r4.real],[r3.imag,r4.imag],'o')
#plt.plot([r3,r4],'x')


plt.show()

