#include "lib/vector.h"
#include "lib/basis.h"
#include <stdio.h>
#include <math.h>
#include "lib/SINS.h"
#include "lib/filereader_sins.h"
#include "lib/progbar.h"

using namespace Vectors;
using namespace std;

enum {
    COLS_CNT = 22,
    PROGB_LEN = 100,
    OUT_INTERVAL = 100
};

#define UPD_PERIOD 0.01

double degtorad(double deg) {
    return deg / 180 * M_PI;
}

double radtodeg(double rad) {
    return rad / M_PI * 180;
}

int main(int argc, char **argv) {
    if (argc == 2) {
        basis B0;
        B0.rotate(vector(0, degtorad(-1.954215945840), 0));
        B0.rotate(vector(degtorad(-3.172652538105), 0, 0));
        B0.rotate(vector(0, 0, -degtorad(87.123140486447)));
        SINS_t SINS(degtorad(55.654100000000), degtorad(37.551900000000), 216.899993896484, vector(0, 0, 0), B0, UPD_PERIOD);
        FILE *infile;
        FILE *outfile;
        infile  = fopen(argv[1], "r");
        outfile = fopen("out.txt", "w");
        int i;
        char *dummy = NULL;
        size_t linemaxlen = 255;
        printf("Pre-scanning file ...\n");
        for (i = 0; !feof(infile) && getline(&dummy, &linemaxlen, infile); ) {
           i++;
        }
        printf("%d lines found\n", i);
        progbar_t progb(i, PROGB_LEN);
        progb.upd(0);
        rewind(infile);
        double indata[COLS_CNT];
        for (i = 0; !feof(infile); ) {
            i++;
            freadline(infile, indata, COLS_CNT);
            vector acc_raw  (indata[ACC_X] , indata[ACC_Y] , indata[ACC_Z] ),
                   omega_raw(indata[GYRO_X], indata[GYRO_Y], indata[GYRO_Z]);
            SINS.upd(acc_raw, omega_raw);
            progb.upd(i);
            if ((i % OUT_INTERVAL) == 0) {
                double fi         = radtodeg(SINS.getfi()),
                       lambda     = radtodeg(SINS.getlambda()),
                       fi_sns     = indata[FI_SNS],
                       lambda_sns = indata[LAMBDA_SNS],
                       dfi        = fi - fi_sns,
                       dlambda    = lambda - lambda_sns;
                fprintf(outfile,
                        "%20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf\n",
                        fi, lambda, fi_sns, lambda_sns, dfi, dlambda);
            }
        }
        printf("\n");
        fclose(infile);
        fclose(outfile);


/////////////////
/////////////////
/////////////////
/*	vector f_raw_L = f_raw_B;
	f_raw_L.Globalize(B);

	vector omega_L = omega_raw_B;
	omega_L.Globalize(B);

	vector U = U_I;
	U.Localize(L_I);

	vector omegaL;
	// вычислить

	double hR = position.z + R;
	vector r(hR * cos(position.y) * cos(position.x),
			 hR * cos(position.y) * sin(position.x),
			 hR * sin(position.y));

	vector acc = f_raw_B - vector::CrossProd((U + omegaL), V)
						 - vector::CrossProd(U, vector::CrossProd(U, r)) + g;

	V = V + acc * dt;
	r = r + V * dt;

	B.rotate(omega_L * dt);*/
    }
	return 0;
}
