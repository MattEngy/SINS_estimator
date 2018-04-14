#include "LPF.h"

LPF_t::LPF_t(float k, float val) {
    k_   = k;
    val_ = val;
}

float LPF_t::upd(float val) {
    val_ = val_ * (1 - k_) + val * k_;
    return val_;
}

float LPF_t::upd(float val, float sens) {
    val_ = val_ * (1 - sens) + val * sens;
    return val_;
}

float LPF_t::getval() {
    return val_;
}

LPF_t::operator float() {
    return val_;
}

vec_LPF_t::vec_LPF_t(float k, vector val) {
    k_   = k;
    val_ = val;
}

vector vec_LPF_t::upd(vector val) {
    val_ = val_ * (1 - k_) + val * k_;
    return val_;
}

vector vec_LPF_t::upd(vector val, float sens) {
    val_ = val_ * (1 - sens) + val * sens;
    return val_;
}

vector vec_LPF_t::getval() {
    return val_;
}

vec_LPF_t::operator vector() {
    return val_;
}
