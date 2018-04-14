#pragma once
#include "vector.h"

using namespace Vectors;

class LPF_t {
public:
    LPF_t() {};
    LPF_t(float k, float val);
    float upd(float val);
    float upd(float val, float sens);
    float getval();
    operator float();
private:
    float k_, val_;
};

class vec_LPF_t {
public:
    vec_LPF_t() {};
    vec_LPF_t(float k, vector val);
    vector upd(vector val);
    vector upd(vector val, float sens);
    vector getval();
    operator vector();
private:
    float k_;
    vector val_;
};
