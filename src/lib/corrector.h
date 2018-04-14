#pragma once
#include "params.h"
#include "LPF.h"
#include "vector.h"

class corrector_t {
public:
    corrector_t(float course_sens, float acc_sens) {
        H_err_ = LPF_t(course_sens, 0);
        acc_err_ = vec_LPF_t(acc_sens, vector(0, 0, 0));
        acc_sns_lpf_ = vec_LPF_t(1, vector(0, 0, 0));
        prev_trusted_ = false;
        inited_ = false;
        trusted_cnt_ = 0;
    }

    void upd(double omegaz, vector acc_ins, double elapsed) {
        acc_ins.z = 0;
        if ((v_sns_.Length() > 10) /*&& (fabs(omegaz) > 0.018)*/ && (acc_ins.Length() > 0.6) && (acc_sns_lpf_.getval().Length() > 0.6)) {
            if (prev_trusted_) {
                if (inited_) {
                    acc_err_.upd(acc_ins - acc_sns_);
                    H_err_.upd((acc_err_.getval().x * acc_sns_lpf_.getval().y - acc_err_.getval().y * acc_sns_lpf_.getval().x) /
                               (acc_sns_lpf_.getval().Length() * acc_sns_lpf_.getval().Length()));
                } else {
                    acc_err_.upd(acc_ins - acc_sns_, 1);
                    H_err_.upd((acc_err_.getval().x * acc_sns_lpf_.getval().y - acc_err_.getval().y * acc_sns_lpf_.getval().x) /
                               (acc_sns_lpf_.getval().Length() * acc_sns_lpf_.getval().Length()), 0);
                    inited_ = true;
                }
            }
            prev_trusted_ = true;
            trusted_cnt_++;
        } else {
            prev_trusted_ = false;
            trusted_cnt_ -= fmin(trusted_cnt_, 10);
        }
    }

    float get_course_err() {
        return H_err_;
    }

    float getcnt() {
        return trusted_cnt_;
    }

    vector get_acc_err() {
        return acc_err_;
    }

    vector upd_v_sns(vector vsns, float elapsed) {
        acc_sns_ = (vsns - v_sns_) / elapsed;
        acc_sns_lpf_.upd(acc_sns_);
        v_sns_ = vsns;
    }

private:
    vector v_sns_,
           acc_sns_;
    LPF_t H_err_;
    vec_LPF_t acc_err_,
              acc_sns_lpf_,
              acc_ins_;
    bool prev_trusted_,
         inited_;
    int trusted_cnt_;
};
