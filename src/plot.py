# -*- coding: cp1251 -*-
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
import getopt
import mpl_toolkits.axisartist as AA
from mpl_toolkits.axes_grid1 import host_subplot
from matplotlib import rc
import seaborn as sns

f = open("out.txt")
data = f.read()
data = data.split('\n')
test = data[0].split()
print(test[4])
vsns      = []
vesns     = []
vnsns     = []
ve        = []
vn        = []
v         = []
accsns    = []
accins    = []
coursesns = []
courseins = []
courseerr = []
omegaz    = []
accerr    = []
roll      = []
pitch     = []
f1 = open('out_no_corr.txt')
data1 = f1.read()
data1 = data1.split('\n')
test1 = data1[0].split()
ve1 = []
vn1 = []
for row in data1:
    nums = row.split()
    if len(nums) > 0:
        ve1.append(float(nums[10]))
        vn1.append(float(nums[11]))
for row in data:
    nums = row.split()
    if len(nums) > 0:
        omegaz.append(float(nums[14]))
        accsns.append(float(nums[3]))
        accins.append(float(nums[13]))
        vsns.append(float(nums[2]))
        v.append(float(nums[12]))
        vesns.append(float(nums[0]))
        vnsns.append(float(nums[1]))
        ve.append(float(nums[10]))
        vn.append(float(nums[11]))
        coursesns.append(float(nums[7]))
        courseins.append(float(nums[18]))
        courseerr.append(float(nums[19]))
        accerr.append(float(nums[20]))
        roll.append(float(nums[21]))
        pitch.append(float(nums[22]))
x = [float(t) / 60 for t in range(len(vesns))]
print(len(x))

sns.set_style('white')
sns.set_style('ticks')

mpl.rcParams.update({'font.size' : 18})

def make_patch_spines_invisible(ax):
    ax.set_frame_on(True)
    ax.patch.set_visible(False)
    for sp in ax.spines.values():
        sp.set_visible(False)

fig, host = plt.subplots()

par1 = host.twinx()
#    par3 = host.twinx()

def _clip(a) :
    if (a < -180) :
        return a + 360
    if (a > 180) :
        return a - 360
    return a
p1, = host.plot(x, roll, "b-")
p2, = par1.plot(x, pitch, "r")

#    host.set_xlim(0, 2)
#    host.set_ylim(-20, 0)
par1.set_ylim(-10, 10)
host.set_ylim(-10, 10)
host.set_xlabel(u"Время, мин")
host.set_ylabel(u"Крен, град.")
par1.set_ylabel(u"Тангаж, град.")
host.yaxis.label.set_color(p1.get_color())
par1.yaxis.label.set_color(p2.get_color())

tkw = dict(size=4, width=1.5)
host.tick_params(axis='y', colors=p1.get_color(), **tkw)
par1.tick_params(axis='y', colors=p2.get_color(), **tkw)
host.tick_params(axis='x', **tkw)

#par2 = host.twinx()
#par2.set_ylim(-15, 15)
#par2.set_ylabel(u"Производная курса, гр./сек")
#p3, = par2.plot(x, [omegaz[i]/np.pi*180 for i in range(len(x))], "g-", label="Velocity")
#par2.spines["right"].set_visible(True)
#par2.spines["right"].set_position(("axes", 1.2))
#par2.tick_params(axis='y', colors=p3.get_color(), **tkw)
#par2.yaxis.label.set_color(p3.get_color())
##    make_patch_spines_invisible(par2)
#fig.subplots_adjust(right=0.75)

#    lines = [p1, p2, p3]

#    host.legend(lines, [l.get_label() for l in lines])

host.grid(c='gray', ls='--', lw=0.5)
plt.title(u'Углы ориентации')
plt.savefig('plot.png')
plt.draw()
plt.show()
