import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
import getopt

with open("out.txt") as f:
    data = f.read()

    data = data.split('\n')
    test = data[0].split()
    print(test[4])
    vsns      = []
    vesns     = []
    vnsns     = []
    ve        = []
    vn        = []
    coursesns = []
    courseins = []
    courseerr = []
    for row in data:
        nums = row.split()
        if len(nums) > 0:
            vsns.append(float(nums[2]))
            vesns.append(float(nums[5]))
            vnsns.append(float(nums[6]))
            ve.append(float(nums[7]))
            vn.append(float(nums[8]))
            coursesns.append(float(nums[6]))
            courseins.append(float(nums[14]))
            courseerr.append(float(nums[14]) - float(nums[6]))
            if abs(courseerr[len(courseerr) - 1]) >= 40:
                courseerr[len(courseerr) - 1] = 40
    x = [float(t) / 60 for t in range(len(vesns))]
    print(len(x)) 
    mpl.style.use('seaborn')
#    plt.plot(x, vesns, 'b', label = 'vE INS in, m/s')
#   plt.plot(x, vnsns, 'g', label = 'vN INS in, m/s')
#    plt.plot(x, ve,    'r', label = 'vE, m/s')
#    plt.plot(x, vn,    'y', label = 'vN, m/s')
#    plt.plot(x, courseins,    'y', label = 'Hins, m/s', color = 'r')
    plt.plot(x, courseerr,    'y', label = 'H_err, deg')
    plt.plot(x, vsns,    'y', label = 'Vsns, m/s', color = 'b')
    plt.legend(loc='best')
    plt.xlabel('time, min')
    plt.savefig('plot.png')
    plt.show()
