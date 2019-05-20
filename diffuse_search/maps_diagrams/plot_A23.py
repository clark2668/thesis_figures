# -*- coding: utf-8 -*-
import numpy as np #import numpy
import matplotlib.pyplot as plt

def main():

	# A2

	fig = plt.figure(figsize=(2*5,2*5))
	ax=fig.add_subplot(111)
	ax.set_title("A2",fontsize=30)

	A2_S1=np.array([10.5874,2.3432])
	A2_S2=np.array([4.85167,-10.3981])
	A2_S3=np.array([-2.58128,9.37815])
	A2_S4=np.array([-7.84111,-4.05791])
	A2_P5=np.array([37.8585,-17.7704])
	A2_P6=np.array([21.0882,42.2156])

	ax.plot(A2_S1[0],A2_S1[1], "^", color='black', label="String 1", markersize=12)
	ax.plot(A2_S2[0],A2_S2[1], ">", color='black', label="String 2", markersize=12)
	ax.plot(A2_S3[0],A2_S3[1], "v", color='black', label="String 3", markersize=12)
	ax.plot(A2_S4[0],A2_S4[1], "<", color='black', label="String 4", markersize=12)
	ax.plot(A2_P5[0],A2_P5[1], "x", color='black', label="Cal Pulser 5", markersize=14, mew=5)
	ax.plot(A2_P6[0],A2_P6[1], "+", color='black', label="Cal Pulser 6", markersize=16, mew=5)


	# ax.text(0.27, 0.23, 'A2',
	# 	verticalalignment='bottom', horizontalalignment='left',
	# 	transform=ax.transAxes,
	# 	color='red', fontsize=24)

	ax.legend(fontsize=22, loc='lower left')
	ax.grid(alpha=0.4)

	ax.set_xlabel('Local X (m)',size=30)
	ax.set_ylabel('Local Y (m)',size=30)
	ax.tick_params(labelsize=30,pad=10)

	ax.set_xlim(-50,50)
	ax.set_ylim(-50,50)

	# ax.set_xticklabels(['','10','11','12','13','14','15',''])
	# ax.set_yticklabels(['','14','15','16',''])

	fig.savefig("A2_map.png",edgecolor='none',bbox_inches="tight",dpi=300)


	# A3

	fig2 = plt.figure(figsize=(2*5,2*5))
	ax2=fig2.add_subplot(111)
	ax2.set_title("A3",fontsize=30)

	A3_S1=np.array([4.82341,-9.41804])
	A3_S2=np.array([10.6429,3.40846])
	A3_S3=np.array([-2.0103,9.4124])
	A3_S4=np.array([-8.14654,-3.933])
	A3_P5=np.array([38.2336,-16.2148])
	A3_P6=np.array([18.096,36.7114])

	ax2.plot(A3_S1[0],A3_S1[1], "^", color='black', label="String 1", markersize=12)
	ax2.plot(A3_S2[0],A3_S2[1], ">", color='black', label="String 2", markersize=12)
	ax2.plot(A3_S3[0],A3_S3[1], "v", color='black', label="String 3", markersize=12)
	ax2.plot(A3_S4[0],A3_S4[1], "<", color='black', label="String 4", markersize=12)
	ax2.plot(A3_P5[0],A3_P5[1], "x", color='black', label="Cal Pulser 5", markersize=14, mew=5)
	ax2.plot(A3_P6[0],A3_P6[1], "+", color='black', label="Cal Pulser 6", markersize=16, mew=5)

	ax2.legend(fontsize=22, loc='lower left')
	ax2.grid(alpha=0.4)

	ax2.set_xlabel('Local X (m)',size=30)
	ax2.set_ylabel('Local Y (m)',size=30)
	ax2.tick_params(labelsize=30,pad=10)

	ax2.set_xlim(-50,50)
	ax2.set_ylim(-50,50)

	fig2.savefig("A3_map.png",edgecolor='none',bbox_inches="tight",dpi=300)

#actually execute the main function
main()


			
		
