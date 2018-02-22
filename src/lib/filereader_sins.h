#include <stdio.h>
#include <stdlib.h>
#include "params.h"

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
