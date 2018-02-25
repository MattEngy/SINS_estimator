#pragma once
#include "params.h"
#include "LPF.h"
#include "vector.h"

class corrector_t {
public:
    corrector_t() {
        H_err_ = LPF_t(1, 0);
        prev_trusted_ = false;
    }

    void upd(vector omega, vector v_sns, vector v_ins) {
        vector acc_sns = (v_sns - v_sns_prev_) * 1,
               acc_ins = (v_ins - v_ins_prev_) * 1,
               acc_err = acc_ins - acc_sns;
        if ((v_sns.Length() > 5) && (omega.z < 0.3) && (acc_sns.Length() > 0.5)) {
            if (prev_trusted_) {
                H_err_.upd((acc_err.x * acc_sns.y - acc_err.y * acc_sns.x) / (acc_sns.x * acc_sns.x + acc_sns.y * acc_sns.y));
            }
            prev_trusted_ = true;
            v_sns_prev_ = v_sns;
            v_ins_prev_ = v_ins;
        } else {
            prev_trusted_ = false;
        }
    }

    float geterr() {
        return H_err_.getval();
    }

private:
    vector v_sns_prev_,
           v_ins_prev_;
    LPF_t H_err_;
    bool prev_trusted_;

};
