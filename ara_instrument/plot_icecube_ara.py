# -*- coding: utf-8 -*-
import numpy as np #import numpy
import matplotlib.pyplot as plt

# very helpful: http://icecube.berkeley.edu/calibration/IceCubeCoordinateSystem.pdf
	
def main():

	data = np.genfromtxt("icecube_dom60.csv", delimiter=',',skip_header=1, names=['x','y','z','string','dom'])

	xs = data['x']
	ys = data['y']
	zs = data['z']
	strings = data['string']
	doms = data['dom']
	#convert to km
	xs/=1000.
	ys/=1000.
	# xs/=0.3048
	# ys/=0.3048


	icecube_center=np.array([46500,52200])
	icecube_center=icecube_center*.3048/1000.


	xs+=icecube_center[0]
	ys+=icecube_center[1]

	A1=np.array([38800.69, 51066.22])
	A2=np.array([35528.80, 45382.35])
	A3=np.array([32246.30, 51065.59])
	SP=np.array([49722.88, 50530.11])
	WT3=np.array([41062.3, 50347.4])
	ICL=np.array([46430.6, 52174.2])
	A1*=.3048/1000.
	A2*=.3048/1000.
	A3*=.3048/1000.
	SP*=.3048/1000.
	WT3*=.3048/1000.
	ICL*=.3048/1000.

	fig = plt.figure(figsize=(2*7,2*4))
	ax=fig.add_subplot(111)

	ax.plot(xs,ys,'o',color='gray',markersize=6,linewidth=0,alpha=0.7)
	ax.plot(A2[0],A2[1], "o", color='red', label="A2", markersize=12)
	ax.plot(A3[0],A3[1], "o", color='blue', label="A3", markersize=12)
	ax.plot(SP[0],SP[1], "k>", label="SP", markersize=12)
	ax.plot(WT3[0],WT3[1], "k<", label="WT3", markersize=12)
	ax.plot(ICL[0],ICL[1], "k^", label="ICL", markersize=12)

	ax.text(0.27, 0.23, 'A2',
		verticalalignment='bottom', horizontalalignment='left',
		transform=ax.transAxes,
		color='red', fontsize=24)
	ax.text(0.13, 0.66, 'A3',
		verticalalignment='bottom', horizontalalignment='left',
		transform=ax.transAxes,
		color='blue', fontsize=24)
	ax.text(0.51, 0.50, 'WT3',
		verticalalignment='bottom', horizontalalignment='left',
		transform=ax.transAxes,
		color='black', fontsize=24)
	ax.text(0.88, 0.58, 'South \nPole',
		verticalalignment='top', horizontalalignment='left',
		transform=ax.transAxes,
		color='black', fontsize=24)
	ax.text(0.75, 0.64, 'ICL',
		verticalalignment='bottom', horizontalalignment='left',
		transform=ax.transAxes,
		color='black', fontsize=24,
		fontweight='bold')
	ax.text(0.75, 0.86, 'IceCube',
		verticalalignment='bottom', horizontalalignment='left',
		transform=ax.transAxes,
		color='grey', fontsize=24)
	ax.annotate("",  
		xytext=(A2[0], A2[1]),
		xy=(A2[0]+(0.5-np.cos(np.radians(36.773))), A2[1]+(0.5*np.sin(np.radians(36.773)))),
		arrowprops=dict(arrowstyle="->",
						color='red',
						ls='--')
		)
	ax.annotate("", 
		xytext=(A2[0], A2[1]),
		xy=(A2[0]+(0.5-np.sin(np.radians(90-36.773))), A2[1]-(0.5*np.cos(np.radians(90-36.773)))),
		arrowprops=dict(arrowstyle="->",
						color='red',
						ls='--')
		)

	ax.annotate("",  
		xytext=(A3[0], A3[1]),
		xy=(A3[0]+(0.5-np.cos(np.radians(36.773))), A3[1]+(0.5*np.sin(np.radians(36.773)))),
		arrowprops=dict(arrowstyle="->",
						color='blue',
						ls='--')
		)
	ax.annotate("", 
		xytext=(A3[0], A3[1]),
		xy=(A3[0]+(0.5-np.sin(np.radians(90-36.773))), A3[1]-(0.5*np.cos(np.radians(90-36.773)))),
		arrowprops=dict(arrowstyle="->",
						color='blue',
						ls='--')
		)


	# ax.legend(fontsize=24, loc='lower right')
	ax.grid(alpha=0.4)

	ax.set_xlabel('Easting (km)',size=30)
	ax.set_ylabel('Northing (km)',size=30)
	ax.tick_params(labelsize=30,pad=10)

	ax.set_xlim(9,16)
	ax.set_ylim(13,17)

	ax.set_xticklabels(['','10','11','12','13','14','15',''])
	ax.set_yticklabels(['','14','15','16',''])

	fig.savefig("ARA2_instrument.png",edgecolor='none',bbox_inches="tight",dpi=300)

#actually execute the main function
main()


			
		
