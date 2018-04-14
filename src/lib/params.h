#pragma once

#define INP_COLS_CNT 22
#define PROGB_LEN 100
#define OUT_FREQ 1
#define CAL_TIME 600
#define UPD_FREQ 100
#define COR2_COURSE_LPF_SENS 0.005
#define COR2_CNT_THSD 500
#define COR_COURSE_LPF_SENS 0.1
#define COR_ACC_LPF_SENS 0.05
#define COR_CNT_THSD 4

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
    H_SNS = 11,
    VE_INS = 14,
    VN_INS = 15
};
