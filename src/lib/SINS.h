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
private:
    double latit_,
           longit_,
           h_;
    vector V_;
    basis B_;
    double period_;
};
