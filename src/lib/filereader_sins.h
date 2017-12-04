#include <stdio.h>
#include <stdlib.h>

enum col_pos {
    GYRO_X = 0,
    GYRO_Y,
    GYRO_Z,
    ACC_X,
    ACC_Y,
    ACC_Z,
    V_SNS = 7,
    COURSE_SNS = 8,
    LATIT_SNS = 9,
    LONGIT_SNS = 10,
    H_SNS = 11
};

#define MAXLEN 1024

bool freadline(FILE *f, double *a, int colcnt) {
    char str[MAXLEN],
         *strptr = str,
         *curend;
    int i;
    if (fgets(strptr, MAXLEN, f)) {
        double dbuf = strtod(strptr, &curend);
        for (int i = 0; (str == curend) || (i < colcnt); ++i) {
            a[i] = dbuf;
            strptr = curend;
            dbuf = strtod(strptr, &curend);
        }
        return true;
    }

    return false;
}

#undef MAXLEN
