#pragma once
#include "vector.h"

namespace Vectors {
    class basis {
    public:

        vector i, j, k;

        basis();
        basis(vector i0, vector j0, vector k0);
        basis(double elems[3][3]);

        vector &operator[](char index);
        void rotate(vector axis);
        void transpond();
        basis operator*(basis b);
        basis operator*(double b);
        basis operator+(basis b);
        basis operator-(basis b);
        char* tostring();
    };
}
