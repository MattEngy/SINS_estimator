#include <stdio.h>
#include <stdlib.h>

enum col_pos {
    ACC_X = 0,
    ACC_Y,
    ACC_Z,
    GYRO_X,
    GYRO_Y,
    GYRO_Z
};

bool freadline(FILE *f, double *a, int colcnt) {
     for (int i = 0; i < colcnt; i++) {
        if (fscanf(f, "%lf", &(a[i])) == 0) {
            return false;
        }
     }
     return true;
}
