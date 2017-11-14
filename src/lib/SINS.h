#include "vector.h"
#include "basis.h"

using namespace Vectors;

class SINS_t {
public:
    SINS_t(double fi, double lambda, double h, vector V, basis B, double period);
    void upd(vector acc_raw, vector omega_raw);
    double getfi();
    double getlambda();
    double geth();
private:
    double fi_,
           lambda_,
           h_;
    vector V_;
    basis B_;
    double period_;
};
