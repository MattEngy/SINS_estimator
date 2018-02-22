#pragma once

#define COLS_CNT 22
#define PROGB_LEN 100
#define OUT_INTERVAL 100
#define CAL_TIME 60000
#define UPD_PERIOD 0.01
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
