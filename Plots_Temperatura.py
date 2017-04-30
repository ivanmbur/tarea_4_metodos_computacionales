import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import rc

rc("text", usetex = True)

tiempos = [0, 100, 2500]
casos = [1, 2]
condiciones = ["abierta", "periodica", "fija"]
color = ["k", "b", "g"]

datos = [[[np.loadtxt("%s_%d_%d.txt" % (condicion_frontera, caso, tiempo)) for tiempo in tiempos] for condicion_frontera in condiciones] for caso in casos]

promedio = [[np.loadtxt("%s_%d_promedio.txt" % (condicion_frontera, caso)) for condicion_frontera in condiciones] for caso in casos]

x, y = np.meshgrid(range(0, 100), range(0, 100))

for i in range(0,len(tiempos)):
	for j in range(0, len(condiciones)):
		for k in range(0, len(casos)):
			fig = plt.figure()
			ax = fig.add_subplot(111, projection = "3d")
			ax.plot_wireframe(x, y, datos[k][j][i])
			ax.set_title(r"Condi\'on de frontera %s en el caso %d en el tiempo $%ds$" % (condiciones[j], casos[k], tiempos[i]))
			ax.set_xlabel(r"$x$")
			ax.set_ylabel(r"$y$")
			ax.set_zlabel(r"$T$")
			fig.savefig("%s_%d_%d.pdf" % (condiciones[j], casos[k], tiempos[i]))

for i in range(0, len(casos)):
	fig, ax = plt.subplots()
	for j in range(0, len(condiciones)):
		ax.plot(promedio[i][j][:,0], promedio[i][j][:,1], c = color[j], label = r"Condici\'on %s" % condiciones[j])
	ax.set_title(r"Promedio de temperatura en el caso %d" % casos[i])
	ax.set_xlabel(r"$t$")
	ax.set_ylabel(r"$\langle T\rangle$")
	ax.legend()
	fig.savefig("%d_promedio.pdf" % casos[i]) 

