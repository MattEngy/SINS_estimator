#include "lib/vector.h"
#include "lib/basis.h"
#include <stdio.h>
#include <math.h>
#include <cmath>
#include "lib/SINS.h"
#include "lib/filereader_sins.h"
#include "lib/progbar.h"
#include "lib/params.h"
#include "lib/LPF.h"
#include "lib/corrector.h"
#include "lib/corrector2.h"

using namespace Vectors;
using namespace std;

double degtorad(double deg) {
    return deg / 180 * M_PI;
}

double radtodeg(double rad) {
    return rad / M_PI * 180;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Wong amount of arguments! Exiting...\n");
        return -1;
    }
    FILE *infile;
    FILE *outfile;
    infile  = fopen(argv[1], "r");
    outfile = fopen("out.txt", "w");
    int i;
    const int linemaxlen = 1024;
    char dummy[linemaxlen];
    printf("Pre-scanning file ...\n");
    for (i = 0; fgets(dummy, linemaxlen, infile) != NULL; ) {
        i++;
    }
    printf("%d lines found\n", i);
    progbar_t progb(i, PROGB_LEN);
    progb.upd(0);
    rewind(infile);
    vector Ucal(0, 0, 0),
           fcal(0, 0, 0);
    basis B0;
    double indata[INP_COLS_CNT];
    for (i = 0; i < (CAL_TIME * UPD_FREQ) && freadline(infile, indata, INP_COLS_CNT); ) {
        i++;
        fcal += vector(indata[ACC_X] , indata[ACC_Y] , indata[ACC_Z]);
        Ucal += vector(indata[GYRO_X] , indata[GYRO_Y] , indata[GYRO_Z]);
        progb.upd(i);
    }
    printf("\nAlignment finished at i = %d, t = %fs\n", i, i / (float)UPD_FREQ);
    SINS_t SINS(degtorad(indata[LATIT_SNS]),
                degtorad(indata[LONGIT_SNS]),
                indata[H_SNS],
                fcal / i,
                Ucal / i,
                1 / float(UPD_FREQ));
    for (i; freadline(infile, indata, INP_COLS_CNT); ) {
        i++;
        vector acc_raw  (indata[ACC_X] , indata[ACC_Y] , indata[ACC_Z] ),
               omega_raw(indata[GYRO_X], indata[GYRO_Y], indata[GYRO_Z]);
        static bool correction_done = false;
        static corrector_t corrector(COR_COURSE_LPF_SENS,
                                     COR_ACC_LPF_SENS);
        static corrector2_t corrector2(COR2_COURSE_LPF_SENS);
        float v_sns_tang      = indata[V_SNS],
              course_sns_rad  = degtorad(indata[COURSE_SNS]);
        vector v_sns(v_sns_tang * sin(course_sns_rad), v_sns_tang * cos(course_sns_rad), 0);
        if ((!correction_done) && (corrector2.getcnt() >= COR_CNT_THSD)) {
            correction_done = true;
            SINS.setv(v_sns);
            vector corr_omega(0, 0, corrector2.geterr() * UPD_FREQ);
            corr_omega.Localize(SINS.getb());
            SINS.upd(acc_raw, omega_raw + corr_omega);
            corrector2.corrected();
            printf("\nCorrected at i = %d\n", i);
        } else {
            SINS.upd(acc_raw, omega_raw);
        }
        vector omega_ins_L = SINS.getomega();
        vector acc_ins_L = SINS.getacc();
        corrector.upd(omega_ins_L.z, acc_ins_L, 1 / (float)UPD_FREQ);
        progb.upd(i);
        if ((i % (UPD_FREQ / OUT_FREQ)) == 0) {
            vector v_ins_L = SINS.getv();
            basis B = SINS.getb();
            float latit           = radtodeg(SINS.getlatit()),
                  longit          = radtodeg(SINS.getlongit()),
                  course_ins_rad  = vector::Angle(vector(0, 1, 0), vector(B.j.x, B.j.y, 0));
            static vector v_sns_prev(0, 0, 0);
            vector acc_sns = (v_sns - v_sns_prev) * OUT_FREQ;
            v_sns_prev = v_sns;
            if (B.j.x < 0) {
                course_ins_rad = 2 * M_PI - course_ins_rad;
            }
            corrector2.upd(course_sns_rad, course_ins_rad, omega_ins_L.z, v_sns_tang);
//            corrector.upd_v_sns(v_sns, 1 / (float)OUT_FREQ);
            fprintf(outfile,
                    "%20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf %20.10lf\r\n",
                    v_sns.x,    v_sns.y, v_sns_tang, acc_sns.x, indata[LATIT_SNS], indata[LONGIT_SNS], indata[H_SNS], indata[COURSE_SNS],
                    indata[VE_INS], indata[VN_INS],
                    v_ins_L.x, v_ins_L.y, v_ins_L.Length(), acc_ins_L.x, indata[GYRO_Z], latit, longit, SINS.geth(), radtodeg(course_ins_rad),
                    radtodeg(corrector2.geterr()), corrector.get_acc_err().x, radtodeg(SINS.getroll()), radtodeg(SINS.getpitch()), 0); //for debug
        }
    }
    printf("\n");
    fclose(infile);
    fclose(outfile);

	return 0;
}
