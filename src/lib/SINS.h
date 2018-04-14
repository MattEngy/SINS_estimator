#include "vector.h"
#include "basis.h"

using namespace Vectors;

class SINS_t {
public:
    SINS_t(double latit, double longit, double h, vector V, basis B, double period);
    SINS_t(double latit, double longit, double h, vector f, vector U, double period);
    void upd(vector acc_raw, vector omega_raw);
    double getlatit();
    double getlongit();
    double geth();
    vector getv();
    void setv(vector v);
    vector getacc();
    vector getomega();
    basis getb();
    float getroll();
    float getpitch();
private:
    double latit_,
           longit_,
           h_;
    vector V_,
           omega_L_,
           acc_L_;
    basis B_;
    double period_;
};
