"""
Common neutrino nucleon interactions
"""
import matplotlib.pyplot as plt
from feynman import Diagram

fig = plt.figure(figsize=(10,5))

ax1 = fig.add_subplot(121, frameon=False)
diagram = Diagram(ax1)
diagram.text(.5,0.9,"Charged-Current", fontsize=25)
in1 = diagram.vertex(xy=(0.05,0.75), marker='')
in2 = diagram.vertex(xy=(0.05,0.25), marker='')
v1 = diagram.vertex(xy=(.45,.6))
v2 = diagram.vertex(xy=(.45,.4))
out1 = diagram.vertex(xy=(0.85,0.75), marker='')
out2 = diagram.vertex(xy=(0.85,0.25), marker='')
nu1 = diagram.line(in1, v1) #incoming neutrino
N = diagram.line(in2, v2) #incoming neucleon
W = diagram.line(v1,v2,style='wiggly') #W mediator
nu2 = diagram.line(v1, out1) #outgoing neutrino
X = diagram.line(v2, out2) #outgoing shower
diagram.text(0.10,0.68,"$\\nu_{\ell}$",fontsize=30)
diagram.text(0.10,0.32,"$N$",fontsize=30)
diagram.text(0.57,0.5,"$W^{\pm}$",fontsize=30)
diagram.text(0.81,0.68,"$\ell$",fontsize=30)
diagram.text(0.81,0.32,"$X$",fontsize=30)

ax2= fig.add_subplot(122, frameon=False)
diagram2 = Diagram(ax2)
diagram2.text(.5,0.9,"Neutral-Current", fontsize=25)
in1 = diagram2.vertex(xy=(0.05,0.75), marker='')
in2 = diagram2.vertex(xy=(0.05,0.25), marker='')
v1 = diagram2.vertex(xy=(.45,.6))
v2 = diagram2.vertex(xy=(.45,.4))
out1 = diagram2.vertex(xy=(0.85,0.75), marker='')
out2 = diagram2.vertex(xy=(0.85,0.25), marker='')
nu1 = diagram2.line(in1, v1) #incoming neutrino
N = diagram2.line(in2, v2) #incoming neucleon
W = diagram2.line(v1,v2,style='wiggly') #W mediator
nu2 = diagram2.line(v1, out1) #outgoing neutrino
X = diagram2.line(v2, out2) #outgoing shower
diagram2.text(0.10,0.68,"$\\nu$",fontsize=30)
diagram2.text(0.10,0.32,"$N$",fontsize=30)
diagram2.text(0.57,0.5,"$Z^{0}$",fontsize=30)
diagram2.text(0.81,0.68,"$\\nu$",fontsize=30)
diagram2.text(0.81,0.32,"$N*$",fontsize=30)

diagram.plot()
diagram2.plot()

plt.tight_layout()
fig.savefig("neutrino_nucleon_interactions.png",dpi=300)