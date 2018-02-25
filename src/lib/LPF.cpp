#include "LPF.h"

LPF_t::LPF_t(float k, float val) {
    k_   = k;
    val_ = val;
}

float LPF_t::upd(float val) {
    val_ = val_ * (1 - k_) + val * k_;
    return val_;
}

float LPF_t::getval() {
    return val_;
}
