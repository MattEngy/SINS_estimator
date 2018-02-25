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
    v         = []
    accsns    = []
    coursesns = []
    courseins = []
    courseerr = []
    omegaz    = []
    for row in data:
        nums = row.split()
        if len(nums) > 0:
            omegaz.append(float(nums[14]))
            accsns.append(float(nums[3]))
            vsns.append(float(nums[2]))
            v.append(float(nums[12]))
            vesns.append(float(nums[0]))
            vnsns.append(float(nums[1]))
            ve.append(float(nums[10]))
            vn.append(float(nums[11]))
            coursesns.append(float(nums[7]))
            courseins.append(float(nums[18]))
            courseerr.append(float(nums[19]))
    x = [float(t) / 60 for t in range(len(vesns))]
    print(len(x))
    subplt = plt.subplot(111)
#    subplt1 = subplt.twinx()
#    subplt2 = subplt.twinx()
#    subplt3 = subplt.twinx()
#    subplt4 = subplt.twinx()
    mpl.style.use('seaborn')
#    plt.plot(x, vesns, 'b', label = 'vE INS in, m/s')
#   plt.plot(x, vnsns, 'g', label = 'vN INS in, m/s')
#    plt.plot(x, ve,    'r', label = 'vE, m/s')
#    subplt1.plot(x, courseerr,    'y', label = 'courseerr, deg')
#    subplt2.plot(x, accsns,    'y', label = 'accsns, m/s^2', color = 'r')
#    plt.plot(x, vsns,    'y', label = 'vsns, m/s', color = 'g')
#    subplt4.plot(x, omegaz,    'y', label = 'omegaz, rad/sec', color = 'b')
#    plt.plot(x, np.subtract(courseins, coursesns), 'y', label = "course_err, deg", color = 'r')
#    plt.plot(x, coursesns, 'y', label = "course_sns, deg", color = 'b')
#    plt.plot(x, courseins, 'y', label = "course_ins, deg", color = 'r')
    plt.plot(x, np.subtract(vn, vnsns), 'y', label = "vn_err, m/s", color = 'b')
    plt.plot(x, np.subtract(ve, vesns), 'y', label = "ve_err, m/s", color = 'r')
    plt.legend(loc='best')
    plt.xlabel('time, min')
    plt.savefig('plot.png')
    plt.draw()
    plt.show()
