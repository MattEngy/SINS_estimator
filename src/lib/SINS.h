#include "vector.h"
#include "basis.h"

using namespace Vectors;

class SINS_t {
public:
    SINS_t(double lambda, double fi, double h, vector V, basis B, double period);
    void upd(vector acc_raw, vector omega_raw);
    double getlambda();
    double getfi();
    double geth();
private:
    double lambda_,
           fi_,
           h_;
    vector V_;
    basis B_;
    double period_;
};
