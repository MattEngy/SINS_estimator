#pragma once

class LPF_t {
public:
    LPF_t() {};
    LPF_t(float k, float val);
    float upd(float val);
    float getval();
private:
    float k_, val_;
};
