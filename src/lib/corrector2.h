#pragma once
#include "params.h"
#include "LPF.h"
#include "vector.h"
#include "math.h"

class corrector2_t {
public:
    corrector2_t(float lpf_sens, float course_err) {
        course_err_ = LPF_t(lpf_sens, course_err);
        prev_trusted_ = false;
        trusted_cnt_ = 0;
    }

    float upd(double course_sns, double course_ins, double omega_z, double v_sns_tang) {
        if ((v_sns_tang > 5) && (omega_z < 0.3)) {
            if (prev_trusted_) {
                course_err_.upd(__trim__(course_ins - course_sns));
                trusted_cnt_++;
            }
            prev_trusted_ = true;
        } else {
            prev_trusted_ = false;
            trusted_cnt_ -= 10 * ((trusted_cnt_ - 10) >= 0);
        }
        return course_err_.getval();
    }

    float geterr() {
        return course_err_.getval();
    }

    int getcnt() {
        return trusted_cnt_;
    }

private:
    float __trim__(float val) {
        if (val > M_PI) {
            return val - 2 * M_PI;
        }
        if (val < -M_PI) {
            return val + 2 * M_PI;
        }
        return val;
    }

    LPF_t course_err_;
    int trusted_cnt_;
    bool prev_trusted_;
};
