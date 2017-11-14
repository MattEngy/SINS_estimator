#include <stdio.h>
#include <stdlib.h>

enum col_pos {
    GYRO_X = 0,
    GYRO_Y,
    GYRO_Z,
    ACC_X,
    ACC_Y,
    ACC_Z,
};

bool freadline(FILE *f, double *a, int colcnt) {
     for (int i = 0; i < colcnt; i++) {
        if (fscanf(f, "%lf", &(a[i])) == 0) {
            return false;
        }
     }
     return true;
}
