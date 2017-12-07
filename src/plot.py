import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
import getopt

with open("out.txt") as f:
    data = f.read()

    data = data.split('\n')
    test = data[0].split()
    print(test[4])
    vesns = []
    vnsns = []
    ve    = []
    vn    = []
    for row in data:
        nums = row.split()
        if len(nums) > 0:
            vesns.append(float(nums[5]))
            vnsns.append(float(nums[6]))
            ve.append(float(nums[7]))
            vn.append(float(nums[8]))
    x = [float(t) / 60 for t in range(len(vesns))]
    print(len(x)) 
    mpl.style.use('seaborn')
    plt.plot(x, vesns, 'b', label = 'vE INS in, m/s')
    plt.plot(x, vnsns, 'g', label = 'vN INS in, m/s')
    plt.plot(x, ve,    'r', label = 'vE, m/s')
    plt.plot(x, vn,    'y', label = 'vN, m/s')
    plt.legend(loc='best')
    plt.xlabel('time, min')
    plt.savefig('plot.png')
