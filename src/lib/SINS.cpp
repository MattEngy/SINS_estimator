#include "SINS.h"
#include <math.h>

SINS_t::SINS_t(double lambda, double fi, double h, vector V, basis B, double period) {
    lambda_ = lambda;
    fi_     = fi;
    h_      = h;
    V_      = V;
    B_      = B;
    period_ = period;
}

double SINS_t::getlambda() {
    return lambda_;
}

double SINS_t::getfi() {
    return fi_;
}

double SINS_t::geth() {
    return h_;
}

void SINS_t::upd(vector acc_raw, vector omega_raw) {
    double R = 6400 * 1000;
    vector g(0, 0, -9.8);
    double Ud = M_PI / (12 * 60 * 60);
    
    double rd = R + h_;    
    vector r(0, 0, rd);
    vector U(0, Ud * cos(fi_), Ud * sin(fi_));
    vector omegaL = vector(-V_.y / rd, V_.x / (rd * cos(fi_)), V_.x / (rd * cos(fi_)) * tan(fi_)) + U;

    vector acc = acc_raw - vector::CrossProd((omegaL), V_)
                 - vector::CrossProd(U, vector::CrossProd(U, r)) + g;

    V_ = V_ + acc * period_;
    
    lambda_ += V_.x / (rd * cos(fi_)) * period_;
    fi_     += V_.y / rd * period_;
    h_      += V_.z * period_;
    
    vector omegaB_L = omega_raw;
    omegaB_L.Globalize(B_);
    B_.rotate(omegaB_L * period_);
/*   L_I_ = basis(vector(-sin(lambda),           cos(lambda),            0),
                 vector(-sin(fi) * cos(lambda), -sin(fi) * sin(lambda), cos(fi)),
                 vector(cos(fi) * cos(lambda),  cos(fi) * sin(lambda), sin(fi)));
*/
}
