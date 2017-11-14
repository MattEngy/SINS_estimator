#include "SINS.h"
#include <math.h>

SINS_t::SINS_t(double fi, double lambda, double h, vector V, basis B, double period) {
    fi_     = fi;
    lambda_ = lambda;
    h_      = h;
    V_      = V;
    B_      = B;
    period_ = period;
}

double SINS_t::getfi() {
    return fi_;
}

double SINS_t::getlambda() {
    return lambda_;
}

double SINS_t::geth() {
    return h_;
}

void SINS_t::upd(vector acc_raw, vector omega_raw) {
    double R = 6356863;
    vector g(0, 0, -9.80655);
    double Ud = M_PI / (12 * 60 * 60);
    
    double rd = R + h_;    
    vector r(0, 0, rd);
    vector U(0, Ud * cos(fi_), Ud * sin(fi_));
    vector omegaL = vector(-V_.y / rd,
                           V_.x / rd,
                           V_.x / rd * tan(fi_))
                    + U;
    vector accI_L = acc_raw;
    accI_L.Globalize(B_);

    vector acc = accI_L - vector::CrossProd((omegaL + U), V_)
                 - vector::CrossProd(U, vector::CrossProd(U, r)) + g;

    V_ = V_ + acc * period_;
    
    lambda_ += V_.x / (rd * cos(fi_)) * period_;
    fi_     += V_.y / rd * period_;
//    h_      += V_.z * period_;
    
    vector omegaB_L = omega_raw;
    omegaB_L.Globalize(B_);
    omegaB_L = omegaB_L - omegaL;
    B_.rotate(omegaB_L * period_);
/*   L_I_ = basis(vector(-sin(lambda),           cos(lambda),            0),
                 vector(-sin(fi) * cos(lambda), -sin(fi) * sin(lambda), cos(fi)),
                 vector(cos(fi) * cos(lambda),  cos(fi) * sin(lambda), sin(fi)));
*/
}
