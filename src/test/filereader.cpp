#include <stdio.h>
#include <stdlib.h>
#include "../lib/filereader_sins.h"

int main(int argc, char **argv) {
    FILE *inpf = fopen(argv[1], "r");

    int cols = atoi(argv[2]);
    double a[cols];

    freadline(inpf, a, cols);
    


    printf("%lf\t%lf\n", a[GYRO_X], a[cols - 1]);

    fclose(inpf); 
    return 0;
}
