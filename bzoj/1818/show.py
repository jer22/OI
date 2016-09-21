import matplotlib.pyplot as plt
import re

data = open('1818.in').readlines()

plt.xlim(xmax = 100,xmin = -100)
plt.ylim(ymax = 100,ymin = -100)

for i in range(1, int(data[0]) + 1) :
	cor = data[i].split(' ')
	plt.plot(cor[0], cor[1], 'ro')
plt.show()
